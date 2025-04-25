#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Problem {
    string title;
    string difficulty;
    bool solved;
};

// Function declarations
void showMenu();
void addProblem(vector<Problem>& problems);
void listProblems(const vector<Problem>& problems);
void markAsSolved(vector<Problem>& problems);
void loadFromFile(vector<Problem>& problems, const string& filename);
void saveToFile(const vector<Problem>& problems, const string& filename);

int main() {
    vector<Problem> problems;
    string filename = "problems.txt";

    // Load from file
    loadFromFile(problems, filename);

    int choice;
    do {
        showMenu();
        cin >> choice;
        cin.ignore(); // clear newline

        switch (choice) {
            case 1: addProblem(problems); break;
            case 2: listProblems(problems); break;
            case 3: markAsSolved(problems); break;
            case 4: saveToFile(problems, filename); cout << "Saved. Exiting...\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 4);

    return 0;
}
void showMenu() {
    cout << "\n--- DSA Problem Tracker ---\n";
    cout << "1. Add Problem\n";
    cout << "2. View All Problems\n";
    cout << "3. Mark Problem as Solved\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}
void addProblem(vector<Problem>& problems) {
    Problem p;
    cout << "Enter problem title: ";
    getline(cin, p.title);

    cout << "Enter difficulty (Easy/Medium/Hard): ";
    getline(cin, p.difficulty);

    p.solved = false; // Default to unsolved

    problems.push_back(p);
    cout << "Problem added!\n";
}
void listProblems(const vector<Problem>& problems) {
    if (problems.empty()) {
        cout << "No problems added yet.\n";
        return;
    }

    cout << "\n--- Problem List ---\n";
    for (size_t i = 0; i < problems.size(); ++i) {
        cout << i + 1 << ". " << problems[i].title 
             << " | " << problems[i].difficulty 
             << " | " << (problems[i].solved ? "Solved" : "Unsolved") << "\n";
    }
}
void markAsSolved(vector<Problem>& problems) {
    listProblems(problems);

    if (problems.empty()) return;

    cout << "Enter the number of the problem to mark as solved: ";
    int index;
    cin >> index;
    cin.ignore();

    if (index < 1 || index > problems.size()) {
        cout << "Invalid problem number.\n";
    } else {
        problems[index - 1].solved = true;
        cout << "Marked as solved!\n";
    }
}
void saveToFile(const vector<Problem>& problems, const string& filename) {
    ofstream outFile(filename);

    if (!outFile) {
        cout << "Error saving to file.\n";
        return;
    }

    for (const auto& p : problems) {
        outFile << p.title << "|" << p.difficulty << "|" << p.solved << "\n";
    }

    outFile.close();
}
void loadFromFile(vector<Problem>& problems, const string& filename) {
    ifstream inFile(filename);

    if (!inFile) {
        // File doesn't exist yet – first run
        return;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string title, difficulty, solvedStr;

        getline(ss, title, '|');
        getline(ss, difficulty, '|');
        getline(ss, solvedStr);

        Problem p;
        p.title = title;
        p.difficulty = difficulty;
        p.solved = (solvedStr == "1");

        problems.push_back(p);
    }

    inFile.close();
}
