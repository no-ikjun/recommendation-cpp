#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

class Vocabulary {
public:
  void createVocabulary();
private:
  std::unordered_map<std::string, long> vocab;
};

#endif