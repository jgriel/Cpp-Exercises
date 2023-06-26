#include <string>
#include <iostream>
#include "BetterPriorityQueue.h"

using namespace std;

//Contains
bool BetterPriorityQueue::Contains(DNode node){
    for(DNode n : c){
        if (n == node){
            return true;
        }
    }
    return false;
}

//Update
bool BetterPriorityQueue::Update(DNode node){
    //Check if node is in queue, if it is, save idx
    int idx;
    bool in = false;
    for (size_t i = 0; i < c.size(); i++){
        if (c.at(i) == node){
            in = true;
            idx = i;
        }
    }
    //ignore if not in queue
    if(!in){
        return false;
    }
    //ignore if priority trying to be inserted is lower
    else if(node.pri > c.at(idx).pri){
        return false;
    }

    //remove old node and enqueue new node
    c.erase(c.begin() + idx);
    this->push(node);

    return true;
}

//ToString
string BetterPriorityQueue::ToString(){
    string str;
    str.push_back('[');
    //append each node
    for(size_t i = 0; i < c.size(); i++){
        str.append(DnodeToString(c.at(i)));
        if(i != c.size() - 1){
            str.append(", ");
        }
    }
    str.push_back(']');

    return str;
}

//DnodeToString
string BetterPriorityQueue::DnodeToString(DNode node){
    string str;
    str.push_back('(');
    str.push_back(node.node->key);
    str.append(": " + to_string(node.pri) + ")");

    return str;
}