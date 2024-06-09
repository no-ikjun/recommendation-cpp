#include "../include/recommender/Word2Vec.h"
#include "../include/recommender/Vocabulary.h"
#include "../include/LinearAlgebra/ColumnVector.h"

#include <vector>
#include <array>
#include <iostream>
#include <utility>
#include <iomanip>

#include <unordered_map>
#include <string>


int main() {  
  Vocabulary vocabulary;

  try {
    std::cout << "Looking for saved vocabulary..." << std::endl;
    vocabulary.loadFrom("./src/recommender/vocabulary.bin");
  } catch (const std::exception& e) {
    std::cout << "Cannot find saved vocabulary" << std::endl;
    std::cout << "Generating vocabulary..." << std::endl;
    vocabulary.create("./dataset/dataset_sm", 100000);
    vocabulary.saveAs("./src/recommender/vocabulary.bin");
  }
  Word2Vec word2vec(300, 3, vocabulary);

  try{
    std::cout << "Looking for saved model weights..." << std::endl;
    word2vec.loadWeights("./src/recommender/weights");
  } catch (const std::exception& e) {
    std::cout << "Cannot find saved model weights" << std::endl;
    try {
      word2vec.loadCBOW("./src/recommender/cbow.bin");
    } catch (const std::exception& e) {
      std::cout << "Cannot find saved continuous bag of words" << std::endl;
      std::cout << "Generating continuous bag of words... " << std::endl;
      word2vec.generateCBOW("./dataset/dataset_sm", 3);
      word2vec.saveCBOW("./src/recommender/cbow.bin");
    }

    word2vec.train(10000, 0.01);

    word2vec.saveWeights("./src/recommender/weights");
  }
  
  std::cout << "\nsun " << std::endl;
  LinearAlgebra::ColumnVector sun = word2vec.embed("sun");
  sun.print(true);

  std::cout << "\ndaughter" << std::endl;
  LinearAlgebra::ColumnVector daughter = word2vec.embed("daughter");
  daughter.print(true);

  std::cout << "\nman" << std::endl;
  LinearAlgebra::ColumnVector man = word2vec.embed("man");
  man.print(true);
  
  std::cout << "\nwoman" << std::endl;
  LinearAlgebra::ColumnVector woman = word2vec.embed("woman");
  woman.print(true);

  std::cout << "\nsun - man + woman" << std::endl;
  LinearAlgebra::ColumnVector mystery = word2vec.embed("woman");

  std::cout << "\n(sun - man + woman) ~ daughter similarity: " 
    << mystery.cosineSimilarity(daughter)
  << std::endl;

  std::cout << "\n(sun - man + woman) ~ rock similarity: " 
    << mystery.cosineSimilarity(word2vec.embed("rock"))
  << std::endl;
  
}