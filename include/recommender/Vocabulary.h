#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

class Vocabulary {
public:
  std::unordered_map<std::string, int> getVocab();
  void createVocabulary(std::filesystem::path);
private:
  std::unordered_map<std::string, int> vocab;
};

#endif