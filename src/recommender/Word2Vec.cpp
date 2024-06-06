#include "../../include/recommender/Word2Vec.h"
#include "../../include/recommender/Tokenizer.h"
#include "../../include/recommender/Vocabulary.h"
#include "../../include/LinearAlgebra/Matrix.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility> // pair
#include <random>
#include <limits>
#include <cmath> 

Word2Vec::Word2Vec(int dimension, int vocabularySize, int contextLength): vocabulary(vocabularySize) {
  this->dimension = dimension;
  this->contextLength = contextLength;
  this->vocabulary.createVocabulary("./dataset/dataset_sm");
};

std::vector<std::pair<int, std::vector<int>>> Word2Vec::getCBOW() {
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
        if(tokens.size() < 2 * contextLength + 1) continue;
        std::vector<int> indexed_tokens;
        for(auto token: tokens) {
          indexed_tokens.push_back(this->vocabulary.getId(token));
        }
        std::vector<int> context_bow;
        for(
          auto center_it = indexed_tokens.begin()+contextLength; 
          center_it != indexed_tokens.end()-contextLength-1; 
          ++center_it
        ) { 
          this->CBOW.push_back(std::make_pair(*center_it, std::vector<int>{}));
          for(auto it = center_it-contextLength; it != center_it+contextLength+1; ++it) {
            if(center_it != it) {
              this->CBOW.back().second.push_back(*it);
            };
          }
        }
      }
      std::cout 
        << "      Total " << this->CBOW.size()
        << " of continuous bag of words gernerated." 
      << std::endl;

      std::cout << "    Closing " << datafile << "..." << std::endl;
      file.close();

      std::cout << "\r                          \r";
    } else {
      std::cerr << "    Cannot open data file: " << datafile << std::endl;
      return;
    }
  }
}

void Word2Vec::train(int epoch, double alpha) {
  std::cout << "@Word2Vec" << std::endl;

  std::cout << "  Initializing weights..." << std::endl;

  this->encoderWeights = LinearAlgebra::Matrix(this->vocabulary.getVocabSize(), this->dimension, true);
  this->decoderWeights = LinearAlgebra::Matrix(this->dimension, this->vocabulary.getVocabSize(), true);
  std::cout << "    Initialized encoder weights" << std::endl;
  this->encoderWeights.print();
  std::cout << "    Initialized decoder weights" << std::endl;
  this->decoderWeights.print();

  std::cout << "  Training Word2Vec model..." << std::endl;

  double totalLoss = 0.;
  for(int e = 0; e < epoch; ++e) {
    std::cout << "    Epoch " << e + 1 << "/" << epoch << std::endl;
    LinearAlgebra::Matrix prediction = this->encoderWeights * this->decoderWeights * LinearAlgebra::Matrix(this->vocabulary.getVocabSize(), 1, true);
    prediction.print();
  }
}