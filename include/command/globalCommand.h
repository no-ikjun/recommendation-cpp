#ifndef GLOBALCOMMAND_H
#define GLOBALCOMMAND_H

#include <string>
#include <iostream>

class GlobalCommand {
public:
  static bool continuePrompt();
  void showMenu();
};

#endif // GLOBALCOMMAND_H