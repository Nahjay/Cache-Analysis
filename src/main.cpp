#include "MenuUtils.h"
#include <iostream>
#include <limits>

// Completing Main
int main() {
    // Print Initial Header
    printHeader();
    // Check if the user already has some stored results
    ensurePreviousRunsDir();

    std::string mainMenu;

    while(true){
        std::cout << "Main Menu:" << std::endl;
        std::cout << "1. Run Cache simulation" << std::endl;
        std::cout << "2. View previous simulation results" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "> ";

        std::getline(std::cin, mainMenu);

        int option;
        try {
            option = std::stoi(mainMenu);
        } catch (const std::exception&) {
            std::cout << "Invalid input. Please enter 1, 2, or 3.\n\n";
            continue;
        }

        if (option < 1 || option > 3) {
            std::cout << "Invalid option. Please enter 1, 2, or 3.\n\n";
            continue;
        }

        if(option == 1){
            runSimulation();
        }
        else if(option == 2){
            listPreviousRuns();
        }
        else if(option == 3){
            std::cout << std::endl;
            std::cout << "Exiting Cache Simulator. Goodbye!\n";
            break;
        }
    }

    return 0;
}

