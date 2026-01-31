//
// Created by roybo on 1/30/2026.
//

#include "Verifier.h"
#include <set>
#include <utility>
using namespace std;

Verifier::Verifier(vector<pair<Node*, Node*>> matches) {
    this->matches = std::move(matches);
}

string Verifier::verify() {
    // Check for duplicate matches.
    set<Node*> h_set, s_set;
    for (auto match : matches) {
        if (h_set.count(match.first) > 0) {
            return "INVALID: Duplicate hospital found in the matches.";
        }
        if (s_set.count(match.second) > 0) {
            return "INVALID: Duplicate student found in the matches.";
        }
        h_set.insert(match.first);
        s_set.insert(match.second);
    }

    // Check for unstable matches.
    for (auto match : matches) {
        // An unstable pair is when X prefers Y, Y prefers X, yet X and Y are assigned to different nodes.
        Node* h = match.first;
        for (auto s : h->get_upper_preferences()) {
            bool s_prefers_h = s->get_node_preference(s->get_assigned()) > s->get_node_preference(h);
            if (s_prefers_h) {
                return "UNSTABLE: " + h->get_type() + " " + to_string(h->get_id()) + " and " +
                s->get_type() + " " + to_string(s->get_id()) +
                " prefer each other but neither are assigned to each other.";
            }
        }
    }

    return "VALID STABLE";
}
