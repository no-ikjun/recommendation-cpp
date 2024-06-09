#include "../include/recommender/Vocabulary.h"
#include <iostream>
#include <iomanip>

int main() {
  Vocabulary vocab;
  vocab.create("./dataset/dataset_sm", 10000);
  std::cout << "\n100 tokens among " << vocab.getVocab().size() << std::endl;
  int i = 0;
  for(auto [token, id]: vocab.getVocab()) {
    if(i>100) break;
    std::cout << std::setw(7) << id << std::setw(15) << std::left << token << std::endl;
    i++;
  }
}