#include "LFUCache.h"

// Implementation for LFUCache Class

// Constructor
LFUCache::LFUCache(int capacity) {
    // Set capacity
    this->capacity = capacity;
}

// Reset
void LFUCache::reset() {
    // Reset both maps by clearing them
    this->cacheMap.clear();
    this->freqMap.clear();
}

// Destructor
LFUCache::~LFUCache() {
    // Just call reset when LFUCache object falls out of scope
    // again redundant cuz those maps will be cleaned up anyways
    // but good practice/design :)
    reset();
}