#include "../../include/recommender/Word2Vec.h"
#include "../../include/recommender/Tokenizer.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility> // pair

Word2Vec::Word2Vec(int dimension, Vocabulary& vocabulary) {
  this->vocabulary = vocabulary;
}

std::vector<std::pair<int, int>> Word2Vec::getCBOW() {
  return this->CBOW;
}

void Word2Vec::generateCBOW(std::filesystem::path datasetPath, int contextLength) {
  std::cout << "@Word2Vec" << std::endl;

  std::cout
    << "  Currently at " << std::filesystem::current_path()
  << std::endl;

  std::cout 
    << "  Loading text dataset from " << datasetPath.relative_path() 
    << " to create continuous bag of words..."
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
      std::cout << "      Generating continuous bag of words... " << std::endl;
      while (std::getline(file, line)) {
        std::vector<std::string> tokens = tokenize(line);
        std::vector<int> mapped_tokens;
        for(auto token: tokens) {
          mapped_tokens.push_back(this->vocabulary.getId(token));
        }
        std::vector<int> context_bow;
        for(auto center_it = begin(mapped_tokens); center_it != end(mapped_tokens); ++center_it) { 
          for(auto it = std::max(begin(mapped_tokens), center_it-contextLength); it != std::min(end(mapped_tokens), center_it+contextLength); ++it) {
            if(center_it != it) {
              this->CBOW.push_back(std::make_pair(*center_it, *it));
            };
          }
        }
      }
      std::cout << "      Continuous bag of words gernerated." << std::endl;

      std::cout << "    Closing " << datafile << "..." << std::endl;
      file.close();

      std::cout << "\r                          \r";
    } else {
      std::cerr << "    Cannot open data file: " << datafile << std::endl;
      return;
    }
  }
}