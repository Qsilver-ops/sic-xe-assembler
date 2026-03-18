// main.cpp
// CS530 Project 2 - SIC/XE Assembler
#include <iostream>
#include <fstream>
#include <string>

void pass1(const std::string& filename);

int main(int argc, char* argv[]) {

    std::cout << "LXE assembler starting...\n";

    if(argc < 2){
        std::cout << "Usage: ./lxe file1.sic file2.sic\n";
        return 1;
    }

    for(int i = 1; i < argc; i++){
        pass1(argv[i]);
    }

    return 0;
}
