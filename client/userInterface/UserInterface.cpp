#include "UserInterface.h"
#include <iostream>

void UserInterface::start() {
    std::string message;
    printPrompt();
    while (true) {
        message = getUserInput();
        if (message == "exit") {
            std::cout << "Exiting..." << std::endl;
            break;
        }
        std::cout << "You sent: " << message << std::endl;
    }
}

void UserInterface::printPrompt() {
    std::cout << "Enter message (or type 'exit' to quit): ";
}

std::string UserInterface::getUserInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}
