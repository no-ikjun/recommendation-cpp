#include "../include/recommender/Word2Vec.h"
#include "../include/recommender/Vocabulary.h"
#include "../include/LinearAlgebra/ColumnVector.h"

#include <vector>
#include <array>
#include <iostream>
#include <utility>
#include <iomanip>

#include <unordered_map>


int main() {
  Vocabulary vocabulary;
  try {
    std::cout << "Looking for saved vocabulary..." << std::endl;
    vocabulary.loadFrom("./src/recommender/vocabulary.bin");
  } catch (const std::exception& e) {
    std::cout << "Cannot find saved vocabulary" << std::endl;
    std::cout << "Generating vocabulary..." << std::endl;
    vocabulary.create("./dataset/dataset_sm", 1000);
    vocabulary.saveAs("./src/recommender/vocabulary.bin");
  }

  Word2Vec word2vec(2, 2, vocabulary);

  try{
    std::cout << "Looking for saved model weights..." << std::endl;
    word2vec.loadWeights("./src/recommender/weights.bin");
  } catch (const std::exception& e) {
    std::cout << "Cannot find saved model weights" << std::endl;
    try {
      word2vec.loadCBOW("./src/recommender/cbow.bin");
    } catch (const std::exception& e) {
      std::cout << "Cannot find saved continuous bag of words" << std::endl;
      std::cout << "Generating continuous bag of words... " << std::endl;
      word2vec.generateCBOW("./dataset/dataset_sm", 2);
      word2vec.saveCBOW("./src/recommender/cbow.bin");
    }

    word2vec.train(1, 0.01);

    word2vec.saveWeights("./src/recommender/weights.bin");
  }
  
  // std::cout << "\nking " << std::endl;
  // LinearAlgebra::ColumnVector king = word2vec.embed("king");
  // king.print();

  // std::cout << "\nqueen" << std::endl;
  // LinearAlgebra::ColumnVector queen = word2vec.embed("queen");
  // queen.print();

  // std::cout << "\nman" << std::endl;
  // LinearAlgebra::ColumnVector man = word2vec.embed("man");
  // man.print();
  
  // std::cout << "\nwoman" << std::endl;
  // LinearAlgebra::ColumnVector woman = word2vec.embed("woman");
  // woman.print();

  // std::cout << "\nking - man + woman" << std::endl;
  // LinearAlgebra::ColumnVector mystery = word2vec.embed("woman");

  // std::cout << "\n(king - man + woman) ~ queen similarity: " 
  //   << mystery.cosineSimilarity(queen)
  // << std::endl;

  // std::cout << "\n(king - man + woman) ~ apple similarity: " 
  //   << mystery.cosineSimilarity(word2vec.embed("apple"))
  // << std::endl;
  
}