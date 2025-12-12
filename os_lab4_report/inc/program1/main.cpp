#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "prime.h"
#include "square.h"

void printHelp() {
    std::cout << "\n=== Program 1: Static Linking ===" << std::endl;
    std::cout << "Library linked at COMPILE TIME" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  0 - Show info about current implementation" << std::endl;
    std::cout << "  1 A B - Count primes between A and B" << std::endl;
    std::cout << "  2 A B - Calculate area with sides A and B" << std::endl;
    std::cout << "  help - Show this help" << std::endl;
    std::cout << "  quit - Exit program" << std::endl;
}

int main() {
    printHelp();
    
    std::string line;
    while (true) {
        std::cout << "\n> ";
        std::getline(std::cin, line);
        
        if (line.empty()) continue;
        
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        
        if (command == "quit" || command == "exit" || command == "q") {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        else if (command == "help" || command == "h") {
            printHelp();
        }
        else if (command == "0") {
            std::cout << "Current implementation: Library 1" << std::endl;
            std::cout << "  PrimeCount: Naive algorithm (check all divisors)" << std::endl;
            std::cout << "  Square: Rectangle area (A × B)" << std::endl;
            std::cout << "Note: Cannot switch implementation - linked at compile time!" << std::endl;
        }
        else if (command == "1") {
            int A, B;
            if (iss >> A >> B) {
                int result = PrimeCount(A, B);
                std::cout << "PrimeCount(" << A << ", " << B << ") = " << result << std::endl;
            } else {
                std::cout << "Error: Please provide two integers A and B" << std::endl;
            }
        }
        else if (command == "2") {
            float A, B;
            if (iss >> A >> B) {
                float result = Square(A, B);
                if (result >= 0) {
                    std::cout << "Square(" << A << ", " << B << ") = " << result << std::endl;
                } else {
                    std::cout << "Error: A and B must be positive numbers" << std::endl;
                }
            } else {
                std::cout << "Error: Please provide two numbers A and B" << std::endl;
            }
        }
        else {
            std::cout << "Unknown command. Type 'help' for available commands." << std::endl;
        }
    }
    
    return 0;
}