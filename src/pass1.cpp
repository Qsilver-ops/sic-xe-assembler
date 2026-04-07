// pass1.cpp
// Handles SYMTAB creation and LOCCTR tracking
#include "optable.h"
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;

// Symbol table (preserves insertion order)
vector<pair<string, int>> pass1(const string &filename) {

  optable table;

  vector<pair<string, int>> SYMTAB;

  ifstream infile(filename);
  if (!infile) {
    cerr << "Error opening file: " << filename << endl;
  }

  // create listing file (.l)
  string listname = filename;
  size_t dot2 = listname.find_last_of('.');
  if (dot2 != string::npos) {
    listname = listname.substr(0, dot2);
  }
  listname += ".l";

  ofstream listfile(listname);
  if (!listfile) {
    cerr << "Error creating listing file: " << listname << endl;
  }

  string line;
  int LOCCTR = 0;

  while (getline(infile, line)) {

    // skip empty lines
    if (line.empty())
      continue;

    string label = "";
    string opcode = "";
    string operand = "";

    stringstream ss(line);

    // if line starts with space/tab, there is no label
    if (isspace(line[0]) || !isalpha(line[0])) {
      ss >> opcode >> operand;
    } else {
      ss >> label >> opcode >> operand;
    }

    // Handle START directive (initialize LOCCTR)
    if (opcode == "START") {
      LOCCTR = stoi(operand);
      cout << "LOCCTR: " << hex << LOCCTR << " LABEL: " << label
           << " OPCODE: " << opcode << " OPERAND: " << operand << endl;

      listfile << hex << LOCCTR << "\t" << line << endl;
      continue;
    }

    // print parsed line with LOCCTR
    cout << "LOCCTR: " << hex << LOCCTR << " LABEL: " << label
         << " OPCODE: " << opcode << " OPERAND: " << operand << endl;

    // write to listing file
    listfile << hex << LOCCTR << "\t" << line << endl;

    // add label to SYMTAB only if it exists
    if (!label.empty()) {
      SYMTAB.push_back({label, LOCCTR});
    }

    // LOCCTR update rules

    if (opcode == "WORD") {
      LOCCTR += 3;
    } else if (opcode == "RESW") {
      LOCCTR += 3 * stoi(operand);
    } else if (opcode == "RESB") {
      LOCCTR += stoi(operand);
    } else if (opcode == "BASE") {
      LOCCTR += 0;
    } else if (opcode == "*") {
      // literal pool entry — calculate size same as BYTE
      string op = operand;
      if (op[0] == '=') {
        op = op.substr(1);
      }
      if (op[0] == 'C') {
        LOCCTR += op.length() - 3;
      } else if (op[0] == 'X') {
        LOCCTR += (op.length() - 3) / 2;
      }
    }

    else if (opcode == "BYTE") {
      if (operand[0] == 'C') {
        // C'EOF' → number of characters
        LOCCTR += operand.length() - 3;
      } else if (operand[0] == 'X') {
        // X'F1' → half number of hex digits
        LOCCTR += (operand.length() - 3) / 2;
      }
    } else if (opcode == "END") {
      break;
    } else {
      // normal instruction (temporary assumption)
      int instructionFormat = table.getInstructionFormat(opcode);
      if (opcode[0] == '+') {
        instructionFormat = 4;
      }
      if (instructionFormat == -1) {
        // unrecognized opcode, skip or handle error
        cerr << "Warning: unknown opcode '" << opcode << "' at LOCCTR " << hex
             << LOCCTR << endl;
      } else {
        LOCCTR += instructionFormat;
      }
    }
  }

  infile.close();
  listfile.close();

  // print SYMTAB to console
  cout << "\nSYMTAB:\n";
  for (const auto &entry : SYMTAB) {
    cout << entry.first << " -> " << hex << entry.second << endl;
  }

  //  write SYMTAB to .st file
  string outname = filename;
  size_t dot = outname.find_last_of('.');
  if (dot != string::npos) {
    outname = outname.substr(0, dot);
  }
  outname += ".st";

  ofstream symfile(outname);
  if (!symfile) {
    cerr << "Error creating SYMTAB file: " << outname << endl;
  }

  symfile << "SYMTAB:\n";
  for (const auto &entry : SYMTAB) {
    symfile << left << setw(10) << entry.first << " " << hex << entry.second
            << endl;
  }

  symfile.close();
  return SYMTAB;
}
