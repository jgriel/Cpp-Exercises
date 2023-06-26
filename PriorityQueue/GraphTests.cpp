

#include "Graph.h"
#include <iostream>
#include <cassert>

using namespace std;


void TestAddNode(){
	cout << "Testing AddNode..." << endl;
	Graph g = Graph();
	g.AddNode('a', 15);
	
	//cout << "nodes: "  << g.NodesToString() << endl;
	//cout << "graph: " << g.ToString() << endl;
	
	assert(g.NodesToString() == "[(a:15)]");
	assert(g.ToString() == "a | \n");
	
	g.AddNode('b', 12);
	//cout << "nodes: "  << g.NodesToString() << endl;
	//cout << "graph: " << endl << g.ToString() << endl;

	assert(g.NodesToString() == "[(a:15), (b:12)]");
	assert(g.ToString() == "a | \nb | \n");
	
	// more tests....
	
	cout << "PASSED!" << endl << endl;
}


void TestAddEdge(){
	cout << "Testing AddEdge..." << endl;
	Graph g = Graph();
	GraphNode *gn1 = g.AddNode('a', 15);
	
	//cout << "nodes: "  << g.NodesToString() << endl;
	//cout << "graph: " << g.ToString() << endl;
	
	assert(g.NodesToString() == "[(a:15)]");
	assert(g.ToString() == "a | \n");
	
	GraphNode *gn2 = g.AddNode('b', 12);
	//cout << "nodes: "  << g.NodesToString() << endl;
	//cout << "graph: " << endl << g.ToString() << endl;

	assert(g.NodesToString() == "[(a:15), (b:12)]");
	assert(g.ToString() == "a | \nb | \n");
	
	GraphNode *gn3 = g.AddNode('c', 9);
	assert(g.NodesToString() == "[(a:15), (b:12), (c:9)]");
	assert(g.ToString() == "a | \nb | \nc | \n");
	
	cout << "here" << endl;
	g.AddEdge(gn1, gn3, 2);
	//cout << "nodes: "  << g.NodesToString() << endl;
	//cout << "graph: " << endl << g.ToString() << endl;
	assert(g.NodesToString() == "[(a:15), (b:12), (c:9)]");
	assert(g.ToString() == "a | [(a:15)->(c:9) w:2]\nb | \nc | \n");
	
	g.AddEdge(gn3, gn2);
	g.AddEdge(gn1, gn2, 8);
	//cout << "nodes: "  << g.NodesToString() << endl;
	//cout << "graph: " << endl << g.ToString() << endl;
	
	assert(g.NodesToString() == "[(a:15), (b:12), (c:9)]");
	assert(g.ToString() == "a | [(a:15)->(c:9) w:2], [(a:15)->(b:12) w:8]\nb | \nc | [(c:9)->(b:12) w:0]\n");
	
	cout << "PASSED!" << endl << endl;
}


void TestDestructor(){
	cout << "Testing Destructor..." << endl;
	Graph *g = new Graph();
	
	GraphNode *a = g->AddNode('a', 3);
	GraphNode *b = g->AddNode('b', 5);
	g->AddEdge(b, a, 15);
	
	delete g;
	
	
	Graph g2 = Graph();
	GraphNode *c = g2.AddNode('c', 12);
	g2.AddNode('d', 11);
	assert(c->key == 'c' && c->data == 12);
	
	
	
	cout << "NO ERRORS.  Use valgrind to check!" << endl << endl;
}

void TestGetNodes(){
	Graph g1 = Graph();
	vector<GraphNode*> vec1 = g1.GetNodes();
	assert(vec1.size() == 0);

	Graph g2 = Graph();
	g2.AddNode('a', 15);
	vector<GraphNode*> vec2 = g2.GetNodes();
	assert(vec2.size() == 1);

	Graph g3 = Graph();
	g3.AddNode('a', 15);
	g3.AddNode('b', 20);
	vector<GraphNode*> vec3 = g3.GetNodes();
	assert(vec3.size() == 2);
}

void TestNodeAt(){
	Graph g1 = Graph();
	g1.AddNode('a', 6);
	g1.AddNode('b', 32);
	g1.AddNode('c', 56);
	const GraphNode* test = g1.NodeAt(1);
	assert(test->key == 'b');
}

void TestSize(){
	Graph g1 = Graph();
	assert(g1.Size() == 0);

	Graph g2 = Graph();
	GraphNode* n1 = g2.AddNode('a', 6);
	GraphNode* n2 = g2.AddNode('b', 14);
	g2.AddEdge(n1, n2, 2);
	assert(g2.Size() == 1);
	
	
	Graph g3 = Graph();
	GraphNode* n3 = g3.AddNode('a', 6);
	GraphNode* n4 = g3.AddNode('b', 32);
	GraphNode* n5 = g3.AddNode('c', 56);
	g3.AddEdge(n3, n4, 2);
	g3.AddEdge(n3, n5, 3);
	assert(g3.Size() == 2);
}

void TestOrder(){
	Graph g1 = Graph();
	assert(g1.Order() == 0);

	Graph g2 = Graph();
	g2.AddNode('a', 6);
	assert(g2.Order() == 1);
	
	
	Graph g3 = Graph();
	g3.AddNode('a', 6);
	g3.AddNode('b', 32);
	g3.AddNode('c', 56);
	assert(g3.Order() == 3);
}

void TestGetEdges(){
	cout << "Testing GetEdges..." << endl;
	Graph g = Graph();
	GraphNode *gn1 = g.AddNode('a', 15);
	GraphNode *gn2 = g.AddNode('b', 12);
	GraphNode *gn3 = g.AddNode('c', 9);
	GraphNode *gn4 = g.AddNode('d', 16);

	GraphEdge *e1 = g.AddEdge(gn1, gn3, 2);
	g.AddEdge(gn3, gn2);
	GraphEdge *e3 = g.AddEdge(gn1, gn2, 8);
	GraphEdge *e4 = g.AddEdge(gn1, gn4, 12);
	
	
	vector<GraphEdge*> edges = g.GetEdges(gn1);
	vector<GraphEdge*> soln = {e1, e3, e4};
	assert(edges == soln);
	
	cout << "PASSED!" << endl << endl;
}


int main(){
	
	TestAddNode();
	TestAddEdge();
	TestDestructor();
	TestGetNodes();
	TestNodeAt();	
	TestSize();
	TestOrder();
	TestGetEdges();

	cout << "ALL TESTS PASSED!" << endl;
	return 0;
}
