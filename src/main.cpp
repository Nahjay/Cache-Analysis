#include "TraceParser.h"
#include "LRUCache.h"
#include "LFUCache.h"
#include <iostream>
#include <thread>

void printResults(const std::string& name, int hits, int misses, double hitRate, std::ostream& out) {
    out << "[" << name << " Cache Results] \n";
    out << "Hits:      " << hits << "\n";
    out << "Misses:    " << misses << "\n";
    out << "Hit Rate:  " << std::fixed << std::setprecision(4)
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
    out << "Cache Size: " << cacheSize << " lines\n";
    out << "Cache Mode: " << (mode == 1 ? "LRU" : mode == 2 ? "LFU" : "LRU + LFU") << "\n\n";
    out << "=================== Simulation Results ==================\n\n";
    
    if (mode == 1 || mode == 3) {
        printResults("LRU", lru.getHits(), lru.getMisses(), lru.getHitRate(), out);
    }
    if (mode == 2 || mode == 3) {
        printResults("LFU", lfu.getHits(), lfu.getMisses(), lfu.getHitRate(), out);
    }
    out.close();
}

void runSimulation() {
    std::string filename;
    std::string runName;
    int cacheSize;
    int mode;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), "\n");
    std::cout << "Please enter the name for this simulation (no spaces):\n> ";
    std::getline(std::cin, runName);
    std::string path = "previous_runs/" + runName + ".txt";
    if (fs::exists(path)) {
        std::cout << "A simulation with that name already exists.\n";
        std::cout << "Would you like to overwrite it (y/n): ";
        char answer;
        std::cin >> answer;
        if (answer != 'y' && answer != 'Y') {
            std::cout << "Simulation cancelled.\n";
            return;
        }
    }

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
    std::cout << "Trace File: " << filename << "\n";
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

    TraceParser parser(filename);
    TraceInstruction instruction;
    LRUCache lruCache(cacheSize);
    LFUCache lfuCache(cacheSize);

    int instructionCount = 0;
    while (parser.readInstruction(instruction)) {
        instructionCount++;
        if (instructionCount % 1000000 == 0) {
            std::cout << "\rProcessed " << instructionCount / 1000000
                    << "M instructions..." << std::flush;
        }

        for (auto addr : parser.extractAddresses(instruction)) {
            if (mode == 1) {
                lruCache.access(addr);
            } else if (mode == 2) {
                lfuCache.access(addr);
            } else {
                lruCache.access(addr);
                lfuCache.access(addr);
            }
        }
    }
    std::cout << "Simulation complete \n\n";
    std::cout << "=================== Simulation Results ==================\n\n";
    if (mode == 1 || mode == 3) {
        printResults("LRU", lruCache.getHits(), lruCache.getMisses(), lruCache.getHitRate(), std::cout);
    }
    if (mode == 2 || mode == 3) {
        printResults("LFU", lfuCache.getHits(), lfuCache.getMisses(), lfuCache.getHitRate(), std::cout);
    }
    saveResultsToFile(runName, filename, cacheSize, mode, lruCache, lfuCache);
    std::cout << "Results have been saved to:\n previous_runs/" << runName << ".txt\n\n";

}
