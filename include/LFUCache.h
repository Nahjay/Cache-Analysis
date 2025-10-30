#pragma once

// Relevant Includes
#include <unordered_map>
#include <list>
#include <cstdint>
#include <cstddef>

// Struct definition that will store a frequency value
// and iterator for a cache line address
struct FrequencyIterator {
    int frequency;
    std::list<uint64_t>::iterator iterator;
};

// Define LFU Class
class LFUCache {
    private:
        // Private attributes

        // To get O(1) Time Complexity for the LFU Cache we need to use 2 maps.

        /* The first map will map each cache address to a struct that contains
        the frequency (how many times this cache address has been accessed)
        and then a respective iterator for that cache line address which will
        be integrated into the LL that is used in the second hash map. */
        std::unordered_map<uint64_t, FrequencyIterator> cacheMap;

        /* The second map will map each tracked frequency to a list of cache
        line addresses. This will allow for O(1) lookup when we need to find 
        and remove the cache line that has been accessed the least amount of
        times.
        */
       std::unordered_map<int, std::list<uint64_t>> freqMap;



        // Cache Relevant Metrics (same as LRU)
        int hits = 0;
        int misses = 0;
        int capacity;
        // Keep track of what is the lowest frequency value in the map
        int min_freq;
    public:
        // Public interface

        // Constructor
        LFUCache(int capacity);
};