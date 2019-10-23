#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char ** argv) {
  std::ifstream f;
  std::string strings;

  std::vector<std::string> str;

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
      f.open(argv[i]);
      if (f.fail()) {
        std::cerr << "No File" << std::endl;
        exit(EXIT_FAILURE);
      }
      while (!f.eof()) {
        std::getline(f, strings);
        str.push_back(strings);
      }

      std::sort(str.begin(), str.end());

      for (size_t i = 0; i < str.size(); i++) {
        std::cout << str[i] << std::endl;
      }

      str.clear();
      f.close();
    }
  }

  return EXIT_SUCCESS;
}
