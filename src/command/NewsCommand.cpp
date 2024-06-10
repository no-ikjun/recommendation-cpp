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

bool NewsCommand::printNews(std::string id) {
  try {
    News news = newsDb->get(id);
    int width = 80;
    std::string title = news.getTitle();
    int padding = (width - title.length()) / 2;

    // 출력할 제목이 중앙 정렬되도록 설정
    if (padding > 0) {
      std::cout << std::string(padding, ' ');
    }
    std::cout << GREEN << title << RESET << std::endl;

    std::cout << RESET << std::endl << CYAN << news.getContent() << RESET << std::endl;

    // 사용자 입력 요청
    std::cout << std::endl << "1: 긍정, 2: 부정, 3: 종료" << std::endl;
    int response;
    std::cin >> response;

    switch (response) {
      case 1:
      case 2:
        // 긍정 또는 부정 선택 시 함수 재호출
        std::cout << (response == 1 ? "긍정적인 의견을 선택하셨습니다." : "부정적인 의견을 선택하셨습니다.") << std::endl;
        return printNews(id); // 같은 뉴스를 다시 출력
      case 3:
        // 함수 종료
        std::cout << "함수를 종료합니다." << std::endl;
        return false;
      default:
        // 잘못된 입력 처리
        std::cout << "잘못된 입력입니다. 다시 입력해주세요." << std::endl;
        return printNews(id);
    }
  } catch (const std::exception& e) {
    printError(e.what());
    return false;
  }
}

void NewsCommand::printError(const std::string& message) {
  std::cout << RED << "News Command Error: " << message << RESET << std::endl;
}