
#include "Graph.h"
#include "BetterPriorityQueue.h"
#include <iostream>
#include <climits>
#include <cassert>

using namespace std;

//getMin
//returns minimum value node in queue ~THANKS binary heap~
DNode getMin(BetterPriorityQueue q){
	int minPri = INT_MAX;
	DNode min = q.top();
	//Find min by looking at top item and then popping to go through queue
	for(size_t i = 0; i < q.size(); i++){
		if(q.top().pri < minPri){
			minPri = q.top().pri;
			min = q.top();
		}
		q.pop();
	}

	//Not pass by reference, so we don't have to worry about pushing nodes back in
	return min;
}

//popMin
//Removes minimum value from queue ~thanks again binary heap~
void popMin(BetterPriorityQueue& q, DNode min){
	vector<DNode> popped;
	//Check top value with minimum, pop and vec_push if it ain't it chief
	for(size_t i = 0; i < q.size(); i++){
		if(q.top() == min){
			q.pop();
		}else{
			popped.push_back(q.top());
			q.pop();
		}
	}
	//Pass by reference, so we DO have to worry about pushing items back into queue
	for(DNode node : popped){
		q.push(node);
	}
}

//Dijkstra
//Worst-case time complexity: O(n^3)
//This is because I have for loop that runs for the initial size of the queue with 
//another for loop that runs for the size of a set of edges for the minimum node with
//ANOTHER for loop in Update that runs for the size of the queue.
int dijkstra(const GraphNode *start, const GraphNode *end, Graph *g){
	bool startIn = false;
	bool endIn = false;
	vector<GraphNode*> nodez = g->GetNodes();
	//Ensure start and end nodes are actually in graph
	for(GraphNode* n : nodez){
		if(n == start){
			startIn = true;
		}
		if(n == end){
			endIn = true;
		}
	}
	//Return "infinity" if that jawn ain't in there
	if(!startIn || !endIn){
		return INT_MAX;
	}

	//If start and end goal are the same, return 0
	if (start == end){
		return 0;
	}
	
	BetterPriorityQueue list;
	vector<GraphNode*> nodes = g->GetNodes();
	//Initially populate Queue
	for(GraphNode* node: nodes){
		DNode cur;
		cur.node = node;
		if(node == start){
			cur.pri = 0;
		}
		list.push(cur);
	}

	DNode min;
	size_t size = list.size();
	//I finally present to you: Dijkstra's algorithm... 
	for(size_t i = 0; i < size; i++){
		cout << list.ToString() << endl << endl;
		min = getMin(list); //Because pop would be too easy
		//"base case"
		if(min.node == end){
			return min.pri;
		}
		vector<GraphEdge*> edges = g->GetEdges(min.node);
		//Update priorites in tree as paths are discovered
		for(GraphEdge* edge : edges){
			DNode cur;
			cur.node = edge->to;
			cur.pri = min.pri + edge->weight;
			list.Update(cur);
		}
		popMin(list, min);  //Pop? Never heard of her
	}

	return min.pri; //If we actually get here the apocalypse has finally started... Arm up!
}

//DijkstraTest
int DijkstraTest(){
	Graph *g = new Graph();
	
	GraphNode *a = g->AddNode('1');
	GraphNode *b = g->AddNode('2');
	GraphNode *c = g->AddNode('3');
	GraphNode *d = g->AddNode('4');
	GraphNode *e = g->AddNode('5');
	GraphNode *f = g->AddNode('6');
	g->AddNode('7');

	g->AddEdge(a, b, 7);
	g->AddEdge(a, c, 9);
	g->AddEdge(a, f, 14);

	g->AddEdge(b, a, 7);
	g->AddEdge(b, c, 10);
	g->AddEdge(b, d, 15);

	g->AddEdge(c, a, 9);
	g->AddEdge(c, b, 10);
	g->AddEdge(c, d, 11);
	g->AddEdge(c, f, 2);

	g->AddEdge(d, b, 15);
	g->AddEdge(d, c, 11);
	g->AddEdge(d, e, 6);

	g->AddEdge(f, a, 14);
	g->AddEdge(f, c, 2);
	g->AddEdge(f, e, 9);
	
	g->AddEdge(e, d, 6);
	g->AddEdge(e, f, 9);


	unsigned int ans = dijkstra(g->NodeAt(0), e, g);
	assert(ans == 20);

	delete g;
		
	return ans;
}


int main(){
	
	int ans = DijkstraTest();
	cout << "ans: "  << ans << endl;
	
	return 0;
}
