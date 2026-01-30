//
// Created by roybo on 1/30/2026.
//

#include "Node.h"
#include <utility>
using namespace std;

Node::Node(string type, string name) {
    this->type = std::move(type);
    this->name = std::move(name);
    assigned_node = nullptr;
}

string Node::get_type() {
    return type;
}

string Node::get_name() {
    return name;
}

Node* Node::get_assigned() {
    return assigned_node;
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

bool Node::assign(Node* node) {
    if (node == nullptr) {
        return false;
    }

    if (node->get_type() == type) {
        throw("ERROR: Cannot assign two nodes of the same type.");
    }

    Node* assigned = node->get_assigned();
    if (assigned == nullptr) {
        // If a node is vacant, accept it.
        assigned_node = node;
        node->set_assigned(this);
        return true;
    } else if (get_node_preference(this) > get_node_preference(assigned)) {
        // If a node prefers this node more to their current one, accept this node.
        assigned_node = node;
        node->set_assigned(this);
        assigned->set_assigned(nullptr);
        return true;
    } else {
        // If a node prefers their current node to this node, reject this node.
        return false;
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
        cout << type << " " << name << " is unassigned.";
    } else {
        cout << type << " " << name << " is assigned to "
        << assigned_node->get_type() << " " << assigned_node->get_name() << endl;
    }
}
