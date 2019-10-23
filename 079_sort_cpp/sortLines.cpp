#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char ** argv) {
  std::ifstream read;
  std::string strings;

  std::vector<std::string> str;
  if (argc < 1) {
    exit(EXIT_FAILURE);
  }
  if (argc == 1) {
    while (!std::cin.eof()) {
      std::getline(std::cin, strings);

      str.push_back(strings);

      std::sort(str.begin(), str.end());

      for (size_t i = 0; i < str.size(); i++) {
        std::cout << str[i] << std::endl;
      }

      str.clear();
    }
  }

  else {
    for (int i = 1; i < argc; i++) {
      read.open(argv[i]);
      if (read.fail()) {
        exit(EXIT_FAILURE);
      }
      while (!read.eof()) {
        std::getline(read, strings);
        str.push_back(strings);
      }

      std::sort(str.begin(), str.end());

      for (size_t i = 0; i < str.size(); i++) {
        std::cout << str[i] << std::endl;
      }

      str.clear();
      read.close();
    }
  }

  return EXIT_SUCCESS;
}
