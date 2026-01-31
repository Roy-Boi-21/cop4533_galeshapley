#include <iostream>
#include <vector>
#include "utilities.h"
#include "Node.h"
#include "Matcher.h"
#include "Verifier.h"
using namespace std;

int main() {
    // Ask how the user wants to input data into the program.
    string choice;
    while (true) {
        cout << "How will you input the data?" << endl;
        cout << "1. Manually" << endl;
        cout << "2. Read a file" << endl;
        cin >> choice;
        if ((choice == "1") || (choice == "2")) {
            break;
        } else {
            cout << "Please choose a valid option." << endl;
        }
    }

    vector<Node*> hospitals;
    vector<Node*> students;

    if (choice == "1") {
        pair<vector<Node*>, vector<Node*>> data = read_manually();
        hospitals = data.first;
        students = data.second;
    } else {
        pair<vector<Node*>, vector<Node*>> data = read_from_file();
        hospitals = data.first;
        students = data.second;
    }

    // DEBUG: Output the preference lists.
    /*for (auto h : hospitals) {
        h->print_preferences();
    }
    cout << endl;
    for (auto s : students) {
        s->print_preferences();
    }
    cout << endl;*/

    Matcher m(hospitals, students);
    vector<pair<Node*, Node*>> matches = m.match();
    write_to_file(matches);
    // DEBUG: Print out the matches.
    /*for (auto match : matches) {
        match.first->print();
    }*/

    Verifier v(matches);
    cout << v.verify() << endl;

    // Deallocate the hospitals and students.
    for (int i = 0; i < hospitals.size(); i++) {
        delete hospitals[i];
        delete students[i];
    }
    return 0;
}
