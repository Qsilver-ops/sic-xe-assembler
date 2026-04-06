// main.cpp
// CS530 Project 2 - SIC/XE Assembler
#include "optable.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::pair<std::string, int>> pass1(const std::string &filename);
void pass2(const std::string &filename,
           const std::vector<std::pair<std::string, int>> &SYMTAB);

int main(int argc, char *argv[]) {

  std::cout << "LXE assembler starting...\n";

  if (argc < 2) {
    std::cout << "Usage: ./lxe file1.sic file2.sic\n";
    return 1;
  }

  std::vector<std::pair<std::string, int>> SYMTAB;
  for (int i = 1; i < argc; i++) {
    SYMTAB = pass1(argv[i]);
    pass2(argv[i], SYMTAB);
  }
  for (size_t i = 0; i < SYMTAB.size(); i++) {
    std::cout << i << ":" << SYMTAB.at(i).first ;
    std::cout << ", " << SYMTAB.at(i).second << std::endl;
  }

  return 0;
}
