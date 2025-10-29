// Implementation of Trace Parser Class
#include "TraceParser.h"

// Constructor
TraceParser::TraceParser(std::string& filename) {
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