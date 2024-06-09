#include "command/GlobalCommand.h"
#include "command/NewsCommand.h"
#include "session/UserSession.h"
#include "data/User.h"
#include "db/UserDatabase.h"
#include "recommender/Recommender.h"
#include "recommender/Word2Vec.h"
#include "recommender/Vocabulary.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>

const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string RESET = "\033[0m";

void NewsCommand::getRecommendation() {
  UserSession* session = UserSession::getInstance();
  std::string userId = session->getUserId();
  User user = userDb->get(userId);

  Vocabulary vocabulary;
  vocabulary.loadFrom("./src/recommender/vocabulary.bin");
  Word2Vec word2vec(300, 3, vocabulary);
  word2vec.embed("any string here");

  // printNews(newsId);
}

bool NewsCommand::printNews(std::string id) {
  try {
    News news = newsDb->get(id);
    int width = 80;
    std::string title = news.getTitle();
    int padding = (width - title.length()) / 2;

    if (padding > 0) {
      std::cout << std::setw(padding) << ' ';
    }
    std::cout << GREEN << title << RESET << std::endl;

    std::cout << std::endl;

    std::cout << RESET << std::endl << CYAN << news.getContent() << RESET << std::endl;
    return true;
  } catch (const std::exception& e) {
    printError(e.what());
    return false;
  }
}

void NewsCommand::printError(const std::string& message) {
  std::cout << RED << "News Command Error: " << message << RESET << std::endl;
}