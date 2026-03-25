// main.cpp
// CS530 Project 2 - SIC/XE Assembler
#include "optable.h"
#include <fstream>
#include <iostream>
#include <string>

void pass1(const std::string &filename);

int main(int argc, char *argv[]) {
  optable table;
  int opcode = table.getOpcode("ADD");
  std::cout << std::hex <<opcode << std::endl;
  std::cout << std::hex <<table.getOpcode("STA")<< std::endl;
  std::cout << std::hex << table.getOpcode("LDA") << std::endl;


  std::cout << "LXE assembler starting...\n";

  if (argc < 2) {
    std::cout << "Usage: ./lxe file1.sic file2.sic\n";
    return 1;
  }

  for (int i = 1; i < argc; i++) {
    pass1(argv[i]);
  }

  return 0;
}
