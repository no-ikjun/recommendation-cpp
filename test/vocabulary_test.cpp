#include "../include/recommender/Vocabulary.h"
#include <iostream>
#include <iomanip>

int main() {
  Vocabulary vocab(100);
  vocab.createVocabulary("./dataset/dataset_sm");
  std::cout << "100 tokens among " << vocab.getVocab().size() << std::endl;
  int i = 0;
  for(auto [token, id]: vocab.getVocab()) {
    if(i>100) break;
    std::cout << std::setw(7) << id << std::setw(15) << std::left << token << std::endl;
    i++;
  }
  std::cout << vocab.getId("alsdkjfalsdkjflaksljdk") << std::endl;
  std::cout << vocab.getId(" ") << std::endl;
  std::cout << vocab.getId("\0") << std::endl;
  std::cout << vocab.getId("  ") << std::endl;
}