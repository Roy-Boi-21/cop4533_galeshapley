#include <iostream>
#include <vector>
#include <chrono>
#include "utilities.h"
#include "Node.h"
#include "Matcher.h"
#include "Verifier.h"
using namespace std;

int main() {
    // Ask how the user wants to input data into the program.
    string choice;
    bool run_matching = false;
    bool run_verifier = false;

    cout << "Welcome to the Gale-Shapley Algorithm!" << endl;
    while (true) {
        cout << "What would you like to run?" << endl;
        cout << "1. Matching Engine" << endl;
        cout << "2. Verifier" << endl;
        cout << "3. Both" << endl;
        cin >> choice;

        run_matching = ((choice == "1") || (choice == "3"));
        run_verifier = ((choice == "2") || (choice == "3"));

        if ((choice == "1") || (choice == "2") || (choice == "3")) {
            break;
        } else {
            cout << "Please choose a valid option." << endl;
        }
    }

    choice.clear();
    while (true) {
        cout << "How will you input the data about the hospitals and students?" << endl;
        cout << "1. Manually" << endl;
        cout << "2. Read a file" << endl;
        cout << "3. Randomly generate data" << endl;
        cin >> choice;
        if ((choice == "1") || (choice == "2") || (choice == "3")) {
            break;
        } else {
            cout << "Please choose a valid option." << endl;
        }
    }

    vector<Node*> hospitals;
    vector<Node*> students;
    pair<vector<Node*>, vector<Node*>> data;

    if (choice == "1") {
        data = read_manually();
        hospitals = data.first;
        students = data.second;
    } else if (choice == "2") {
        data = read_from_file();
        hospitals = data.first;
        students = data.second;
    } else {
        data = generate_data();
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

    if (run_matching) {
        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

        Matcher m(hospitals, students);
        vector<pair<Node *, Node *>> matches = m.match();
        write_to_file(matches);
        // DEBUG: Print out the matches.
        /*for (auto match : matches) {
            match.first->print();
        }*/

        chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();

        chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(end - start);

        cout << "Matching " + to_string(matches.size()) + " hospitals to students took "
             << time_span.count() << " seconds." << endl;

        // This code will only execute if both engines are run at once.
        if (run_verifier) {
            start = chrono::high_resolution_clock::now();

            Verifier v(matches);
            cout << v.verify() << endl;

            end = chrono::high_resolution_clock::now();

            time_span = chrono::duration_cast<chrono::duration<double>>(end - start);

            cout << "Verifying " + to_string(matches.size()) + " matches took "
                 << time_span.count() << " seconds." << endl;
        }
    }

    if (run_verifier) {
        choice.clear();
        while (true) {
            cout << "How will you input the matches about the hospitals and students?" << endl;
            cout << "1. Manually" << endl;
            cout << "2. Read a file" << endl;
            cout << "3. Randomly generate matches" << endl;
            cin >> choice;
            if ((choice == "1") || (choice == "2") || (choice == "3")) {
                break;
            } else {
                cout << "Please choose a valid option." << endl;
            }
        }

        vector<pair<Node*, Node*>> matches;

        if (choice == "1") {
            matches = read_matches_manually(data);
        } else if (choice == "2") {
            matches = read_matches_file(data);
        } else {
            matches = generate_matches(data);
        }

        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

        Verifier v(matches);
        cout << v.verify() << endl;

        chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();

        chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(end - start);

        cout << "Verifying " + to_string(matches.size()) + " matches took "
             << time_span.count() << " seconds." << endl;
    }

    // Deallocate the hospitals and students.
    for (int i = 0; i < hospitals.size(); i++) {
        delete hospitals[i];
        delete students[i];
    }
    return 0;
}
