#include "optable.h"
#include <iostream>
#include <string>
#include <unordered_map>
optable::optable() {}
int optable::getOpcode(std::string s) { return table.at(s).first; }

int optable::getInstructionFormat(std::string s) {
  return table.at(s).second;
}

;
