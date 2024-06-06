#include "../include/recommender/Word2Vec.h"
#include "../include/recommender/Vocabulary.h"

#include <vector>
#include <array>
#include <iostream>
#include <utility>
#include <iomanip>


int main() {
  Word2Vec word2vec(20, 50, 3);
  word2vec.generateCBOW("./dataset/dataset_sm", 3);
  std::vector<std::pair<int, std::vector<int>>> cbow = word2vec.getCBOW();

  std::cout << "\n100 training set among " << cbow.size() << std::endl;
  int i = 0;
  for(auto& [center_token, context_tokens]: cbow) {
    if(i > 100) break;
    std::cout << std::setw(5) << center_token << " : ";
    for(auto context_token: context_tokens) {
      std::cout << std::setw(5) << context_token << " ";
    } 
    std::cout << std::endl;
    i++;
  }

  word2vec.train(100, 0.1);
}