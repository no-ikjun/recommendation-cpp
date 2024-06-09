#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

class Vocabulary {
public:
  Vocabulary();
  std::unordered_map<std::string, int> getVocab();
  int getVocabSize();
  int getId(std::string);
  void create(std::filesystem::path, size_t maxVocabSize);
  void saveAs(std::filesystem::path);
  void loadFrom(std::filesystem::path);
private:
  std::unordered_map<std::string, int> vocab;
};

#endif