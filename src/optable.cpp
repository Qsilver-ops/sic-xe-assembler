#include "optable.h"
#include <iostream>
#include <string>
#include <unordered_map>
optable::optable() {}
int optable::getOpcode(std::string s) {
  if (table.count(s) > 0) {
    return table.at(s).first;
  }
  return -1;
}

int optable::getInstructionFormat(std::string s) {
  if (table.count(s) > 0) {
    return table.at(s).second;
  }
  return -1;
}
