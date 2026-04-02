// pass2.cpp
// Generates listing file using SYMTAB and OPTAB
#include "optable.h"
#include <fstream>
#include <iostream>

optable table;

void pass2(const std::string &filename) {
  std::ifstream infile(filename);
  if (!infile) {
    std::cerr << "Error opening symtab" << std::endl;
    exit(1);
  }
  while
}
