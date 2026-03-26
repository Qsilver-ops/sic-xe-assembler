// pass1.cpp
// Handles SYMTAB creation and LOCCTR tracking
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cctype>

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

        // Handle START directive (initialize LOCCTR)
        if (opcode == "START") {
            LOCCTR = stoi(operand);
            cout << "LOCCTR: " << LOCCTR
                 << " LABEL: " << label
                 << " OPCODE: " << opcode
                 << " OPERAND: " << operand << endl;
            continue;
        }

        // print what we parsed (now includes LOCCTR)
        cout << "LOCCTR: " << LOCCTR
             << " LABEL: " << label
             << " OPCODE: " << opcode
             << " OPERAND: " << operand << endl;

        // add label to SYMTAB only if it exists
        if (!label.empty()) {
            SYMTAB[label] = LOCCTR;
        }

        // ----- LOCCTR update rules -----

        if (opcode == "WORD") {
            LOCCTR += 3;
        }
        else if (opcode == "RESW") {
            LOCCTR += 3 * stoi(operand);
        }
        else if (opcode == "RESB") {
            LOCCTR += stoi(operand);
        }
        else if (opcode == "BYTE") {
            if (operand[0] == 'C') {
                // C'EOF' → number of characters
                LOCCTR += operand.length() - 3;
            }
            else if (operand[0] == 'X') {
                // X'F1' → half number of hex digits
                LOCCTR += (operand.length() - 3) / 2;
            }
        }
        else if (opcode == "END") {
            break;
        }
        else {
            // normal instruction (temporary assumption)
            LOCCTR += 3;
        }
    }

    infile.close();
}

        // temporary simple LOCCTR update
        LOCCTR += 3;
    }

    infile.close();

   // check labels being stored
    cout << "\nSYMTAB:\n";
    for (const auto& entry : SYMTAB) {
        cout << entry.first << " -> " << entry.second << endl;
    }
}
