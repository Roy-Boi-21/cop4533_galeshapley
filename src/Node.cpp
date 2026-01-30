//
// Created by roybo on 1/30/2026.
//

#include "Node.h"
#include <utility>
using namespace std;

Node::Node(string type, int id) {
    this->type = std::move(type);
    this->id = id;
    assigned_node = nullptr;
}

string Node::get_type() {
    return type;
}

int Node::get_id() {
    return id;
}

Node* Node::get_assigned() {
    return assigned_node;
}

vector<Node*> Node::get_preferences() {
    return preferences;
}

void Node::set_assigned(Node* node) {
    assigned_node = node;
}

int Node::get_node_preference(Node* node) {
    if (node == nullptr) {
        return -1;
    }

    for (int i = 0; i < preferences.size(); i++) {
        if (preferences[i] == node) {
            return i + 1;
        }
    }

    return -1;
}

pair<bool, Node*> Node::assign(Node* node) {
    if (node == nullptr) {
        return pair(false, nullptr);
    }

    if (node->get_type() == type) {
        throw("ERROR: Cannot assign two nodes of the same type.");
    }

    Node* assigned = node->get_assigned();
    if (assigned == nullptr) {
        // If a node is vacant, accept it.
        assigned_node = node;
        node->set_assigned(this);
        return pair(true, nullptr);
    } else if (get_node_preference(this) > get_node_preference(assigned)) {
        // If a node prefers this node more to their current one, accept this node.
        assigned_node = node;
        node->set_assigned(this);
        assigned->set_assigned(nullptr);
        return pair(false, assigned);
    } else {
        // If a node prefers their current node to this node, reject this node.
        return pair(false, nullptr);
    }
}

void Node::add_preference(Node* node) {
    preferences.push_back(node);
}

void Node::add_preferences(vector<Node*> nodes) {
    for (auto node : nodes) {
        preferences.push_back(node);
    }
}

void Node::print() {
    if (assigned_node == nullptr) {
        cout << type << " " << id << " is unassigned.";
    } else {
        cout << type << " " << id << " is assigned to "
        << assigned_node->get_type() << " " << assigned_node->get_id() << endl;
    }
}

void Node::print_preferences() {
    cout << type << " " << id << "'s Preferences:" << endl;
    for (int j = 0; j < preferences.size(); j++) {
        cout << j + 1 << ": " << preferences[j]->get_type() << " " << preferences[j]->get_id() << endl;
    }
}
