#include "../include/recommender/Word2Vec.h"
#include "../include/recommender/Vocabulary.h"

#include <vector>
#include <array>
#include <iostream>
#include <utility> // pair

int main() {
  Word2Vec word2vec(100, 10000);
  word2vec.generateCBOW("./dataset/dataset_sm", 3);
  std::vector<std::pair<int, int>> cbow = word2vec.getCBOW();

  std::cout << "\n100 training set among " << cbow.size() << std::endl;
  int i = 0;
  for(auto pair: cbow) {
    if(i > 100) break;
    std::cout << pair.first << " " << pair.second << std::endl;
    i++;
  }

}