#include "../include/model/Tokenizer.h"
#include "../../include/model/Vocabulary.h"

#include <unordered_map>
#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>
#include <vector>

void Vocabulary::createVocabulary() {
  std::cout << "@Vocabulary" << std::endl;

  std::cout
    << "  Currently at " << std::filesystem::current_path()
  << std::endl;

  std::filesystem::path datasetPath = "./dataset_sm"; 

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

  std::string line;
  for(auto const& entry: std::filesystem::directory_iterator{datasetPath}) {
    std::filesystem::path datafile = entry.path();      
    std::ifstream file(datafile);

    std::cout << "    Opening " << datafile << "..." << std::endl;

    if (file.is_open()) {
      std::cout << "      Tokenizing... " << std::endl;

      int i = 1;
      while (std::getline(file, line)) {
        std::vector<std::string> tokens = tokenize(line);
        for(const std::string token: tokens) {
          this->vocab[token] = 0;
          this->vocab[token] = this->vocab.size();
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
    << "  Vocabulary of total " << this->vocab.size() << " tokens is created"
  << std::endl;
}