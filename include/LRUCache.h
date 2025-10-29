#pragma once

// Relevant Includes
#include <list>
#include <unordered_map>
#include <cstdint>

// Define LRUCache Class
class LRUCache {
    private:
        // Private Attributes

        // Data Structures //
        // List to maintain order of memory accesses
        std::list<uint64_t> lruList;
        // Unordered Map (Hash Map) that stores each address and an iterator
        // that points exactly to where that address resides inside the LRUList.
        // Using an iterator abstract away the gross overhead of raw 
        // pointer management here.
        std::unordered_map<uint64_t, std::list<uint64_t>::iterator> cacheMap;

        // Cache Relevant Metrics
        int capacity;
        // Value was found inside the cache
        int hits;
        // Value was not found inside the cache
        int misses;
    public:
        // Public Methods and Attributes

        // Constuctor
        LRUCache(int capacity);
        // Access to the cache with a specified address in mind
        bool access(uint64_t address);
        // Getters
        int getCapacity() const;
        int getHits() const;
        int getMisses() const;
        double getHitRate() const;
        // Reset
        void reset();
        // Destructor
        ~LRUCache();
};