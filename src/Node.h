//
// Created by roybo on 1/30/2026.
//

#ifndef GALESHAPLEY_NODE_H
#define GALESHAPLEY_NODE_H

#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class Node {
    string type;
    int id;
    Node* assigned_node;
    vector<Node*> preferences;

public:
    Node(string type, int id);
    string get_type();
    int get_id();
    Node* get_assigned();
    vector<Node*> get_preferences();
    void set_assigned(Node* node);
    int get_node_preference(Node* node);

    pair<bool, Node*> assign(Node* node);
    void add_preference(Node* node);
    void add_preferences(vector<Node*> nodes);

    void print();
    void print_preferences();
};


#endif //GALESHAPLEY_NODE_H
