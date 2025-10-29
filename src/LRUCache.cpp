#include "LRUCache.h"

// Implementation for LRUCache Class

// Constructor
LRUCache::LRUCache(int capacity) {
    // Set capacity to check against to determine when eviction
    // policy needs to be invoked.
    this->capacity = capacity;
}

// Access
bool LRUCache::access(uint64_t address) {
    // Returns true or false based on whether or not an address block (cache line) has been
    // found in the cache.

    // Create the cache line based on the address
    uint64_t lineAddress = address >> 6;
    // Cache lines are really groups of multiple addresses that are typically 64 byte blocks.
    // so by left right shifting by 6, I truncate the lower bytes of the memory address and convert
    // it into a lineAddress that represents a block of memory addresses.

    // Check if address is in the cache
    if (this->cacheMap.find(lineAddress) != this->cacheMap.end()) {
        // Address was inside the cache

        // Add to hits
        this->hits++;

        // Move this memory access to the back of the LL
        // Get the iterator pointing to the node
        auto it = this->cacheMap[lineAddress];
        // Utilize the splice method on the list class to move
        // the node we have just obtained the iterator for.
        this->lruList.splice(this->lruList.end(), this->lruList, it);
        // The node containing the address we just accessed has now been
        // moved to the end of the LL

        // Return true
        return true;
    } else {
        // Address was NOT inside the cache :(

        // Add to misses
        this->misses++;

        // Get capcaity
        int capacity = getCapacity();

        // Check the capacity of the cache before adding the new address
        if (this->cacheMap.size() >= size_t(capacity)) {
            /* We need to evict a cached value when we are at capacity or more
            LRU means to evit the Least Recently Used value in the cache. This
            value will always be the front of the LL as the tail of the LL is
            always updated to be the most recently accessed value, whether it
            is a hit or has just been added to the cache.
            */
            
            // Get the address at the front of the LL
            uint64_t frontAddress = this->lruList.front();
            // Use this address to remove this cache line from the map
            this->cacheMap.erase(frontAddress);
            // Erase the front element of the LL
            this->lruList.pop_front();
        }

        // Add to the cache if we are not at capacity
        
        // Add the address to the back of the LL
        this->lruList.push_back(lineAddress);
        // I need to create an iterator for next address we are adding
        // to the map. This iterator needs to be the last position aka the back
        // of the LL. I gotta remember that .end() returns an iterator to the position
        // 1 after the last element. Sinec I want the actual last element I need the 
        // Previous position of the end of the list
        auto it = std::prev(lruList.end());
        // Insert both the address and iterator into the map
        this->cacheMap.emplace(lineAddress, it);
        // Return false
        return false;
    }
}

// Getters
int LRUCache::getCapacity() const {
    // Return capacity
    return this->capacity;
}

// Get Hits
int LRUCache::getHits() const {
    // Return hits
    return this->hits;
}

// Get Misses
int LRUCache::getMisses() const {
    // Return misses
    return this->misses;
}

// Calculate Hit Rate
double LRUCache::getHitRate() const {
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
void LRUCache::reset() {
    // Clear all elements from the list
    this->lruList.clear();
    // Clear all elements from the map
    this->cacheMap.clear();
}

// Destructor
LRUCache::~LRUCache() {
    // Reset once this object goes out of scope to free up memory
    // This should happen automatically anways but keeping here just
    // for designs sake :P
    reset();
}