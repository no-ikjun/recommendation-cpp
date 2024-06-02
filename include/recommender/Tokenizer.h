#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <sstream>
#include <string>
#include <string>
#include <regex>

inline std::vector<std::string> tokenize (
  std::string& string, 
  char delimiter = ' ', 
  std::regex ignore = std::regex("[^a-zA-Z0-9]") // ignore any token with (non-alphabetic or non-number) characters
) {
  std::vector<std::string> tokens;
  std::stringstream ss(string);
  std::string temp;

  while (getline(ss, temp, delimiter)) {
    if(std::regex_search(temp, ignore) || temp == "\0") {
      continue;
    }
    tokens.push_back(temp);
  }
  return tokens;
}

#endif