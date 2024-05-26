#include "../include/model/Tokenizer.h"

#include <sstream>
#include <string>
#include <string>
#include <regex>

std::vector<std::string> tokenize (
  std::string& string, char delimiter, std::regex ignore
) {
  std::vector<std::string> tokens;
  std::stringstream ss(string);
  std::string temp;

  while (getline(ss, temp, delimiter)) {
    if(std::regex_search(temp, ignore)) {
      continue;
    }
    tokens.push_back(temp);
  }
  return tokens;
}