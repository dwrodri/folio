# folio
A sort of template repo filled with interview-type content.

Eventually I'd like to have a huge test suite that runs through a bunch of 
solutions to common whiteboard problems.

## Disclaimer
The intent of this code is, quite frankly, to help me get hired. My résumé is
[here](https://derekrodriguez.dev/resume.pdf). Once I start working full-time 
I'm probably not going to maintain this code.

The secondary intent is to build a collection of SWE practices + interview 
solutions which demonstrate that I'm not incompetent when it comes to writing 
C++. I might do the same for other languages in the future.

If you're a student, or someone learning C++, the code will probably serve as 
a somewhat useful reference for some of the content that you'd learn in your 
algorithms and data structures course. 

**There is not remotely enough work going into this right now for it to be
considered for production use**.

## Tech Stack
- C++17 support at the moment. I'm considering adding concepts it's not a widely adopted feature yet.
- [CMake 3.12+](https://cmake.org/) build system 
- [Catch2](https://github.com/catchorg/Catch2) + CTest unit tests for the library functionality
- [UBSanitizer](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html) +
[AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html) linked
against all the unit tests for the debug build.
- GitHub CI workflows for running the test suite with GCC 10 + Clang 14 on Debian

## Contents
### Containers
#### SimpleVec
A resizeable generic container, similar to
[`std::vector`](https://en.cppreference.com/w/cpp/container/vector). Maybe
eventually I'll implement an iterator interface.

#### BinaryTree
A generic [binary tree](https://en.wikipedia.org/wiki/Binary_tree). Note that at
the moment, it performs heap allocations for every element! The goal with this
codebase is to focus on correctness first, and then performance second.

#### AVLTree

#### RBTree

### Algorithms
#### Sorts (Bubble Sort / Insertion Sort / Quick Sort)
What it says on the lid. Some quick searches that I wrote for performance
#### DFS 
#### BFS

If you like this content, my résumé is [here](https://derekrodriguez.dev/resume.pdf)
