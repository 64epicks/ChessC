# ChessC
ChessC is a simple, lightweight chess library. It can be easly integrated with any other project or alternatively installed to the libary folder.

## Adding ChessC as a CMake dependency
---
From your CMakeFiles.txt, add the line `add_subdirectory(PATH_TO_CHESSC)`. Then, to link your program add the line `target_link_libraries(ChessC YOUR_PROGRAM)`. To be able to access the headers add either `include_directories(${CHESSC_INCLUDE_DIRS})` to include the headers for all your programs, or add `target_include_directories(YOUR_PROGRAM GLOBAL ${CHESSC_INCLUDE_DIRS})` if you only want to include the headers for a specific program (`GLOBAL` can be changed).

## Installing ChessC as a static library (Linux/Unix only)
First, make sure you are in the right directory, then run `cmake .` to generate build scripts. Then run `make` to compile the library. To install the library into /usr/bin, run `make install`.