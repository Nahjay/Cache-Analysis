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
    // Returns true or false based on whether or not an address has been
    // found in the cache.

    // Check if address is in the cache
    if (this->cacheMap.find(address) != this->cacheMap.end()) {
        // Address was inside the cache

        // Add to hits
        this->hits++;

        // Move this memory access to the back of the LL
        // Get the iterator pointing to the node
        auto it = this->cacheMap[address];
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

        // Check the capacity of the cache before adding the new address
        if (this->cacheMap.size() >= capacity) {
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
        } else {
            // Add to the cache if we are not at capacity
            // First we need to create an iterator for next address we are adding
        }




        // Return false
        return false;
    }
}