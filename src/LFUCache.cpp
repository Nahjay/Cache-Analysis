#include "LFUCache.h"

// Implementation for LFUCache Class

// Constructor
LFUCache::LFUCache(int capacity) {
    // Set capacity
    this->capacity = capacity;
}

// Access the Cache by supplying a memory address
bool LFUCache::access(uint64_t address) {
    // Convert the memory into a viable cache line
    uint64_t lineAddress = address >> 6;

    // Check if this address is in the cache (we have a hit!)
    if (this->cacheMap.find(lineAddress) != this->cacheMap.end()) {
        // Address was found inside cacheMap!

        // Add to hits
        this->hits++;
        // Get a reference to the struct for the cache line address
        FrequencyIterator& freqIter = this->cacheMap[lineAddress];

        /* Now here is the tricky part!!! I gotta first remove this cacheline
        address from the previous frequency list it was stored in before adding
        it to a new list since its frequency just increased (in regards to the
        second map.)
        */
        // Obtain reference to List of previous frequency
        std::list<uint64_t>& prevFreq = this->freqMap[freqIter.frequency];
        // Remove the address in this list using the iterator for this address
        prevFreq.erase(freqIter.iterator);

        // Cleanup and remove this list from the map if its now empty after this
        // removal to conserve space
        if (prevFreq.empty()) {
            // Erase the list at this frequency
            this->freqMap.erase(freqIter.frequency);
            // Also update minimum frequency if needed
            // Get minFreq
            int minFreq = getMinFreq();
            if (minFreq == freqIter.frequency) {
                // Increment minimum frequency
                minFreq++;
                // Track the new minimum frequency
                setMinFreq(minFreq);
            }
        }

        // Update the frequency of this struct member
        freqIter.frequency++;

        // Now we need to add this address into a new frequency list
        // Get a reference to the new frequency list
        std::list<uint64_t>& newFreq = this->freqMap[freqIter.frequency];
        // Add to the end of this frequency list
        newFreq.push_back(lineAddress);
        // Create a new iterator to update the struct to have the proper iterator
        // for this newly updated list.
        auto it = std::prev(newFreq.end());
        // Update the iterator of this struct member
        freqIter.iterator = it;

        // Return true signifying the address was found in the map
        return true;
    } else {
        // This was a miss :(((

        // Add to misses
        this->misses++;

        // First check if we are at capacity, if we at capacity someone needs
        // to get BOOTED!
        // Get capacity
        int capacity = getCapacity();

        // Check size of cacheMap
        if (this->cacheMap.size() >= size_t(capacity)) {
            // Time to enact the LFU eviction policy!!!
            // Get the line address at the front of the freqMap
            // We can index into that list correctly with the second map
            // because we are keeping track and updating the min freq :))
            
            // Get reference to the LL that contains the address that has been
            // accessed the least
            std::list<uint64_t>& leastLL = this->freqMap[this->minFreq];
            // Assuming this LL (frequency bucket) may have multiple values, the
            // value to evict in question will be at the very front!
            // Get this front value
            uint64_t addressToEvict = leastLL.front();
            // Remove from this LL
            leastLL.pop_front();
            // Remove from cacheMap using this line address
            this->cacheMap.erase(addressToEvict);

            // Check if we can cleanup and remove the LL
            if (leastLL.empty()) {
                // Erase from freqMap too
                this->freqMap.erase(this->minFreq);
            }
        }

        // If a miss has not occurred and we are not at capacity, we can add to the map :)
        // Set minFreq to be 1, because we are adding a new address for the FIRST time
        int minFreq = 1;
        setMinFreq(minFreq);

        // Add this lineAddress to the freqMap List
        // Obtain reference to the List we need to add to
        std::list<uint64_t>& freqList = this->freqMap[minFreq];
        // Add to the back of this vector
        freqList.push_back(lineAddress);
        // Obtain iterator to point to this newly added address
        auto it = std::prev(freqList.end());


        // Create struct to add to cacheMap for this lineAddress
        FrequencyIterator freqIter = {minFreq, it};

        // Add this struct to the Cache Map
        this->cacheMap[lineAddress] = freqIter;

        // Return false since address was not in cache
        return false;
    }
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