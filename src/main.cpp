#include <iostream>
#include <vector>
#include "Node.h"
#include "Matcher.h"
#include "Verifier.h"
using namespace std;

int main() {
    // Get how many students and hospitals need to be matched.
    int n = 0;
    cin >> n;

    // Create the hospitals and students.
    vector<Node*> hospitals;
    vector<Node*> students;
    for (int i = 1; i <= n; i++) {
        hospitals.push_back(new Node("Hospital", i));
        students.push_back(new Node("Student", i));
    }
    // Generate the Hospitals' preference lists.
    for (int i = 0; i < n; i++) {
        Node* h = hospitals[i];
        for (int j = 0; j < students.size(); j++) {
            int s = 0;
            cin >> s;
            h->add_preference(students[s - 1]);
        }
    }
    // Generate the Students' preference lists.
    for (int i = 0; i < n; i++) {
        Node* s = students[i];
        for (int j = 0; j < hospitals.size(); j++) {
            int h = 0;
            cin >> h;
            s->add_preference(hospitals[h - 1]);
        }
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
    /*for (auto match : matches) {
        match.first->print();
    }*/

    Verifier v(matches);
    cout << v.verify() << endl;

    // Deallocate the hospitals and students.
    for (int i = 0; i < n; i++) {
        delete hospitals[i];
        delete students[i];
    }
    return 0;
}
