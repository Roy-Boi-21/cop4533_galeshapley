//
// Created by roybo on 1/30/2026.
//

#ifndef GALESHAPLEY_MATCHER_H
#define GALESHAPLEY_MATCHER_H

#include "Node.h"
#include <queue>
#include <vector>
#include <utility>
using namespace std;

class Matcher {
    vector<Node*> hospitals;
    vector<Node*> students;

public:
    Matcher(vector<Node*> hospitals, vector<Node*> students);
    vector<pair<Node*, Node*>> match();
};


#endif //GALESHAPLEY_MATCHER_H
