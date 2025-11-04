#include "TraceParser.h"
#include "LRUCache.h"
#include "LFUCache.h"
#include <iostream>
#include <thread>
#include <experimental/filesystem>
#include <regex>
#include <vector>
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
    
    //This is the main menu where we the user would choose what they want to do.
    std::cout << "Main Menu:" << std::endl;
    std::cout << "1.Run Cache simulation" << std::endl;
    std::cout << "2.View previous simulation results" << std::endl;
    std::cout << "3.Exit" << std::endl;

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
            files.push_back(entry.path().filename().string());//if 
        }

    }
    return;
}

// Defining a quick Main for Testing
int main() {
    printHeader();
    ensurePreviousRunsDir();

    std::string mainMenu;//made an string for getline for the user to pick an option in the main menu

    while(true){

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
            
        }
        else if(option == 3){//if input is 3 then exit
            break;//Exit
        }
    }





    // // Get the string representing the filename
    // std::string filename = argv[1];
    // // Get the cacheSize
    // int cacheSize = std::atoi(argv[2]);
    // // Use the filename to create a traceparser object
    // TraceParser parser = TraceParser(filename);
    // // Create a TraceInstruction struct to parse/read each instruction into
    // TraceInstruction instruction;

    // // Create Cache objects
    // LRUCache lruCache(cacheSize);
    // LFUCache lfuCache(cacheSize);

    // // Keep track of instructions and total accesses
    // int instructionCount = 0;
    // int totalAccesses = 0;

    // // Iterate and parse
    // while(parser.readInstruction(instruction)) {
    //     // Increment instruction count
    //     instructionCount++;

    //     // Progress every 1M instructions
    // if (instructionCount % 1000000 == 0) {
    //     std::cout << "\rProcessed " << instructionCount / 1000000 
    //               << "M instructions..." << std::flush;
    // }

    //     // Extract the memory addresses from the instruction using the parser object
    //     std::vector<uint64_t> addresses = parser.extractAddresses(instruction);

    //     // Iterate through each address extracted
    //     for (size_t i = 0; i < addresses.size(); i++) {
    //         // Access each address using the LRUCache object
    //         lfuCache.access(addresses[i]);
    //         lruCache.access(addresses[i]);
    //         // Increment total acccess
    //         totalAccesses++;
    //     }
    // }

    // // When done print results
    // std::cout << "Hits: " << lruCache.getHits() << std::endl;
    // std::cout << "Misses: " << lruCache.getMisses() << std::endl;
    // std::cout << "Hit Rate: " << lruCache.getHitRate() << std::endl;
    // std::cout << std::endl;
    // std::cout << "LFU stuff" << std::endl;
    // std::cout << "Hits: " << lfuCache.getHits() << std::endl;
    // std::cout << "Misses: " << lfuCache.getMisses() << std::endl;
    // std::cout << "Hit Rate: " << lfuCache.getHitRate() << std::endl; 

    return 0;

}