#include "command/UserCommand.h"
#include "session/UserSession.h"
#include <iostream>

const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string RESET = "\033[0m";

void UserCommand::signUp() {
  std::string id, name, password;
  std::cout << "Sign Up " << YELLOW << "(Input Your Personal Information)" << RESET << std::endl;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::cout << "ID: ";
  std::getline(std::cin, id);
  std::cout << "Name: ";
  std::getline(std::cin, name);
  std::cout << "Password: ";
  std::getline(std::cin, password);

  try {
    User newUser(id, name, password);
    userDb->add(&newUser);
    std::cout << GREEN << "Registration successful." << RESET << std::endl;
  } catch (const std::exception& e) {
    printError(e.what());
  }
}

void UserCommand::signIn() {
  std::string id, password;
  std::cout << "Sign In" << std::endl;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  
  std::cout << "ID: ";
  std::getline(std::cin, id);
  std::cout << "Password: ";
  std::getline(std::cin, password);

  try {
    User user = userDb->get(id);
    if (user.getPassword() == password) {
      UserSession* session = UserSession::getInstance();
      session->login(user.getId(), user.getName());
      std::cout << GREEN << "Login successful. Welcome, " << session->getUserName() << "!" << RESET << std::endl;
    } else {
      std::cout << RED << "Invalid password. Please try again." << RESET << std::endl;
    }
  } catch (const std::exception& e) {
      std::cout << RED << "Login failed: " << e.what() << RESET << std::endl;
  }
}

void UserCommand::setPref() {
  std::cout << "Setting preferences..." << std::endl;
  // 선호도 설정 로직 구현 필요
}

void UserCommand::printError(const std::string& message) {
  std::cerr << "Error: " << message << std::endl;
}