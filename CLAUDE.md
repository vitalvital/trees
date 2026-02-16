# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is an **Aliquot Trees** project - a C program for exploring number theory concepts related to aliquot sequences, perfect numbers, and sociable number cycles. The project implements calculations on the "balance function" B(n) and explores paths through iterated applications of this function.

### Mathematical Context

The project generalizes classical number theory concepts (abundant, deficient, and perfect numbers) using a generic balance function B(n). See `docs/math.md` for formal definitions of:
- Balance function B(n) and gain G(n)
- Deficient/abundant/perfect numbers
- Iterated balance function B_k(n)
- Paths and cycles in aliquot sequences

## Build and Run

```bash
# Build the project (creates executable in bin/)
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug

# Or use CLion's build system directly

# Run the program
./bin/trees
```

The program presents an interactive menu with options:
- `p` - Perfectness: Calculate σ(n) - n for a given number
- `i` - Inverse perfectness (not implemented)
- `d` - Destiny: Follow aliquot sequence until it terminates at 1
- `c` - Cycles: Search for sociable number cycles of specified length
- `t` - Test: Run test function for cycle finding with custom parameters

## Architecture

### Core Components

**src/aliquot.h** - Main header defining:
- `struct Number`: Represents a number with its value, prime factorization (factors array, powers array), and metadata
- Function declarations for prime generation, factorization, and aliquot calculations

**src/aliquot.c** - Implementation:
- `generatePrimes()`: Sieve of Eratosthenes implementation that generates primes up to INT_MAX on startup, stored in global `Primes` array
- `factor()`: Prime factorization using trial division, populates `struct Number` with factors and powers
- `perfect()`: Calculates σ(n) - n using the formula: σ(n) = ∏((p^(k+1) - 1)/(p - 1)) for each prime power p^k
- `destiny()`: Iteratively applies balance function until reaching 1, includes fallback overflow handling
- `cycles()`: Searches for sociable cycles of specified length in a given range
- `test()`: Extended cycle finder with up to 8-factor overflow handling

### Key Implementation Details

**Prime Generation**: On program start, generates all primes up to INT_MAX using a memory-efficient sieve, storing only odd primes (2 is handled specially). This one-time cost enables fast factorization throughout the session.

**Factorization**: Uses trial division with the precomputed prime table. For each number, iterates through primes up to √n, tracking prime factors and their powers in the `struct Number`.

**Overflow Handling**: The code has two strategies for calculating σ(n):
1. Standard formula using geometric series (faster, prone to overflow)
2. Nested loop expansion that directly computes all divisor sums (slower, handles larger intermediate values)

When overflow is detected in strategy 1, the code falls back to strategy 2. The nested loops in `destiny()` go 6 levels deep, while `test()` extends to 8 levels.

**Limitations**:
- Uses `unsigned long long` (64-bit), limiting accurate calculations to ~19 digits
- Factorization speed depends on prime density; large primes near 2^64 are slow
- Overflow detection is conservative but not exhaustive

## Code Patterns

**Number Structure Initialization**: Always initialize factor and power arrays to 1:
```c
for (i = 0; i < 50; i++) {
    N.factors[i] = 1;
    N.powers[i] = 1;
}
```

**String to Number Conversion**: Use `strtoll`/`strtoull` with BASE (10) constant:
```c
N.a = strtoll(N.ch, &input_end_ptr, BASE);
```

**Overflow Checks**: Before multiplying A * B, verify: `ULONG_LONG_MAX / A > B`

## Development Notes

- C23 standard is configured in CMakeLists.txt
- Math library (`-lm`) is linked for sqrt() operations
- The project uses CLion conventions (cmake-build-debug directory)
- Main branch is `master`, current work is on `m2` branch
- Executables are output to `bin/` directory (configured via CMAKE_RUNTIME_OUTPUT_DIRECTORY)

## Known TODOs

- Line 167: Refactor variable name 'ch' (misnomer for number string)
- Line 370, 491: TODO comments suggest refactoring overflow handling and testing different perfectness calculation methods
- Line 147: Alternative overflow calculation method needed
- `inverse()` function is unimplemented (line 300-302)