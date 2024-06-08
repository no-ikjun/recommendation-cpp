#include "../../include/recommender/Word2Vec.h"
#include "../../include/recommender/Tokenizer.h"
#include "../../include/recommender/Vocabulary.h"
#include "../../include/LinearAlgebra/Matrix.h"
#include "../../include/LinearAlgebra/Utils.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <utility> // pair
#include <random>
#include <limits>
#include <cmath> 
#include <vector>
#include <stdexcept>

Word2Vec::Word2Vec(
  int dimension, int contextLength, Vocabulary& vocabulary
): dimension(dimension), contextLength(contextLength), vocabulary(vocabulary) {}

LinearAlgebra::ColumnVector Word2Vec::embed(std::string string) {
  LinearAlgebra::RowVector embeddingVector(this->dimension);
  std::vector<std::string> tokens = tokenize(string);
  int knownTokenCounter = 0;
  for(std::string& token: tokens) {
    int tokenId = this->vocabulary.getId(token);
    if(tokenId == 0) continue; // add 0 vector for <unk> token
    embeddingVector += this->encoderWeights.getRow(tokenId) / knownTokenCounter;
    knownTokenCounter++;
  }
  return embeddingVector.transpose();
}

std::vector<std::pair<int, std::vector<int>>> Word2Vec::getCBOW() {
  return this->CBOW;
}

void Word2Vec::generateCBOW(std::filesystem::path datasetPath, int contextLength) {
  std::cout << "\n@Word2Vec" << std::endl;

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

void Word2Vec::saveCBOW(const std::string& filePath) {
  std::cout << "\n@Word2Vec" << std::endl;
  std::cout << "  Saving CBOW to " << filePath << "... " << std::endl;

  std::ofstream file(filePath, std::ios::binary);
  if (file.is_open()) {
    size_t cbowSize = this->CBOW.size();
    file.write(reinterpret_cast<const char*>(&cbowSize), sizeof(cbowSize));
    for (const auto& pair : this->CBOW) {
      int center = pair.first;
      const std::vector<int>& contexts = pair.second;
      size_t contextSize = contexts.size();
      file.write(reinterpret_cast<const char*>(&center), sizeof(center));
      file.write(reinterpret_cast<const char*>(&contextSize), sizeof(contextSize));
      file.write(reinterpret_cast<const char*>(contexts.data()), contextSize * sizeof(int));
    }
    file.close();
    std::cout << "  CBOW saved to " << filePath << std::endl;
  } else {
    throw std::runtime_error("Failed to open file: " + filePath);
  }
}

void Word2Vec::loadCBOW(const std::string& filePath) {
  std::cout << "\n@Word2Vec" << std::endl;
  std::cout << "  Loading CBOW from " << filePath << "... " << std::endl;

  std::ifstream file(filePath, std::ios::binary);
  if (file.is_open()) {
    size_t cbowSize;
    file.read(reinterpret_cast<char*>(&cbowSize), sizeof(cbowSize));
    this->CBOW.resize(cbowSize);
    for (auto& pair : this->CBOW) {
      int center;
      size_t contextSize;
      file.read(reinterpret_cast<char*>(&center), sizeof(center));
      file.read(reinterpret_cast<char*>(&contextSize), sizeof(contextSize));
      pair.first = center;
      pair.second.resize(contextSize);
      file.read(reinterpret_cast<char*>(pair.second.data()), contextSize * sizeof(int));
    }
    file.close();
    this->contextLength = this->getCBOW()[0].second.size() / 2;

    std::cout << "  CBOW loaded from " << filePath << std::endl;
    std::cout 
      << "    examples #: " << this->getCBOW().size()
      << " | context length: " << this->contextLength
    << std::endl;
  } else {
    throw std::runtime_error("Failed to open file: " + filePath);
  }
}

void Word2Vec::saveWeights(const std::string& filePath) {
  std::cout << "\n@Word2Vec" << std::endl;
  std::cout << "  Saving model weights to " << filePath << "... " << std::endl;

  std::filesystem::path p(filePath);
  std::string stem = p.stem().string();
  std::string extension = p.extension().string();

  std::cout << "    Saving encoder matrix weights as " << stem + "_encoder" + extension << " ..." << std::endl;
  this->encoderWeights.saveAs(stem + "_encoder" + extension);
  std::cout << "    Saving decoder matrix weights as " << stem + "_decoder" + extension << " ..." << std::endl;
  this->decoderWeights.saveAs(stem + "_decoder" + extension);

  std::cout << "  Model weights saved" << std::endl;
}

void Word2Vec::loadWeights(const std::string& filePath) {
  std::cout << "\n@Word2Vec" << std::endl;
  std::cout << "  Loading model weights from " << filePath << "... " << std::endl;

  std::filesystem::path p(filePath);
  std::string stem = p.stem().string();
  std::string extension = p.extension().string();

  std::cout << "    Loading encoder matrix weights from " << stem + "_encoder" + extension << " ..." << std::endl;
  this->encoderWeights.loadFrom(stem + "_encoder" + extension);
  std::cout << "    Loading decoder matrix weights from " << stem + "_decoder" + extension << " ..." << std::endl;
  this->decoderWeights.loadFrom(stem + "_decoder" + extension);

  std::cout << "  Model weights loaded" << std::endl;
}

LinearAlgebra::ColumnVector Word2Vec::forward(std::vector<int> contextTokens) {
  LinearAlgebra::ColumnVector contextEmbedding(this->dimension);
  for(int& context: contextTokens) {
    contextEmbedding += this->encoderWeights.getRow(context).transpose();
  }
  contextEmbedding /= contextTokens.size();
  LinearAlgebra::ColumnVector prediction = (contextEmbedding.transpose() * this->decoderWeights).transpose();
  LinearAlgebra::softmax(prediction);
  return prediction;
}

void Word2Vec::backward(
  std::vector<int>& contextTokens,
  LinearAlgebra::ColumnVector& prediction, 
  int& centerToken, 
  double learningRate
) {
  LinearAlgebra::Matrix decoderMatrixGradient = LinearAlgebra::Matrix(
    this->dimension, this->vocabulary.getVocabSize()
  );
  for(int i = 0; i < decoderMatrixGradient.shape().first; ++i) {
    for(int j = 0; j < decoderMatrixGradient.shape().second; ++j) {
      double average = 0;
      for(int& context: contextTokens) {
        average += this->encoderWeights(context, i);
      }
      average /= contextTokens.size();
      decoderMatrixGradient(i, j) = (-(j == centerToken ? 1 : 0) + prediction(j)) * average;
    }
  }

  LinearAlgebra::Matrix encoderMatrixGradient = LinearAlgebra::Matrix(
    this->vocabulary.getVocabSize(), this->dimension
  );
  LinearAlgebra::ColumnVector oneHotAverageInputVector(this->vocabulary.getVocabSize());
  for(int& context: contextTokens) {
    oneHotAverageInputVector(context) = 1;
  }
  oneHotAverageInputVector /= contextTokens.size();
  for(int i = 0; i < encoderMatrixGradient.shape().first; ++i) {
    for(int j = 0; j < encoderMatrixGradient.shape().second; ++j) {
      for(int k = 0; k < this->vocabulary.getVocabSize(); ++k) {
        encoderMatrixGradient(i, j) += (-(k == centerToken ? 1 : 0) + prediction(k)) * this->decoderWeights(j, k) * oneHotAverageInputVector(i);
      }
    }
  }

  this->encoderWeights -= encoderMatrixGradient * learningRate;
  this->decoderWeights -= decoderMatrixGradient * learningRate;
}

void Word2Vec::train(int epoch, double learningRate) {
  std::cout << "\n@Word2Vec" << std::endl;

  std::cout << "  Initializing weights..." << std::endl;

  this->encoderWeights = LinearAlgebra::Matrix(this->vocabulary.getVocabSize(), this->dimension, true);
  this->decoderWeights = LinearAlgebra::Matrix(this->dimension, this->vocabulary.getVocabSize(), true);
  std::cout << "    Initialized encoder weights" << std::endl;
  std::cout << "    Initialized decoder weights" << std::endl;

  std::cout << "  Model summary" << std::endl;
  std::cout << "    Encoder Weights: Type - LinearAlgebra::Matrix, Shape - " << this->encoderWeights.shape().first << "x" << this->encoderWeights.shape().second << ", Trainable - true" << std::endl;
  std::cout << "    Decoder Weights: Type - LinearAlgebra::Matrix, Shape - " << this->decoderWeights.shape().first << "x" << this->decoderWeights.shape().second << ", Trainable - true" << std::endl;
  std::cout << "    Dimension: " << this->dimension << std::endl;
  std::cout << "    Vocabulary Size: " << this->vocabulary.getVocabSize() << std::endl;
  std::cout << "    Context Length: " << this->contextLength << std::endl;

  std::cout << "  Training Word2Vec model..." << std::endl;

  for(int e = 0; e < epoch; ++e) {
    std::cout << "    Epoch " << e + 1 << "/" << epoch << std::endl;
    int exampleCounter = 0;
    for(auto& [center, contexts]: this->CBOW) {
      exampleCounter++;
      LinearAlgebra::ColumnVector prediction = this->forward(contexts);
      LinearAlgebra::ColumnVector target = LinearAlgebra::oneHotEncode(center, this->vocabulary.getVocabSize());

      double predictionExpSum = 0;
      prediction.forEach([&](double& value) {
        predictionExpSum += std::exp(value);
      });
      double loss = -prediction(center) + std::log(predictionExpSum);

      this->backward(contexts, prediction, center, learningRate);

      std::cout 
        << "      example: " << std::setw(5) << exampleCounter << " / " << this->CBOW.size()
        << std::setw(5) << std::fixed << std::setprecision(6)
        << " | loss: " << loss
      << "\r";
    }
    std::cout << std::endl;
  }
}