#include "../include/recommender/Word2Vec.h"

#include <vector>
#include <array>
#include <iostream>
#include <utility> // pair

int main() {
  Vocabulary vocab;
  vocab.createVocabulary("./dataset/dataset_sm");

  Word2Vec word2vec(100, vocab);
  word2vec.generateCBOW("./dataset/dataset_sm", 5);
  std::vector<std::pair<int, int>> cbow = word2vec.getCBOW();

  int i = 0;
  for(auto pair: cbow) {
    if(i > 100) break;
    std::cout << pair.first << " " << pair.second << std::endl;
    i++;
  }

}