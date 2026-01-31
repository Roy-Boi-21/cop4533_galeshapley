//
// Created by roybo on 1/30/2026.
//

#ifndef GALESHAPLEY_UTILITIES_H
#define GALESHAPLEY_UTILITIES_H

#include "Node.h"
#include <set>
#include <queue>
#include <vector>
#include <utility>
#include <fstream>
using namespace std;

pair<vector<Node*>, vector<Node*>> read_manually();
vector<int> line_to_numbers(const string& line);
pair<vector<Node*>, vector<Node*>> read_from_file();
pair<vector<Node*>, vector<Node*>> generate_data();
void write_to_file(const vector<pair<Node*, Node*>>& nodes);

vector<pair<Node*, Node*>> read_matches_manually(const pair<vector<Node*>, vector<Node*>>& data);
vector<pair<Node*, Node*>> read_matches_file(const pair<vector<Node*>, vector<Node*>>& data);
vector<pair<Node*, Node*>> generate_matches(const pair<vector<Node*>, vector<Node*>>& data);

#endif //GALESHAPLEY_UTILITIES_H
