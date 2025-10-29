// Implementation of Trace Parser Class
#include "TraceParser.h"

// Constructor
TraceParser::TraceParser(const std::string& filename) {
    // Attempt to open the binary file
    this->traceFile.open(filename, std::ios::binary);
    // Check to ensure we have opened the file correctly
    if (!this->traceFile.is_open()) {
        // Throw an exception
        throw std::runtime_error("Could not open trace file.");
    }
}

// Destructor
TraceParser::~TraceParser() {
    // Close the file
    this->traceFile.close();
}

// Read Method
bool TraceParser::readInstruction(TraceInstruction& instruction) {
    // The return value of this function will be used in a loop
    // It will signify if a read was successful or not from the 
    // trace file.
    // Instead of returning a new struct object on every read, we 
    // are going to constantly update an already instantiated 
    // struct objectas we are passing by reference. Tryna conserve
    // memory here!
    return this->traceFile.read(reinterpret_cast<char*>(&instruction), sizeof(TraceInstruction)).good();
}

// Extract Addresses Method
std::vector<uint64_t> TraceParser::extractAddresses(const TraceInstruction& instruction) {
    // Create a return vector
    std::vector<uint64_t> addresses;
    // Explicity set size to 6 for address vector (at most 2 + 4 address processed at a time)
    addresses.reserve(6);

    // I need to iterate through both fields of the instruction
    // that contain memory addresses. If the address field is non
    // zero, that means a memory access occured in that location,
    // and I can feed this information to the cacheing algorithms.

    // Iterate through destination memory accesses first
    for (int i = 0; i < NUM_INSTR_DESTINATIONS; i++) {
        // Push and add to addresses vector
        if (instruction.destination_memory[i] != 0) {
            // Ensure address is a valid address
            addresses.push_back(instruction.destination_memory[i]);
        }
    }

    // Then iterate through source memory accesses
    for (int i = 0; i < NUM_INSTR_SOURCES; i++) {
        // Push and add to addresses vector
        if (instruction.input_memory[i] != 0) {
            // Ensure address is a valid address
            addresses.push_back(instruction.input_memory[i]);
        }
    }

    // Return vector
    return addresses;
}