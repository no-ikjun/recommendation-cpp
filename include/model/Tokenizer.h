#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <regex>
#include <string>

std::vector<std::string> tokenize(
  std::string& string, 
  char delimiter = ' ', // use space as default delimiter
  std::regex ignore = std::regex(".*[^a-zA-Z0-9].*") // ignore any non-alphabetic words or empty word
);

#endif