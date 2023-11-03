#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void sortLine(std::istream & is) {
  std::string str;
  std::vector<std::string> lines;
  while (std::getline(is, str)) {
    lines.push_back(str);
  }
  // checking for errors
  if (is.good() != 1 && is.eof() != 1) {
    std::cerr << "Reading data error" << std::endl;
    exit(EXIT_FAILURE);
  }
  //sortlines
  std::sort(lines.begin(), lines.end());
  for (std::vector<std::string>::iterator i = lines.begin(); i != lines.end(); ++i) {
    std::cout << *i << std::endl;
  }
}
int main(int argc, char ** argv) {
  // std::cout << "CHECKING Main" << std::endl;
  if (argc == 1) {
    sortLine(std::cin);
  }
  if (argc >= 2) {
    // std::cout << "CHECKING 0" << std::endl;
    for (int i = 1; i < argc; i++) {
      // std::cout << "CHECKING 1" << std::endl;
      std::ifstream file(argv[i]);
      if (file.fail()) {
        std::cerr << "Cannot open file" << std::endl;
        return EXIT_FAILURE;
      }
      // std::cout << "CHECKING" << std::endl;
      sortLine(file);
      file.close();
    }
  }
  return EXIT_SUCCESS;
}
