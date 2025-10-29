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