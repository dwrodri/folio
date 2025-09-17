# Vectionary
A C++20 application for making HTTP requests to AI image generation services, specifically the Gemini API.

## Features
- Modern C++20 implementation
- Lightweight HTTP client integration using cpp20-http-client
- JSON handling with nlohmann/json
- Simple API for making Gemini image generation requests
- Minimal dependencies with in-tree dependency management

## Prerequisites
- C++20 compatible compiler (GCC 10+, Clang 12+, or MSVC 2019+)
- CMake 3.12+
- OpenSSL (on Linux/macOS) - automatically handled by package managers

## Tech Stack
- **C++20** with modern features and concepts
- [CMake 3.12+](https://cmake.org/) build system with FetchContent dependency management
- [cpp20-http-client](https://github.com/avocadoboi/cpp20-http-client) for HTTP/HTTPS requests
- [nlohmann/json](https://github.com/nlohmann/json) for JSON parsing
- [Catch2](https://github.com/catchorg/Catch2) + CTest unit tests for the library functionality
- [UBSanitizer](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html) +
[AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html) linked
against all the unit tests for the debug build.
- GitHub CI workflows for running the test suite with GCC 10 + Clang 14 on Debian

## Quick Start

### Building
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### Usage
1. Get a Gemini API key from [Google AI Studio](https://makersuite.google.com/app/apikey)
2. Run the application:
```bash
./vectionary your_api_key_here "A beautiful sunset over mountains"
```


## Project Structure
```
vectionary/
├── .github/
│   └── workflows/
│       └── tests.yaml       # GitHub CI workflow
├── .vscode/                 # VSCode configuration
├── apps/
│   ├── CMakeLists.txt       # App build configuration
│   └── VectionaryApp.cpp    # Main application with Gemini integration
├── src/
│   ├── algos/
│   │   └── Sorts.hpp        # Sorting algorithms implementation
│   └── containers/
│       ├── BinaryTree.hpp   # Binary tree data structure
│       └── SimpleVec.hpp    # Vector-like container
├── tests/
│   ├── BinaryTreeTest.cpp   # Binary tree unit tests
│   ├── CMakeLists.txt       # Test build configuration
│   ├── SimpleVecTests.cpp   # SimpleVec unit tests
│   └── SortsTest.cpp        # Sorting algorithms unit tests
├── .clang-format            # Code formatting rules
├── .clang-tidy              # Static analysis configuration
├── .gitignore               # Git ignore patterns
├── CMakeLists.txt           # Main build configuration
├── LICENSE                  # Project license
└── README.md                # This file
```

## Dependencies
All dependencies are automatically fetched at build time via CMake FetchContent:
- **cpp20-http-client v3.0.0**: Modern C++20 HTTP client
- **nlohmann/json v3.11.3**: JSON library for parsing API responses