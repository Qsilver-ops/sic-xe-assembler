// main.cpp
// CS530 Project 2 - SIC/XE Assembler
#include <iostream>
#include <fstream>
#include <string>


int main(int argc, char* argv[]) {

    std::cout << "LXE assembler starting...\n";

    if(argc < 2){
        std::cout << "Usage: ./lxe file1.sic file2.sic\n";
        return 1;
    }


    for(int i = 1; i < argc; i++){

    std::ifstream infile(argv[i]);

    if(!infile){
        std::cout << "Error opening file: " << argv[i] << std::endl;
        continue;
    }

    std::cout << "Processing file: " << argv[i] << std::endl;

    std::string line;

    while(std::getline(infile, line)){
        std::cout << line << std::endl;
    }

    infile.close();
}

    return 0;
}
