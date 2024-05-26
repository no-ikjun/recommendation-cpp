#ifndef WORD2VEC_H
#define WORD2VEC_H

#include <string>
#include <vector>
#include <array>

class Word2Vec {
public:
  void generateTrainDataset();
  std::vector<double> embed(std::string);
  double train(double alpha, int epoch);
  void saveWeights();
  void loadWeights();
  std::vector<std::string> getKNearestNeighbors(std::string, int k);
  
private:
  std::vector<std::array<long, 2>> CBOW; // Continuous Bag of Words
  std::vector<bool> oneHotEncode(long);
  std::vector<std::vector<bool>> trainX;
  std::vector<std::vector<bool>> trainY;
  std::vector<std::vector<double>> softmax(std::vector<std::vector<double>>);
  std::vector<std::vector<double>> encoder;
  std::vector<std::vector<double>> decoder;
  std::vector<double> forwardPass(std::string);
  double backwardPass(double alpha);
};

#endif WORD2VEC_H