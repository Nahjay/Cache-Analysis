#pragma once

// Relevant Includes
#include <vector>
#include <fstream>
#include <cstdint>
#include <string>

// Relevant Defines / Macros
#define NUM_INSTR_DESTINATIONS 2
#define NUM_INSTR_SOURCES 4


/* Define a struct for the Trace Instruction. This struct outlines the format
for a CRC-2 Trace Instruction, which represents 64 bytes per instruction. 
Once all fields of the instruction have been defined, we will be able to
extract the fields relevant to memory accesses, and use those fields in
the caching algorithms. 
*/ 

/* Before defining the struct, I am using a compiler directive to pack the
struct. This signifies to the compiler that I do NOT want it to insert
additional bytes between struct members, therefore reducing padding. This
is critical because as I read the contents of the trace file, I need the
memory footprint of each instruction to be exactly aligned to 64 bytes
for proper interpretation.
*/
#pragma pack(1)
struct TraceInstruction {
    // Define Format of a CRC-2 Trace Instruction
    // Format taken directly from https://gitlab.ethz.ch/rahbera/champsim/-/blob/master/tracer/champsim_tracer.cpp
    // Using C-Integer types to ensure strict adherence to size of each indivual field in the struct.

    // Instruction Pointer / Program Counter Value
    uint64_t ip;
    // Branch Identifier
    uint8_t is_branch;
    // Branch taken
    uint8_t branch_taken;
    // Destination Registers
    uint8_t destination_registers[NUM_INSTR_DESTINATIONS];
    // Input Registers
    uint8_t input_registers[NUM_INSTR_SOURCES];
    // Destination Memory
    uint64_t destination_memory[NUM_INSTR_DESTINATIONS];
    // Input Memory
    uint64_t input_memory[NUM_INSTR_SOURCES];
    /* The Destination and Input Memory addresses represent the only fields I actually care about in
    this struct in regards to cacheing. They both represent memory accesses and will be translated
    to line tags in the cache if they represent valid addresses (non-zero).
    */
};

// Define Trace Parser Class
class TraceParser {
    private:
        // Private attributes
        // File object for Traces
        std::ifstream traceFile;
    public:
        // Public
        // Constructor
        TraceParser(std::string& filename);
        // Destructor
        ~TraceParser();
};
