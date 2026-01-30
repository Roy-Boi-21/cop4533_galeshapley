//
// Created by roybo on 1/30/2026.
//

#include "Matcher.h"
#include <utility>
using namespace std;

Matcher::Matcher(vector<Node*> hospitals, vector<Node*> students) {
    this->hospitals = std::move(hospitals);
    this->students = std::move(students);
}

vector<pair<Node*, Node*>> Matcher::match() {
    queue<Node*> hospital_queue;
    for (auto h : hospitals) {
        hospital_queue.push(h);
    }

    while (!hospital_queue.empty()) {
        Node* h = hospital_queue.front();
        for (auto s : h->get_preferences()) {
            pair<bool, Node*> result = h->assign(s);
            bool assign_successful = result.first;
            Node* unassigned_node = result.second;

            if (assign_successful) {
                if (unassigned_node != nullptr) {
                    hospital_queue.push(unassigned_node);
                }
                hospital_queue.pop();
                break;
            }
        }
    }

    vector<pair<Node*, Node*>> result;

    result.reserve(hospitals.size());
    for (auto h : hospitals) {
        result.emplace_back(h, h->get_assigned());
    }

    return result;
}
