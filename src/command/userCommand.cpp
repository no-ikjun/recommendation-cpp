#include "command/UserCommand.h"
#include <iostream>

void UserCommand::signUp() {
  std::string id, name, password;
  std::cout << "Sign Up" << std::endl;
  std::cout << "ID: ";
  std::getline(std::cin, id);
  std::cout << "Name: ";
  std::getline(std::cin, name);
  std::cout << "Password: ";
  std::getline(std::cin, password);

  try {
    User newUser(id, name, password);
    userDb->add(&newUser);
    std::cout << "Registration successful." << std::endl;
  } catch (const std::exception& e) {
    printError(e.what());
  }
}

void UserCommand::signIn() {
  std::string id, password;
  std::cout << "Sign In" << std::endl;
  std::cout << "ID: ";
  std::getline(std::cin, id);
  std::cout << "Password: ";
  std::getline(std::cin, password);

  // 로그인 로직 구현 필요
  std::cout << "Login successful." << std::endl;
}

void UserCommand::setPref() {
  std::cout << "Setting preferences..." << std::endl;
  // 선호도 설정 로직 구현 필요
}

void UserCommand::printError(const std::string& message) {
  std::cerr << "Error: " << message << std::endl;
}

void UserCommand::printWelcome() {
  std::cout << "Welcome to the system!" << std::endl;
}

void UserCommand::printGoodbye() {
  std::cout << "Goodbye!" << std::endl;
}
