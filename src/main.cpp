#include "TraceParser.h"
#include "LRUCache.h"
#include "LFUCache.h"
#include <iostream>
#include <thread>

void printResults(const std::string& name, int hits, int misses, double hitRate, std::ostream& out) {
    out << "[" << name << " Cache Results] \n";
    out << "Hits:      " << hits << "\n";
    out << "Misses:    " << misses << "\n";
    out << "Hit Rate:  " << std::fixed << std::setprecision(4);
        << hitRate * 100 << "%\n\n";
}

void saveResultsToFile (const std::string& filename, const std::string& tracefile, int cacheSize,  int mode, const LRUCache& lru, const LFUCache& lfu) {
    ensurePreviousRunsDir();
    std::string path = "previous_runs/" + filename + ".txt";
    std::ofstream out(path);
    if (!out.is_open()) {
        std::cerr << "Error: could not save results to file. \n";
        return;
    }
    out << "Simulation Name: " << filename << "\n";
    out << "Trace file: " << tracefile << "\n";
    out << "Cache Size " << cacheSize << "lines\n";
    out << "Cache Mode " << (mode == 1 ? "LRU": mode == 2 ? "LFU": "LRU + LFU") << "\n\n";
    out << "=================== Simulation Results ==================\n\n";
    
    if (mode == 1 || mode == 3) {
        printResults("LRU, lru.getHits(), lru.getMisses(), lru.getHitRate(), out");
    }
    if (mode == 2 || mode == 3) {
        printResults("LFU, lfu.getHits(), lfu.getMisses(), lfu.getHitRate(), out");
    }
    out.close();
}

void runSimulation() {
    std::string filename;
    std::string runName;
    int cacheSize;
    int mode;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), "\n");
    std::cout << "\nPlease enter the path to your .trace file:\n> ";
    std::getline(std::cin, filename);

    std::cout << "\nEnter the cache size (in number of lines/blocks):\n> ";
    std::cin >> cacheSize;

    std::cout << "\nChoose cache type to simulate\n";
    std::cout << "1. LRU Cache\n";
    std::cout << "2. LFU Cache\n";
    std::cout << "3. Both\n> ";
    std::cin >> mode;

    std::cout << "\n----------------------------------------------------------\n";
    std::cout << "Starting simulation...\n";
    std::cout << "\n---------------------------------------------------------\n";
    std::cout << "Run Name: " << runName << "\n";
    std::cout << "Trace File: " << tracefile << "\n";
    std::cout << "Cache Size: " << cacheSize << " lines\n";
    std::cout << "Simulation mode: ";
    if (mode == 1) {
        std::cout << "LRU Only\n";
    }
    else if (mode == 2) {
        std::cout << "LFU Only\n";
    }
    else {
        std::cout << "LRU + LFU\n";
    }
    std::cout << "------------------------------------------------------\n";

    
}



// Defining a quick Main for Testing
int main(int argc, char* argv[]) {
    // Get the string representing the filename
    std::string filename = argv[1];
    // Get the cacheSize
    int cacheSize = std::atoi(argv[2]);
    // Use the filename to create a traceparser object
    TraceParser parser = TraceParser(filename);
    // Create a TraceInstruction struct to parse/read each instruction into
    TraceInstruction instruction;

    // Create Cache objects
    LRUCache lruCache(cacheSize);
    LFUCache lfuCache(cacheSize);

    // Keep track of instructions and total accesses
    int instructionCount = 0;
    int totalAccesses = 0;

    // Iterate and parse
    while(parser.readInstruction(instruction)) {
        // Increment instruction count
        instructionCount++;

        // Progress every 1M instructions
    if (instructionCount % 1000000 == 0) {
        std::cout << "\rProcessed " << instructionCount / 1000000 
                  << "M instructions..." << std::flush;
    }

        // Extract the memory addresses from the instruction using the parser object
        std::vector<uint64_t> addresses = parser.extractAddresses(instruction);

        // Iterate through each address extracted
        for (size_t i = 0; i < addresses.size(); i++) {
            // Access each address using the LRUCache object
            lfuCache.access(addresses[i]);
            lruCache.access(addresses[i]);
            // Increment total acccess
            totalAccesses++;
        }
    }

    // When done print results
    std::cout << "Hits: " << lruCache.getHits() << std::endl;
    std::cout << "Misses: " << lruCache.getMisses() << std::endl;
    std::cout << "Hit Rate: " << lruCache.getHitRate() << std::endl;
    std::cout << std::endl;
    std::cout << "LFU stuff" << std::endl;
    std::cout << "Hits: " << lfuCache.getHits() << std::endl;
    std::cout << "Misses: " << lfuCache.getMisses() << std::endl;
    std::cout << "Hit Rate: " << lfuCache.getHitRate() << std::endl;

}