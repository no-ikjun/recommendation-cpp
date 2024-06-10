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

void printWrappedText(const std::string& text, int maxWidth) {
  std::istringstream words(text);
  std::string word;
  int currentWidth = 0;

  while (words >> word) {
    if (currentWidth + word.length() > maxWidth) {
      std::cout << std::endl;
      currentWidth = 0;
    }
    if (currentWidth > 0) {
      std::cout << " ";
      currentWidth += 1;
    }
    std::cout << word;
    currentWidth += word.length();
  }
  std::cout << std::endl;
}

bool NewsCommand::printNews(std::string id) {
  while (true) {
    try {
      News news = newsDb->get(id);
      int width = 80;
      std::string title = news.getTitle();
      int padding = (width - title.length()) / 2;

      // 출력할 제목이 중앙 정렬되도록 설정
      std::cout << std::string(padding, ' ') << GREEN << title << RESET << std::endl;
      std::cout << CYAN;
      printWrappedText(news.getContent(), width);
      std::cout << RESET << std::endl;

      // 사용자 입력 요청
      std::cout << std::endl << "1: 긍정, 2: 부정, 3: 종료" << std::endl;
      int response;
      std::cin >> response;

      UserSession* session = UserSession::getInstance();
      User updatedUserData = userDb->get(session->getUserId());

      switch (response) {
        case 1:
          std::cout << "긍정적인 의견을 선택하셨습니다." << std::endl;
          // 관심사 업데이트 로직 필요
          break;
        case 2:
          std::cout << "부정적인 의견을 선택하셨습니다." << std::endl;
          // 관심사 업데이트 로직 필요
          break;
        case 3:
          std::cout << "함수를 종료합니다." << std::endl;
          return true;
        default:
          std::cout << "잘못된 입력입니다. 다시 입력해주세요." << std::endl;
          continue;
      }

      // 관심사 업데이트 성공 시 메시지
      userDb->update(&updatedUserData);
      std::cout << "Preferences updated successfully.\n";

    } catch (const std::exception& e) {
      printError(e.what());
      return false;  // 예외 발생 시 함수 종료
    }
  }
}

void NewsCommand::printError(const std::string& message) {
  std::cout << RED << "News Command Error: " << message << RESET << std::endl;
}