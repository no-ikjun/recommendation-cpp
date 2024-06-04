#include "../../include/recommender/Word2Vec.h"
#include "../../include/recommender/Tokenizer.h"
#include "../../include/recommender/Vocabulary.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility> // pair
#include <random>
#include <limits>
#include <cmath> 

Word2Vec::Word2Vec(int dimension, int vocabularySize, int contextLength): vocabulary(vocabularySize) {
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
        << "of continuous bag of words gernerated." 
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

double getRandomNumber(double mean, double std) {
  std::random_device randomDevice; 
  std::mt19937 generator(randomDevice());
  std::normal_distribution<> distribution(mean, std);
  return distribution(generator);
}

std::vector<std::vector<double>> generate_random_matrix(int rows, int cols, double mean=0, double std=1) {
  std::vector<std::vector<double>> matrix(rows, std::vector<double>(cols));
  for (auto i=matrix.begin(); i != matrix.end(); ++i) {
    for(auto j=(*i).begin(); j != (*i).end(); ++j) {
      *j = getRandomNumber(mean, std);
    }
  }
  return matrix;
}

void softmax(std::vector<std::vector<double>>& matrix) {
  for (auto i=matrix.begin(); i != matrix.end(); ++i) {
    double sum = std::numeric_limits<double>::min();
    for(auto j=(*i).begin(); j != (*i).end(); ++j) {
      *j = std::exp(*j);
      sum += *j;
    }
    for(auto j=(*i).begin(); j != (*i).end(); ++j) {
      *j /= sum;
    }
  }
}

std::vector<double> one_hot_encode(int index, int size) {
  std::vector<double> one_hot_vector(size, 0.);
  one_hot_vector[index] = 1.;
  return one_hot_vector;
}

void Word2Vec::train(int epoch, double alpha) {
  std::cout << "@Word2Vec" << std::endl;

  std::cout << "  Training Word2Vec model..." << std::endl;

  this->encoderWeights = generate_random_matrix(this->vocabulary.getVocabSize(), this->dimension);
  this->decoderWeights = generate_random_matrix(this->dimension, this->vocabulary.getVocabSize());

  for(int e = 0; e < epoch; ++e) {
    std::cout << "Epoch " << e + 1 << "/" << epoch << std::endl;

    double totalLoss = 0.;

    for(auto& [center_token, context_tokens]: this->CBOW) {
      std::vector<double> inputVector(this->dimension, 0.);
      for(int context_token: context_tokens) {
        for(int d = 0; d < dimension; ++d) {
          inputVector[d] += encoderWeights[context_token][d];
        }
      }

      std::vector<double> outputVector = inputVector;
    }
  }
}