#include "Vocabulary.h"

#include <vector>

class Word2Vec: public Model{
public:
  Word2Vec(int dimension);
  std::vector<double> embed(std::string) override;
  void generateCBOW(int contextLength); // Continuous Bag of words
  void loadTrainDataset(std::string filepath);
  void saveTrainDataset(std::string filepath);
  void train(int epoch, double alpha);

private:
  Vocabulary vocabulary;
  int dimension;
  std::vector<std::vector<double>> encoderWeights;
  std::vector<std::vector<double>> decoderWeights;
};