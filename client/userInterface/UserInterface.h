#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>

class UserInterface {
public:
    void start();
    void printPrompt();
    std::string getUserInput();
};

#endif
