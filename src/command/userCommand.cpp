#include "command/UserCommand.h"
#include "session/UserSession.h"
#include "LinearAlgebra/ColumnVector.h"
#include "recommender/Recommender.h"
#include <iostream>
#include <sstream>
#include <limits>
#include <vector>

const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string RESET = "\033[0m";

void UserCommand::signUp() {
  bool registrationSuccessful = false;
  do {
    std::string id, name, password;
    std::cout << "Sign Up " << YELLOW << "(Input Your Personal Information)" << RESET << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();

    std::cout << "ID: ";
    std::getline(std::cin, id);
    std::cout << "Name: ";
    std::getline(std::cin, name);
    std::cout << "Password: ";
    std::getline(std::cin, password);

    try {
      LinearAlgebra::ColumnVector tempPref = LinearAlgebra::ColumnVector(1);
      User newUser(id, name, password, tempPref);
      userDb->add(&newUser);
      std::cout << GREEN << "Registration successful." << RESET << std::endl;
      registrationSuccessful = true;
    } catch (const std::exception& e) {
      printError(e.what());
      std::cout << "Would you like to try registering again? (y/n): ";
      char response;
      std::cin >> response;
      if (response != 'y' && response != 'Y') {
        registrationSuccessful = true;
      }
    }
  } while (!registrationSuccessful);
}

void UserCommand::signIn() {
  bool loginSuccessful = false;
  do {
    std::string id, password;
    std::cout << "Sign In" << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();

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
        loginSuccessful = true;
      } else {
        std::cout << RED << "Invalid password. Please try again." << RESET << std::endl;
      }
    } catch (const std::exception& e) {
        std::cout << RED << "Login failed: " << e.what() << RESET << std::endl;
        std::cout << "Would you like to try logging in again? (y/n): ";
        char response;
        std::cin >> response;
        if (response != 'y' && response != 'Y') {
        loginSuccessful = true;
      }
    }
  } while (!loginSuccessful);
}

void UserCommand::setPref(Recommender* recommender) {
  UserSession* session = UserSession::getInstance();
  User userData = userDb->get(session->getUserId());
  LinearAlgebra::ColumnVector prefData = userData.getPreference();
  std::cout << "Current preferences:\n";
  prefData.print();

  std::cout << "Setting preferences...\n";
  std::cout << "Enter your interests separated by spaces (e.g., technology science business): ";

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ensure buffer is clear

  std::string input;
  std::getline(std::cin, input);  // 전체 라인 입력 받기

  std::istringstream iss(input);

  try {
    std::cout << "1" << std::endl;
    UserSession* session = UserSession::getInstance();
    std::cout << "2" << std::endl;
    std::string userId = session->getUserId();
    std::cout << "3" << std::endl;
    User updatedUserData = userDb->get(userId);
    std::cout << "4" << std::endl;
    updatedUserData.setPreference(recommender->embedPreference(input));
    std::cout << "5" << std::endl;
    updatedUserData.getPreference().print();
    std::cout << "6" << std::endl;
    userDb->update(&updatedUserData);
    std::cout << "7" << std::endl;
    userDb->get(userId).getPreference().print();
    std::cout << "8" << std::endl;
    userDb->saveToFile(userDb->get(userId));
    std::cout << "9" << std::endl;
    userDb->get(userId).getPreference().print();
    std::cout << "Preferences updated successfully.\n";
  } catch (const std::exception& e) {
    std::cerr << "Failed to update preferences: " << e.what() << std::endl;
  }
}

void UserCommand::printError(const std::string& message) {
  std::cout << RED << "User Command Error: " << message << RESET << std::endl;
}