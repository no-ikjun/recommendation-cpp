#ifndef WORD2VEC_H
#define WORD2VEC_H

#include "Model.h"
#include "../recommender/Vocabulary.h"
#include "../LinearAlgebra/Matrix.h"
#include "../LinearAlgebra/ColumnVector.h"

#include <vector>
#include <utility> // pair
#include <unordered_map>
#include <filesystem>
#include <string>

class Word2Vec : public Model {
public:
  Word2Vec(int dimension, int contextLength, Vocabulary& vocabulary);
  
  LinearAlgebra::ColumnVector embed(std::string) override;

  // CBOW: Continuous Bag of Words
  std::vector<std::pair<int, std::vector<int>>> getCBOW();
  void generateCBOW(std::filesystem::path, int contextLength);
  void saveCBOW(const std::string& filePath);
  void loadCBOW(const std::string& filePath);

  void saveWeights(const std::string& filePath);
  void loadWeights(const std::string& filePath);

  LinearAlgebra::ColumnVector forward(std::vector<int> contextTokens);
  void backward(
    std::vector<int>& contextTokens,
    LinearAlgebra::ColumnVector& prediction, 
    int& centerToken, 
    double learningRate
  );
  
  void train(int epoch, double learningRate);

private:
  Vocabulary vocabulary;
  int contextLength;
  std::vector<std::pair<int, std::vector<int>>> CBOW;
  int dimension;
  LinearAlgebra::Matrix encoderWeights;
  LinearAlgebra::Matrix decoderWeights;
};

#endif  