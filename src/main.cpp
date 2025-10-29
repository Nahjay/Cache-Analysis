#include "TraceParser.h"
#include "LRUCache.h"
#include <iostream>

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

    // Keep track of instructions and total accesses
    int instructionCount = 0;
    int totalAccesses = 0;

    // Iterate and parse
    while(parser.readInstruction(instruction)) {
        // Increment instruction count
        instructionCount++;

        // Extract the memory addresses from the instruction using the parser object
        std::vector<uint64_t> addresses = parser.extractAddresses(instruction);

        // Iterate through each address extracted
        for (size_t i = 0; i < addresses.size(); i++) {
            // Access each address using the LRUCache object
            lruCache.access(addresses[i]);
            // Increment total acccess
            totalAccesses++;
        }
    }

    // When done print results
    std::cout << "Hits: " << lruCache.getHits() << std::endl;
    std::cout << "Misses: " << lruCache.getMisses() << std::endl;
    std::cout << "Hit Rate: " << lruCache.getHitRate() << std::endl;

}