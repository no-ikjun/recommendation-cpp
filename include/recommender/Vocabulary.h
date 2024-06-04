#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

class Vocabulary {
public:
  Vocabulary(int maxVocabSize);
  std::unordered_map<std::string, int> getVocab();
  int getVocabSize();
  int getId(std::string);
  void createVocabulary(std::filesystem::path);
  std::vector<bool> one_hot_encode();
private:
  int maxVocabSize;
  std::unordered_map<std::string, int> vocab;
};

#endif