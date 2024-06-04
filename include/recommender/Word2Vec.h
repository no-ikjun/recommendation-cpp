#ifndef WORD2VEC_H
#define WORD2VEC_H

#include "Vocabulary.h"
#include "Matrix.h"

#include <vector>
#include <utility> // pair
#include <unordered_map>

class Word2Vec {
public:
  Word2Vec(int dimension, int vocabularySize, int contextLength);
  // std::vector<double> embed(std::string) override;
  void generateCBOW(std::filesystem::path, int contextLength); // Continuous Bag of words
  std::vector<std::pair<int, std::vector<int>>> getCBOW();
  void loadTrainDataset(std::string filepath);
  void saveTrainDataset(std::string filepath);
  void train(int epoch, double alpha);

private:
  Vocabulary vocabulary;
  int contextLength;
  std::vector<std::pair<int, std::vector<int>>> CBOW;
  int dimension;
  std::vector<std::vector<double>> encoderWeights;
  std::vector<std::vector<double>> decoderWeights;
};

#endif