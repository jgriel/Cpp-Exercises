#include <vector>
#include <string>
#include <iostream>
#include "Graph.h"

using namespace std;

//Destructor
Graph::~Graph(){
  for(GraphNode* gn : nodes){
        delete gn;
    }
    for(GraphEdge* ge : edges){ 
        delete ge;
    }
}

//AddNode
GraphNode* Graph::AddNode(char key, int data){
    GraphNode* node = new GraphNode;
    node->key = key;
    node->data = data;
    for (GraphNode* gn:nodes){
        if(node->key == gn->key){
            throw invalid_argument("Node with this key already exists.");
        }
    }
    nodes.push_back(node);
    return node;
}

//AddEdge
GraphEdge* Graph::AddEdge(GraphNode *gn1, GraphNode *gn2, unsigned int weight){
    //Check if either node is not in graph
    bool Node1In = false;
    bool Node2In = false;
    for(size_t i = 0; i < nodes.size(); i++){
        if(gn1->key == nodes.at(i)->key){
            Node1In = true;
        }
        if(gn2->key == nodes.at(i)->key){
            Node2In = true;
        }
    }
    if (!Node1In || !Node2In){
        throw invalid_argument("1 of these nodes does not exist in the graph.");
    }
    
    //Push to edges vector
    GraphEdge* edge = new GraphEdge;
    edge->from = gn1;
    edge->to = gn2;
    edge->weight = weight;
    edges.push_back(edge);

    //Push to adjList
    bool found = true;
    int idx;
    if(adjList.at(0).size() == 0){
        adjList.at(0).push_back(edge);
    }else{
        for(size_t i = 0; i < adjList.size(); i++){
            if(adjList.at(i).size() != 0 && adjList.at(i).at(0)->from->key == edge->from->key){
                adjList.at(i).push_back(edge);
            }else if(adjList.at(i).size() == 0 && adjList.at(i-1).size() != 0){
                idx = i;
                found = false;
            }
        }
        if (!found){
            adjList.at(idx).push_back(edge);
        }
    }

    return edge;
}

//NodesToString
string Graph::NodesToString() const{
    if (nodes.size() <= 0){
        return "[]";
    }

    string str = "[";
    //costruct each node in string form
    for (size_t i = 0; i < nodes.size(); i++){
        str.append(GraphNodeToString(nodes.at(i)));
        if (i != nodes.size() - 1){
            str.append(", ");
        }
    }
    str.push_back(']');

    return str;
}

//ToString
string Graph::ToString() const{
    if (nodes.size() <= 0){
        return "[]";   
    }

    string str;
    //add each node to list
    for(size_t i = 0; i < nodes.size(); i++){
        str.push_back(nodes.at(i)->key);
        str.append(" | ");

        //add each edge to a given node line
        for(size_t x = 0; x < edges.size(); x++){
            if (edges.at(x)->from->key == nodes.at(i)->key){
                str.append(GraphEdgeToString(edges.at(x)));
                for(size_t y = x + 1; y < edges.size(); y++){
                    if (edges.at(y)->from->key == edges.at(x)->from->key){
                        str.append(", ");
                    }
                }
            }
        }
        str.append("\n");
    }

    return str;
}

//GraphNodeToString
string Graph::GraphNodeToString(const GraphNode *gn){
    string str = "(";
    str.push_back(gn->key);
    str.push_back(':');
    str.append(to_string(gn->data));
    str.push_back(')');
    return str;
}

//GraphEdgeToString
string Graph::GraphEdgeToString(const GraphEdge *ge){
    string str = "[(";
    str.push_back(ge->from->key);
    str.push_back(':');
    str.append(to_string(ge->from->data) + ")->(");
    str.push_back(ge->to->key);
    str.push_back(':');
    str.append(to_string(ge->to->data) + ") w:" + to_string(ge->weight));
    str.push_back(']');
    return str;
}

//GetEdges
const vector<GraphEdge*>& Graph::GetEdges(const GraphNode *gn) const{
    //Check if node is in node vector
    bool NodeIn = false;
    for (size_t i = 0; i < nodes.size(); i++){
        if(gn->key == nodes.at(i)->key){
            NodeIn = true;
        }
    }
    if(!NodeIn){
        throw invalid_argument("Node does not exist in the graph.");
    }

    //return appropriate vector from adjList
    int idx = -1;
    for(size_t i = 0; i < adjList.size(); i++){
        if(adjList.at(i).size() != 0 && adjList.at(i).at(0)->from->key == gn->key){
            return adjList.at(i);
            break;
        }
    }
    return adjList.at(idx);
}

//GetNodes
const vector<GraphNode*>& Graph::GetNodes() const{
    return nodes;
}

//NodeAt
const GraphNode* Graph::NodeAt(unsigned int idx) const{
    return nodes.at(idx);
}

//Size
size_t Graph::Size() const{
    return edges.size();
}

//Order
size_t Graph::Order() const{
    return nodes.size();
}

