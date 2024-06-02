#include "../../include/recommender/Tokenizer.h"
#include "../../include/recommender/Vocabulary.h"

#include <unordered_map>
#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>
#include <vector>
#include <exception>
#include <utility> // pair 
#include <algorithm>

Vocabulary::Vocabulary(int maxVocabSize) {
  this->maxVocabSize = maxVocabSize;
}

std::unordered_map<std::string, int> Vocabulary::getVocab() {
  return this->vocab;
}

int Vocabulary::getId(std::string token) {
  try{
    return this->vocab.at(token);
  } catch(const std::out_of_range &e) {
    return 0;
  }
}

void Vocabulary::createVocabulary(std::filesystem::path datasetPath) {
  std::cout << "@Vocabulary" << std::endl;

  std::cout
    << "  Currently at " << std::filesystem::current_path()
  << std::endl;

  std::cout 
    << "  Loading text dataset from " << datasetPath.relative_path() 
    << " to create vocabulary..."
  << std::endl;

  if(!std::filesystem::exists(datasetPath)) {
    std::cerr 
      << "    Cannot find dataset directory: " << datasetPath
    << std::endl;
    return;
  }

  std::unordered_map<std::string, int> histogram;
  std::string line;
  for(auto const& entry: std::filesystem::directory_iterator{datasetPath}) {
    std::filesystem::path datafile = entry.path();      
    std::ifstream file(datafile);

    std::cout << "    Opening " << datafile << "..." << std::endl;

    if (file.is_open()) {
      std::cout << "      Tokenizing... " << std::endl;
      while (std::getline(file, line)) {
        std::vector<std::string> tokens = tokenize(line);
        for(const std::string token: tokens) {
          auto it = histogram.find(token);
          if(it != histogram.end()) {
            ++histogram[token];
          } else {
            histogram[token] = 1;
          }
        }
      }
      std::cout << "      Tokenization completed" << std::endl;

      std::cout << "    Closing " << datafile << "..." << std::endl;
      file.close();

      std::cout << "\r                          \r";
    } else {
      std::cerr << "    Cannot open data file: " << datafile << std::endl;
      return;
    }
  }
  
  std::cout 
    << "  Vocabulary of total " << histogram.size() << " tokens is created"
  << std::endl;

  if(histogram.size() > this->maxVocabSize) {
    std::cout 
      << "  Removing " << histogram.size() - this->maxVocabSize 
      << " tokens from the vocabulary to match the maximum vocabulary size " << this->maxVocabSize
    << std::endl;

    std::vector<std::pair<std::string, int>> vectorized_vocab(histogram.begin(), histogram.end());
    std::sort(vectorized_vocab.begin(), vectorized_vocab, [](std::pair<std::string, int> a, std::pair<std::string, int> b) -> bool {return a.second < b.second});
    // TODO: 
  }
  
}