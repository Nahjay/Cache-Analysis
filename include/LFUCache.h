#pragma once

// Relevant Includes
#include <map>
#include <unordered_map>
#include <list>
#include <cstdint>
#include <cstddef>

// Define LFU Class
class LFUCache {
    private:
        // Private attributes

        // Cache Relevant Metrics (same as LRU)
        int hits = 0;
        int misses = 0;
        int capacity;
}