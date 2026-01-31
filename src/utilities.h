//
// Created by roybo on 1/30/2026.
//

#ifndef GALESHAPLEY_UTILITIES_H
#define GALESHAPLEY_UTILITIES_H

#include "Node.h"
#include <vector>
#include <utility>
#include <fstream>
using namespace std;

pair<vector<Node*>, vector<Node*>> read_manually();
vector<int> line_to_numbers(const string& line);
pair<vector<Node*>, vector<Node*>> read_from_file();
void write_to_file(const vector<pair<Node*, Node*>>& nodes);

#endif //GALESHAPLEY_UTILITIES_H
