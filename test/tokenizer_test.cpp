#include "../include/recommender/Tokenizer.h"

#include <string>
#include <iostream>
#include <vector>

int main() {
  std::string testString = "Senjō no Valkyria 3 : <unk> Chronicles ( Japanese : 戦場のヴァルキュリア3 , lit . Valkyria of the Battlefield 3 ) , commonly referred to as Valkyria Chronicles III outside Japan , is a tactical role @-@ playing video game developed by Sega and Media.Vision for the PlayStation Portable .";
  std::vector<std::string> tokens = tokenize(testString);
  for(auto token: tokens) {
    std::cout << token << std::endl;
  }
}