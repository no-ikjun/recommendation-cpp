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
#include <ios>

Vocabulary::Vocabulary() {}

std::unordered_map<std::string, int> Vocabulary::getVocab() {
  return this->vocab;
}

int Vocabulary::getVocabSize() {
  return this->vocab.size();
}

int Vocabulary::getId(std::string token) {
  try{
    return this->vocab.at(token);
  } catch(const std::out_of_range &e) {
    return 0;
  }
}

void Vocabulary::create(std::filesystem::path datasetPath, int maxVocabSize) {
  std::cout << "\n@Vocabulary" << std::endl;

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
  
  if(histogram.size() > maxVocabSize) {
    std::cout 
      << "  Removing " << histogram.size() - maxVocabSize 
      << " tokens from the vocabulary to match the maximum vocabulary size " << maxVocabSize
    << std::endl;

    std::vector<std::pair<std::string, int>> vectorized_histogram(histogram.begin(), histogram.end());
    std::sort(
      vectorized_histogram.begin(), 
      vectorized_histogram.end(), 
      [](
        std::pair<std::string, int> a, 
        std::pair<std::string, int> b
      ) -> bool {return a.second > b.second;}
    );
    for(auto it = vectorized_histogram.begin(); it != vectorized_histogram.end() - (histogram.size() - maxVocabSize); ++it) {
      it->second = it - vectorized_histogram.begin();
    }
    this->vocab = std::unordered_map<std::string, int>(vectorized_histogram.begin(), vectorized_histogram.end() - (histogram.size() - maxVocabSize + 1));
    this->vocab["<unk>"] = this->vocab.size();
  }

  std::cout 
    << "  Vocabulary of total " << this->vocab.size() << " tokens is created"
  << std::endl;

}

void Vocabulary::saveAs(std::filesystem::path filePath) {
  std::cout << "\n@Vocabulary" << std::endl;

  std::ofstream file(filePath, std::ios::binary);
  if (file.is_open()) {
    std::cout << "  Saving vocabulary to " << filePath << "..." << std::endl;
    size_t vocabSize = this->vocab.size();
    file.write(reinterpret_cast<const char*>(&vocabSize), sizeof(vocabSize));
    for (const auto& entry : this->vocab) {
      size_t tokenSize = entry.first.size();
      file.write(reinterpret_cast<const char*>(&tokenSize), sizeof(tokenSize));
      file.write(entry.first.c_str(), tokenSize);
      file.write(reinterpret_cast<const char*>(&entry.second), sizeof(entry.second));
    }
    std::cout << "  Vocabulary saved successfully" << std::endl;
    file.close();
  } else {
    throw std::runtime_error("Cannot open file: " + filePath.string());
  }
}

void Vocabulary::loadFrom(std::filesystem::path filePath) {
  std::cout << "\n@Vocabulary" << std::endl;

  std::ifstream file(filePath, std::ios::binary);
  if (file.is_open()) {
    std::cout << "  Loading vocabulary from " << filePath << "..." << std::endl;
    size_t vocabSize;
    file.read(reinterpret_cast<char*>(&vocabSize), sizeof(vocabSize));
    for (size_t i = 0; i < vocabSize; ++i) {
      size_t tokenSize;
      file.read(reinterpret_cast<char*>(&tokenSize), sizeof(tokenSize));
      std::string token(tokenSize, '\0');
      file.read(&token[0], tokenSize);
      int id;
      file.read(reinterpret_cast<char*>(&id), sizeof(id));
      this->vocab[token] = id;
    }
    std::cout << "  Vocabulary loaded successfully" << std::endl;
    file.close();
  } else {
    throw std::runtime_error("Cannot open file: " + filePath.string());
  }
}