#include "LFUCache.h"

// Implementation for LFUCache Class

// Constructor
LFUCache::LFUCache(int capacity) {
    // Set capacity
    this->capacity = capacity;
}

// Setters
void LFUCache::setMinFreq(const int freq) {
    // Update min freq
    this->minFreq = freq;
}

// Getters
// Get Capacity
int LFUCache::getCapacity() const {
    // Return capacity
    return this->capacity;
}

// Get Min Freq
int LFUCache::getMinFreq() const {
    // Return Min Freq
    return this->minFreq;
}

// Get Hits
int LFUCache::getHits() const {
    // Return hits
    return this->hits;
}

// Get Misses
int LFUCache::getMisses() const {
    // Return misses
    return this->misses;
}

// Calculate Hit Rate
double LFUCache::getHitRate() const {
    // Get hits and misses
    int hits = getHits();
    int misses = getMisses();
    // Calculate total
    int total = hits + misses;
    // Calculate result
    if (total == 0) {
        return 0.0;
    } else {
        double hitRate = double(hits) / total;
        // Return
        return hitRate;
    }
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