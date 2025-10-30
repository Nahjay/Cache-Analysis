#include "TraceParser.h"
#include "LRUCache.h"
#include "LFUCache.h"
#include <iostream>
#include <thread>

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