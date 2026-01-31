//
// Created by roybo on 1/30/2026.
//

#include "utilities.h"

pair<vector<Node*>, vector<Node*>> read_manually() {
    // Get how many students and hospitals need to be matched.
    cout << "How many hospitals and students are there?" << endl;
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
    cout << "Generating hospital preferences..." << endl;
    for (int i = 0; i < n; i++) {
        Node* h = hospitals[i];
        cout << "Please enter " << n << " integers from 1 to " << n << " to indicate hospital " << i + 1
             << "'s student preferences." << endl;
        for (int j = 0; j < students.size(); j++) {
            int s = 0;
            cin >> s;
            h->add_preference(students[s - 1]);
        }
    }
    // Generate the Students' preference lists.
    cout << "Generating student preferences..." << endl;
    for (int i = 0; i < n; i++) {
        Node* s = students[i];
        cout << "Please enter " << n << " integers from 1 to " << n << " to indicate student " << i + 1
             << "'s hospital preferences." << endl;
        for (int j = 0; j < hospitals.size(); j++) {
            int h = 0;
            cin >> h;
            s->add_preference(hospitals[h - 1]);
        }
    }

    return {hospitals, students};
}

vector<int> line_to_numbers(const string& line) {
    vector<int> numbers;
    string substr;
    for (auto c : line) {
        if ((c == ' ') || (c == '\n')) {
            numbers.push_back(stoi(substr));
            substr.clear();
        } else {
            substr += c;
        }
    }
    if (!substr.empty()) {
        numbers.push_back(stoi(substr));
    }
    return numbers;
}

pair<vector<Node*>, vector<Node*>> read_from_file() {
    string filename;
    ifstream file;
    while (true) {
        cout << "Enter the name of the file to read in:  (\"example.txt\")" << endl;
        cin >> filename;
        file.open(filename);
        if (file.good()) {
            break;
        } else {
            cout << "ERROR: File not found." << endl;
        }
    }

    string line;
    getline(file, line);
    int n = line_to_numbers(line)[0];

    // Create the hospitals and students.
    vector<Node*> hospitals;
    vector<Node*> students;
    for (int i = 1; i <= n; i++) {
        hospitals.push_back(new Node("Hospital", i));
        students.push_back(new Node("Student", i));
    }
    for (int i = 0; i < n; i++) {
        Node* h = hospitals[i];
        getline(file, line);
        vector<int> numbers = line_to_numbers(line);
        for (int j = 0; j < students.size(); j++) {
            h->add_preference(students[numbers[j] - 1]);
        }
    }
    for (int i = 0; i < n; i++) {
        Node* s = students[i];
        getline(file, line);
        vector<int> numbers = line_to_numbers(line);
        for (int j = 0; j < hospitals.size(); j++) {
            s->add_preference(hospitals[numbers[j] - 1]);
        }
    }

    file.close();

    return {hospitals, students};
}

pair<vector<Node*>, vector<Node*>> generate_data() {
    cout << "Enter an integer how many hospitals and students should be generated:" << endl;
    int n = 0;
    cin >> n;
    srand((unsigned) time(nullptr));

    // Create the hospitals and students.
    vector<Node*> hospitals;
    vector<Node*> students;
    for (int i = 1; i <= n; i++) {
        hospitals.push_back(new Node("Hospital", i));
        students.push_back(new Node("Student", i));
    }
    for (int i = 0; i < n; i++) {
        Node* h = hospitals[i];
        vector<int> number_pool;
        for (int j = 1; j <= n; j++) {
            number_pool.push_back(j);
        }
        queue<int> numbers;
        while (!number_pool.empty()) {
            int j = rand() % number_pool.size();
            numbers.push(number_pool[j]);
            number_pool.erase(number_pool.begin() + j);
        }
        int number = 0;
        for (int j = 0; j < students.size(); j++) {
            number = numbers.front();
            h->add_preference(students[number - 1]);
            numbers.pop();
        }
    }
    for (int i = 0; i < n; i++) {
        Node* s = students[i];
        vector<int> number_pool;
        for (int j = 1; j <= n; j++) {
            number_pool.push_back(j);
        }
        queue<int> numbers;
        while (!number_pool.empty()) {
            int j = rand() % number_pool.size();
            numbers.push(number_pool[j]);
            number_pool.erase(number_pool.begin() + j);
        }
        int number = 0;
        for (int j = 0; j < hospitals.size(); j++) {
            number = numbers.front();
            s->add_preference(hospitals[number - 1]);
            numbers.pop();
        }
    }

    return {hospitals, students};
}

void write_to_file(const vector<pair<Node*, Node*>>& nodes) {
    string filename = "output.txt";
    ofstream file(filename);
    for (auto node_pair : nodes) {
        file << node_pair.first->get_id() << ' ' << node_pair.second->get_id() << endl;
    }
    cout << "Matches written to \"" + filename + "\"" << endl;
}

vector<pair<Node*, Node*>> read_matches_manually(const pair<vector<Node*>, vector<Node*>>& data) {
    vector<pair<Node*, Node*>> matches;
    vector<Node*> hospitals = data.first;
    vector<Node*> students = data.second;

    cout << "Type " << hospitals.size() << " pairs of two integers between 1 and "
         << hospitals.size() << "." << endl;
    for (int i = 0; i < hospitals.size(); i++) {
        cout << "Pair " << i + 1 << "/" << hospitals.size() << ": ";
        int h_id = 0;
        int s_id = 0;
        cin >> h_id;
        cin >> s_id;
        Node* h = hospitals[h_id - 1];
        Node* s = students[s_id - 1];

        h->set_assigned(s);
        s->set_assigned(h);
        matches.emplace_back(h, s);
    }

    return matches;
}

vector<pair<Node*, Node*>> read_matches_file(const pair<vector<Node*>, vector<Node*>>& data) {
    vector<pair<Node*, Node*>> matches;
    vector<Node*> hospitals = data.first;
    vector<Node*> students = data.second;

    string filename;
    ifstream file;
    while (true) {
        cout << "Enter the name of the file to read in:  (\"example.txt\")" << endl;
        cin >> filename;
        file.open(filename);
        if (file.good()) {
            break;
        } else {
            cout << "ERROR: File not found." << endl;
        }
    }

    string line;
    while (getline(file, line)) {
        vector<int> nums = line_to_numbers(line);

        int h_id = nums[0];
        int s_id = nums[1];
        Node* h = hospitals[h_id - 1];
        Node* s = students[s_id - 1];

        h->set_assigned(s);
        s->set_assigned(h);
        matches.emplace_back(h, s);
    }

    file.close();

    return matches;
}

vector<pair<Node*, Node*>> generate_matches(const pair<vector<Node*>, vector<Node*>>& data) {
    vector<pair<Node*, Node*>> matches;
    vector<Node*> hospitals = data.first;
    vector<Node*> students = data.second;

    srand((unsigned) time(nullptr));
    int n = hospitals.size();

    vector<int> number_pool;
    for (int j = 1; j <= n; j++) {
        number_pool.push_back(j);
    }
    queue<int> h_numbers;
    while (!number_pool.empty()) {
        int j = rand() % number_pool.size();
        h_numbers.push(number_pool[j]);
        number_pool.erase(number_pool.begin() + j);
    }

    for (int j = 1; j <= n; j++) {
        number_pool.push_back(j);
    }
    queue<int> s_numbers;
    while (!number_pool.empty()) {
        int j = rand() % number_pool.size();
        s_numbers.push(number_pool[j]);
        number_pool.erase(number_pool.begin() + j);
    }

    while (!h_numbers.empty() && !s_numbers.empty()) {
        int h_id = h_numbers.front();
        int s_id = s_numbers.front();
        Node* h = hospitals[h_id - 1];
        Node* s = students[s_id - 1];

        h->set_assigned(s);
        s->set_assigned(h);
        matches.emplace_back(h, s);

        h_numbers.pop();
        s_numbers.pop();
    }

    return matches;
}