// pass2.cpp
// Generates listing file using SYMTAB and OPTAB
#include "optable.h"
#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <ostream>
#include <vector>

optable table;

void pass2(const std::string &filename,
           std::vector<std::pair<std::string, int>> SYMTAB) {
  std::ifstream infile(filename);
  if (!infile) {
    std::cerr << "Error opening symtab" << std::endl;
  }

  std::ofstream outFile("test.l");

  if (!outFile.is_open()) {
    std::cerr << "Error opening file" << std::endl;
  }

  std::string line;
  std::cout << "starting pass2" << std::endl;
  while (std::getline(infile, line)) {
    std::cout << "current line: " << line << std::endl;
    std::uint32_t objectCode = 0;
    std::string mnemonic;
    bool format4 = false;
    int start = 10; // mnemonics start at 9 is they are format 4, otherwise they
                   // start at 10
    int end = 10;
    if(line[9] == '+'){
      format4 = true;
    }
    while (!isspace(line[end]) && end < (int)line.length()) {
      end++;
    }

    mnemonic = line.substr(start, end - start);
    std::cout << "mnemonic: " << mnemonic << std::endl;
    std::cout << "opcode: " << std::hex << table.getOpcode(mnemonic) << std::endl;

    objectCode = table.getOpcode(mnemonic);
    int instructionFormat = table.getInstructionFormat(mnemonic);
    if (format4) {
      instructionFormat = 4;
    }

    std::cout << "instruction format: " << std::dec << instructionFormat << std::endl;
    objectCode = table.getOpcode(mnemonic);
    if(format4){
      objectCode = objectCode << 24;
    }
    objectCode = objectCode << 16;

    std::cout << "object code: " << std::hex << objectCode << std::endl;


    /*
    for (int i = 0; i < line.length(); i++){

  }
  */
  }
}
