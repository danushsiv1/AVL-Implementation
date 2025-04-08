#include <iostream>
#include <fstream>
#include <string>
#include "AVLTree.h"
using namespace std;

int main(int argc, char* argv[]){
  if(argc != 3){
    std::cerr << "Usage: " << argv[0] << " <input-file> <output-file>\n";
    return 1;
  }

  std::ifstream input(argv[1]);
  std::ofstream output(argv[2]);
  if(!input || !output){
    std::cerr << "Error opening files.\n";
    return 1;
  }

  // Initialize AVLTree
  AVLTree tree;
  std::string command;
  std::string value1, value2;

  // Reads command
  while(input >> command){
    if(command == "i"){
      input >> value1;
      tree.insert(value1);
    } else if (command == "r"){
      input >> value1 >> value2;
      int result = tree.rangeSearch(value1, value2);
      output << result << "\n";
			output.flush();
    }
  }
  return 0;
}