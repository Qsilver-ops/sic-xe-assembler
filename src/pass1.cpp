// pass1.cpp
// Handles SYMTAB creation and LOCCTR tracking
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

// Symbol table
unordered_map<string, int> SYMTAB;

void pass1(const string& filename) {

    ifstream infile(filename);
    if (!infile) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    int LOCCTR = 0;

    while (getline(infile, line)) {

        // skip empty lines
        if (line.empty()) continue;

        string label = "";
        string opcode = "";
        string operand = "";

        stringstream ss(line);

        // if line starts with space/tab, there is no label
        if (isspace(line[0])) {
            ss >> opcode >> operand;
        } else {
            ss >> label >> opcode >> operand;
        }

        // print what we parsed
        cout << "LABEL: " << label
             << " OPCODE: " << opcode
             << " OPERAND: " << operand << endl;

        // add label to SYMTAB only if it exists
        if (!label.empty()) {
            SYMTAB[label] = LOCCTR;
        }

        // temporary simple LOCCTR update
        LOCCTR += 3;
    }

    infile.close();
}
