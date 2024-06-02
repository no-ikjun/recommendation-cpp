#ifndef WORD2VEC_H
#define WORD2VEC_H

#include "Vocabulary.h"

#include <vector>
#include <utility> // pair

class Word2Vec {
public:
  Word2Vec(int dimension, int vocabularySize);
  // std::vector<double> embed(std::string) override;
  void generateCBOW(std::filesystem::path, int contextLength); // Continuous Bag of words
  std::vector<std::pair<int, int>> getCBOW();
  void loadTrainDataset(std::string filepath);
  void saveTrainDataset(std::string filepath);
  void train(int epoch, double alpha);

private:
  Vocabulary vocabulary;
  std::vector<std::pair<int, int>> CBOW;
  int dimension;
  std::vector<std::vector<double>> encoderWeights;
  std::vector<std::vector<double>> decoderWeights;
};

#endif