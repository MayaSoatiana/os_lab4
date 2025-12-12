#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <windows.h>

// Function pointer types matching contracts
typedef int (*PrimeCountFunc)(int, int);
typedef float (*SquareFunc)(float, float);

class DynamicLibrary {
private:
    HMODULE handle;
    std::string name;
    
public:
    DynamicLibrary() : handle(nullptr) {}
    
    ~DynamicLibrary() {
        unload();
    }
    
    bool load(const std::string& libName) {
        unload();  // Unload any previously loaded library
        name = libName;
        std::wstring wideLibName(libName.begin(), libName.end());
        handle = LoadLibraryW(wideLibName.c_str());
        if (!handle) {
            DWORD error = GetLastError();
            std::cerr << "Failed to load " << libName << " (Error: " << error << ")" << std::endl;
            return false;
        }
        return true;
    }
    
    void* getFunction(const std::string& funcName) {
        if (!handle) return nullptr;
        return reinterpret_cast<void*>(GetProcAddress(handle, funcName.c_str()));
    }
    
    void unload() {
        if (handle) {
            FreeLibrary(handle);
            handle = nullptr;
        }
    }
    
    bool isLoaded() const {
        return handle != nullptr;
    }
    
    std::string getName() const {
        return name;
    }
};

void printHelp(int currentLib) {
    std::cout << "\n=== Program 2: Dynamic Loading ===" << std::endl;
    std::cout << "Libraries loaded at RUNTIME" << std::endl;
    std::cout << "Current library: " << (currentLib == 0 ? "None" : 
                      currentLib == 1 ? "Library 1" : "Library 2") << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  0 - Switch between Library 1 and Library 2" << std::endl;
    std::cout << "  1 A B - Count primes between A and B" << std::endl;
    std::cout << "  2 A B - Calculate area with sides A and B" << std::endl;
    std::cout << "  help - Show this help" << std::endl;
    std::cout << "  quit - Exit program" << std::endl;
}

int main() {
    DynamicLibrary lib;
    PrimeCountFunc PrimeCount = nullptr;
    SquareFunc Square = nullptr;  
    int currentLib = 0;  // 0 = none, 1 = lib1, 2 = lib2
    
    // Library 1 by default
    std::string defaultLib;
    defaultLib = "mathlib1.dll";
    
    if (lib.load(defaultLib)) {
        PrimeCount = (PrimeCountFunc)lib.getFunction("PrimeCount");
        Square = (SquareFunc)lib.getFunction("Square");
        
        if (PrimeCount && Square) {
            currentLib = 1;
            std::cout << "Successfully loaded Library 1 by default" << std::endl;
        } else {
            std::cerr << "Error: Could not find required functions in the library" << std::endl;
            lib.unload();
        }
    }
    
    printHelp(currentLib);
    
    std::string line;
    while (true) {
        std::cout << "\n[" << (currentLib == 0 ? "No lib" : 
                   currentLib == 1 ? "Lib1" : "Lib2") << "] > ";
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
            printHelp(currentLib);
        }
        else if (command == "0") {
            // Switch library
            lib.unload();
            PrimeCount = nullptr;
            Square = nullptr;
            
            currentLib = (currentLib == 1) ? 2 : 1;
            std::string libName;
            
            libName = (currentLib == 1) ? "mathlib1.dll" : "mathlib2.dll";
            
            if (lib.load(libName)) {
                PrimeCount = (PrimeCountFunc)lib.getFunction("PrimeCount");
                Square = (SquareFunc)lib.getFunction("Square");
                
                if (PrimeCount && Square) {
                    std::cout << "Switched to Library " << currentLib << std::endl;
                    if (currentLib == 1) {
                        std::cout << "  PrimeCount: Naive algorithm" << std::endl;
                        std::cout << "  Square: Rectangle area (A × B)" << std::endl;
                    } else {
                        std::cout << "  PrimeCount: Sieve of Eratosthenes" << std::endl;
                        std::cout << "  Square: Right triangle area (A × B / 2)" << std::endl;
                    }
                } else {
                    std::cout << "Error: Functions not found in the library" << std::endl;
                    currentLib = 0;
                }
            } else {
                std::cout << "Error: Failed to load library. Make sure " << libName << " exists." << std::endl;
                currentLib = 0;
            }
        }
        else if (command == "1") {
            if (currentLib == 0) {
                std::cout << "Error: No library loaded. Use command '0' to load a library." << std::endl;
                continue;
            }
            
            int A, B;
            if (iss >> A >> B) {
                if (PrimeCount) {
                    int result = PrimeCount(A, B);
                    std::cout << "PrimeCount(" << A << ", " << B << ") = " << result << std::endl;
                } else {
                    std::cout << "Error: PrimeCount function not available" << std::endl;
                }
            } else {
                std::cout << "Error: Please provide two integers A and B" << std::endl;
            }
        }
        else if (command == "2") {
            if (currentLib == 0) {
                std::cout << "Error: No library loaded. Use command '0' to load a library." << std::endl;
                continue;
            }
            
            float A, B;
            if (iss >> A >> B) {
                if (Square) {
                    float result = Square(A, B);
                    if (result >= 0) {
                        std::cout << "Square(" << A << ", " << B << ") = " << result << std::endl;
                    } else {
                        std::cout << "Error: A and B must be positive numbers" << std::endl;
                    }
                } else {
                    std::cout << "Error: Square function not available" << std::endl;
                }
            } else {
                std::cout << "Error: Please provide two numbers A and B" << std::endl;
            }
        }
        else {
            std::cout << "Unknown command. Type 'help' for available commands." << std::endl;
        }
    }
    
    lib.unload();
    return 0;
}