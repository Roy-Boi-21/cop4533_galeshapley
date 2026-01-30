//
// Created by roybo on 1/30/2026.
//

#ifndef GALESHAPLEY_VERIFIER_H
#define GALESHAPLEY_VERIFIER_H

#include "Node.h"
using namespace std;

class Verifier {
    vector<pair<Node*, Node*>> matches;

public:
    Verifier(vector<pair<Node*, Node*>> matches);
    string verify();
};


#endif //GALESHAPLEY_VERIFIER_H
