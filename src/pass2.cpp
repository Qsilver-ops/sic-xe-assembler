// pass2.cpp
// Generates listing file using SYMTAB and OPTAB
#include "optable.h"
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

optable table;

void pass2(const std::string &filename,
           const std::vector<std::pair<std::string, int>> &SYMTAB) {
  std::ifstream infile(filename);
  if (!infile) {
    std::cerr << "Error opening source file: " << filename << std::endl;
    return;
  }

  std::string outname = filename;
  size_t dot = outname.find_last_of('.');
  if (dot != std::string::npos) {
    outname = outname.substr(0, dot);
  }
  outname += ".l";

  std::ofstream outFile(outname, std::ios::app); // append for now
  if (!outFile.is_open()) {
    std::cerr << "Error opening listing file: " << outname << std::endl;
    return;
  }

  std::string line;
  std::cout << "starting pass2" << std::endl;

  while (std::getline(infile, line)) {
    if (line.empty()) {
      continue;
    }

    std::string label = "";
    std::string opcode = "";
    std::string operand = "";

    std::stringstream ss(line);

    // same parsing logic as pass1
    if (std::isspace(static_cast<unsigned char>(line[0])) || !std::isalpha(static_cast<unsigned char>(line[0]))) {
      ss >> opcode >> operand;
    } else {
      ss >> label >> opcode >> operand;
    }

    bool format4 = false;
    std::string mnemonic = opcode;

    if (!opcode.empty() && opcode[0] == '+') {
      format4 = true;
      mnemonic = opcode.substr(1);
    }

    std::cout << "current line: " << line << std::endl;
    std::cout << "label: " << label << std::endl;
    std::cout << "opcode: " << opcode << std::endl;
    std::cout << "operand: " << operand << std::endl;
    std::cout << "mnemonic: " << mnemonic << std::endl;

    // assembler directives are not real machine opcodes
    if (mnemonic == "START" || mnemonic == "END" || mnemonic == "WORD" ||
        mnemonic == "RESW" || mnemonic == "RESB" || mnemonic == "BYTE") {
      std::cout << "directive: " << mnemonic << std::endl;
      continue;
    }

    int opcodeValue = table.getOpcode(mnemonic);
    int instructionFormat = table.getInstructionFormat(mnemonic);

    if (format4) {
      instructionFormat = 4;
    }

    std::cout << "opcode value: " << std::hex << opcodeValue << std::endl;
    std::cout << "instruction format: " << std::dec << instructionFormat << std::endl;

    if (opcodeValue == -1) {
      std::cout << "invalid opcode: " << mnemonic << std::endl;
      continue;
    }

    unsigned int objectCode = static_cast<unsigned int>(opcodeValue);
    std::cout << "object code (partial): " << std::hex << objectCode << std::endl;
  }

  infile.close();
  outFile.close();
}
