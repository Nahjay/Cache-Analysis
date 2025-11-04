#pragma once

#include <string>
#include "LRUCache.h"
#include "LFUCache.h"

// Header/Menu functions
void printHeader();
void printResults(const std::string& name, int hits, int misses, double hitRate, std::ostream& out);

// File operations
bool ensurePreviousRunsDir();
bool validData(const std::string& filename);
void saveResultsToFile(const std::string& filename, const std::string& tracefile, 
int cacheSize, int mode, const LRUCache& lru, const LFUCache& lfu);

// Menu functions
void runSimulation();
void listPreviousRuns();