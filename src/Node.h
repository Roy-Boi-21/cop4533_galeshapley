//
// Created by roybo on 1/30/2026.
//

#ifndef GALESHAPLEY_NODE_H
#define GALESHAPLEY_NODE_H

#include <iostream>
#include <vector>
using namespace std;

class Node {
    string type;
    string name;
    Node* assigned_node;
    vector<Node*> preferences;

public:
    Node(string type, string name);
    string get_type();
    string get_name();
    Node* get_assigned();
    void set_assigned(Node* node);
    int get_node_preference(Node* node);

    bool assign(Node* node);
    void add_preference(Node* node);
    void add_preferences(vector<Node*> nodes);

    void print();
};


#endif //GALESHAPLEY_NODE_H
