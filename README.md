# Cache-Analysis

A high-performance cache simulator that compares **Least Recently Used (LRU)** and **Least Frequently Used (LFU)** cache replacement policies using real memory trace data.

## Overview

This simulator processes binary trace files to analyze cache behavior under realistic workloads. It helps determine how different cache replacement algorithms perform with varying memory access patterns, cache sizes, and workload characteristics. This is a critical problem in computer architecture design and optimization.

## Features

**Two cache replacement algorithms**: LRU and LFU with optimal O(1) implementations
- **Multi-threaded simulation**: Run both algorithms in parallel for 2x speedup
- **ChampSim trace support**: Compatible with standard CPU trace formats (64-byte instructions)
- **Result persistence**: Save and review previous simulation results
- **Interactive menu**: User-friendly interface for running experiments
- **Configurable cache sizes**: Test with any number of cache lines

## Cache Implementation Details

### LRU (Least Recently Used) Cache

**Design**: Combines a hash map with a doubly-linked list to track recency order.

**Data Structures**:
- `std::unordered_map<uint64_t, list_iterator>`: Maps cache line addresses to their position in the recency list
- `std::list<uint64_t>`: Maintains addresses in recency order (most recent at back, least recent at front)

**Algorithm**:
- **Hit**: Move accessed address to the back of the list (O(1) with iterator)
- **Miss at capacity**: Evict front of list (LRU), insert new address at back
- **Miss with space**: Insert new address at back

**Time Complexity**:
- Average case: **O(1)** for all operations (hit, miss, eviction)
- Worst case: **O(n)** due to hash table collisions or rehashing

---

### LFU (Least Frequently Used) Cache

**Design**: Uses two hash maps and frequency buckets to track access counts with LRU tie-breaking.

**Data Structures**:
- `std::unordered_map<uint64_t, FrequencyIterator>`: Maps addresses to {frequency, list_iterator}
- `std::unordered_map<int, std::list<uint64_t>>`: Maps frequencies to lists of addresses at that frequency
- `int minFreq`: Tracks the minimum frequency bucket for O(1) eviction

**Algorithm**:
- **Hit**: Remove from old frequency bucket, increment frequency, insert into new frequency bucket
- **Miss at capacity**: Evict LRU entry from `minFreq` bucket, insert new address with frequency=1
- **Miss with space**: Insert new address with frequency=1, set `minFreq=1`

**Time Complexity**:
- Average case: **O(1)** for all operations
- Worst case: **O(n)** due to hash table collisions

---

### Why These Complexities Matter

Both implementations achieve **O(1) average-case performance** through careful use of iterators to avoid linear searches. The worst-case O(n) occurs only with hash collisions (extremely rare with real workloads). This makes them suitable for high-throughput cache simulation on traces with hundreds of millions of memory accesses.

## Problem Solved

Real-world CPU caches must choose between competing replacement policies. This simulator addresses the challenge of **comparing LRU and LFU performance** by:

1. **Using realistic workloads**: ChampSim traces from SPEC CPU benchmarks capture actual program behavior
2. **Measuring key metrics**: Hit rate, miss rate, and access counts quantify cache effectiveness
3. **Supporting varied configurations**: Test different cache sizes to find optimal capacity for each policy
4. **Revealing workload sensitivity**: Shows when LRU adapts better (phase changes) vs. when LFU excels (stable access patterns)

Results demonstrate why **LRU dominates in real hardware**: it's simpler, cheaper to implement due to less hardware overhead, and adapts quickly to program phase changes, whereas LFU without can suffer when workloads shift.

## Requirements

- **C++17 or newer**
- **GCC 9+ or Clang 9+** (for `<filesystem>` support)
- Make (for building)

### Check your GCC version:
`g++ --version`

If you have GCC 7 or 8, the Makefile will automatically link `-lstdc++fs`. ***HOWEVER***, the project has the most success during the compilation process if you are using GCC 9+ so it is **HIGHLY** recommended that you upgrade your GCC to the latest version for full compatibility with the code base!!!

## Project Structure
```
Project2/
├── include/ # Header files (.h)
│ ├── LRUCache.h
│ ├── LFUCache.h
│ ├── TraceParser.h
│ └── MenuUtils.h
├── src/ # Implementation files (.cpp)
│ ├── LRUCache.cpp
│ ├── LFUCache.cpp
│ ├── TraceParser.cpp
│ ├── MenuUtils.cpp
│ └── main.cpp
├── build/ # Compiled object files (auto-generated)
├── previous_runs/ # Saved simulation results (auto-generated)
├── Makefile
└── README.md
```

## Compilation

### Standard Build
`make`

### Debug build (with -g flag)
`make debug`

### Clean build artifacts
`make clean`
 
## Getting Trace Files
Download ChampSim traces from: https://dpc3.compas.cs.stonybrook.edu/champsim-traces/speccpu/

Example:
`wget https://dpc3.compas.cs.stonybrook.edu/champsim-traces/speccpu/403.gcc-48B.champsimtrace.xz
xz -d 403.gcc-48B.champsimtrace.xz`

## Running the Simulator

### Main Menu

```
Main Menu:
1. Run Cache simulation
2. View previous simulation results
3. Exit
```

### Option 1: Run Cache Simulation

When you select **Option 1**, you'll be prompted for:

1. **Simulation name** (alphanumeric and underscores only)
   - Example: `test_run_512`, `astar_lru_only`
   - Used as the filename for saving results

2. **Trace file path**
   - Full or relative path to your `.trace` file
   - Example: `traces/473.astar-163B.champsimtrace`

3. **Cache size** (number of cache lines)
   - Each line = 64 bytes
   - Example: `512` (32 KB cache), `1024` (64 KB cache)

4. **Cache type**:
   - `1` - LRU only (single-threaded)
   - `2` - LFU only (single-threaded)
   - `3` - Both (multi-threaded, ~2x faster)

**Example session**:
```
============================================================
                 Welcome to Cache Simulator  
============================================================
 We are simulating memory access patterns with LRU and LFU caching!
-------------------------------------------------------------------
Main Menu:
1. Run Cache simulation
2. View previous simulation results
3. Exit
> 1

Please enter a name for this simulation (alphanumeric and underscores only):
> testing

Please enter the path to your trace file:
> 403.gcc-48B.champsimtrace

Enter the cache size (in number of lines/blocks):
> 1024

Choose cache type to simulate
1. LRU Cache
2. LFU Cache
3. Both
> 3

----------------------------------------------------------
Starting simulation...

---------------------------------------------------------
Run Name: testing
Trace File: 403.gcc-48B.champsimtrace
Cache Size: 1024 lines
Simulation mode: LRU + LFU
------------------------------------------------------
Parsing trace file...
Parsed 2000M instructions...
Parsing complete. Running caches in parallel...

Simulation complete!

=================== Simulation Results ==================

[LRU Cache Results] 
Hits:      1013528839
Misses:    1826632
Hit Rate:  99.8201%

[LFU Cache Results] 
Hits:      1008981699
Misses:    6373772
Hit Rate:  99.3723%

Results have been saved to:
 previous_runs/testing.txt

Main Menu:
1. Run Cache simulation
2. View previous simulation results
3. Exit
> 3

Exiting Cache Simulator. Goodbye!
```
### Option 2: View Previous Results

Lists all saved simulations from `previous_runs/` directory:
- Select a number to view that result file
- Press Enter to return to main menu

### Option 3: Exit

Cleanly exits the simulator.

## Understanding Results

**Hit Rate** = Hits / (Hits + Misses)

- **High hit rate (>95%)**: Cache is effective for this workload and size
- **Low hit rate (<80%)**: Workload has poor locality or cache is too small

## Performance Notes

- **Trace file size**: A 9 GB trace (~150M instructions) processes in 1-3 minutes
- **Multi-threading (mode 3)**: Parses once, runs both caches in parallel for near-2x speedup
- **Memory usage**: Mode 3 stores all addresses in RAM (~2-3 GB for large traces)
- **File Size**: A trace file must be decompressed from .xz format before being ran. Since these trace files are large the time to decompress can be long in some cases. Try to find smaller trace files as some can be over a 100GB large! Custom traces can also be generated and tested by the user!

## Troubleshooting

**"Trace file does not exist"**
- Check file path (use `ls` or `pwd` to verify location)
- Ensure trace is decompressed (`.trace`, not `.trace.xz`)

**"undefined reference to std::filesystem"**
- Your GCC version is 7 or 8, but Makefile didn't link `-lstdc++fs`
- Manually add: `LDFLAGS = -lstdc++fs` in Makefile

**Compilation errors**
- Ensure GCC 9+ or use `-std=c++17` flag
- Run `make clean` then `make` to rebuild from scratch

## Credits

- ChampSim trace format: https://github.com/ChampSim/ChampSim

## License

Academic/Educational use.

