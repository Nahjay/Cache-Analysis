#include "TraceParser.h"
#include "LRUCache.h"
#include "LFUCache.h"
#include <iostream>
#include <thread>
#include <experimental/filesystem>
#include <regex>
#include <vector>
#include <fstream>
#include <limits>
namespace fs = std::experimental::filesystem;

void ensurePreviousRunsDir() {
    if (!fs::exists("previous_runs")) {
        fs::create_directory("previous_runs");
        std::cout << "Created 'previous_runs' directory.\n";
    } else {
        std::cout << "'previous_runs' directory already exists.\n";
    }
}


void printHeader(){

    //Creating the Header
    std::cout << "============================================================" << std::endl;
    std::cout << "                 Welcome to Cache Simulator  " << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << " We are simulating memory access patterns with LRU and LFU caching!" << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;

}


bool validData(std::string filename){//Function for filename

    //creating regex obj that requires that filename have only alphabetical letters and underscores
    std::regex obj("^[a-zA-Z0-9_]+$");
    
    //Runs through the string and returns true if it only has allowed characters and false if the string has non-allowed characters
    return std::regex_match(filename, obj);
    
}

void listPreviousRuns(){
    ensurePreviousRunsDir();//ensuring that if there isn't a previous runs directory make new directory
    std::vector<std::string> files;

    for(const auto& entry: fs::directory_iterator("previous_runs")){//go through the previous runs directory

        if(entry.is_regular_file()){
            files.push_back(entry.path().filename().string());//if the file is a regular file then push it into the files vector 
            
            //A regular file is a standard file that contains data, as opposed to other file types 
            // like directories, symbolic links, block devices, or character devices.
        }
    }

    if(files.empty()){//if the vector of files is empty then print no simulations found
        std::cout << "No previous simulations found!" << std::endl;
        return;
    }

    //Making header for results
    std::cout << "============================================================" << std::endl;
    std::cout << "            Previous Simulation Results" << std::endl;
    std::cout << "============================================================" << std::endl;
    

    for(std::size_t i = 0; i < files.size(); i++){
        std::cout << i + 1 << ". " << files[i] << std::endl;
        //ex. 1. FILE_NAMEEE 
        //Printing all the previous files
    }

    std::cout << files.size() + 1 << ". Back to main menu" << std::endl;
     //After Listing all previous files give option to go back to main menu
    
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//clears the newline

    if (choice > 0 && choice <= (int)files.size()) {//check if the choice number is a valid number

        std::string filepath = "previous_runs/" + files[choice - 1]; //the full path to the selected file.
        std::ifstream in(filepath);// This opens the chosen file for reading.

        if (in.is_open()) {//if the file is able to be opened than print its results
            std::cout << "------------------------------------------------------------\n";
            std::cout << "Showing results from: " << files[choice - 1] << "\n";
            std::cout << "------------------------------------------------------------\n";
            std::cout << in.rdbuf();//read everything in the file (in) and basically output everything inside
            std::cout << "------------------------------------------------------------\n";
            std::cout << "Press Enter to return to the main menu...";
            std::cin.get();//This essentially waits for user to press enter and go back to main menu
        }
    }
    

}

// Defining a quick Main for Testing
int main() {
    printHeader();
    ensurePreviousRunsDir();

    std::string mainMenu;//made an string for getline for the user to pick an option in the main menu

    while(true){
        //This is the main menu where we the user would choose what they want to do.
        std::cout << "Main Menu:" << std::endl;
        std::cout << "1.Run Cache simulation" << std::endl;
        std::cout << "2.View previous simulation results" << std::endl;
        std::cout << "3.Exit" << std::endl;

        std::getline(std::cin, mainMenu);
        int option = std::stoi(mainMenu);//Putting the input that was picked as an option and turn it into a integer

        if(option == 1){//if input is 1
            std::cout << "------------------------------------------------------------" << std::endl;
            std::cout << "Please enter a name for this simulation(No Spaces or dashes!!)" << std::endl;

            std::string filename;
            std::cin >> filename;

            if(!validData(filename)){//if the filename is not valid Try again 
                
                std::cout << "Error!" << std::endl;
                std::cout << "Try Again! No Spaces! No dashes!" << std::endl;
                continue;
            }

            runsimulation();//If everything is right run the simulation
        }
        else if(option == 2){
            listPreviousRuns();
        }
        else if(option == 3){//if input is 3 then exit
            break;//Exit
        }
    }



    return 0;

}