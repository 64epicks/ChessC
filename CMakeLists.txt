cmake_minimum_required(VERSION 3.9)
project(ChessC VERSION 0.1 DESCRIPTION "Lightweight chess engine")

include(GNUInstallDirs)

# Build options
option(BUILD_CORE     "BUILD_CORE"     ON)
option(BUILD_TESTS    "BUILD_TESTS"    OFF)
option(BUILD_EXAMPLES "BUILD_EXAMPLES" OFF)

# Run tests?
option(RUN_TESTS "RUN_TESTS" OFF)

# Set global variables
set(CHESSC_INCLUDE_DIRS "include/")

if(BUILD_CORE)
    add_library(ChessC SHARED
        src/chessboard.cpp
        src/check.cpp
        src/move.cpp
        src/fen.cpp
        src/solver.cpp
    )
    set_target_properties(ChessC PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER include/chessc.h
    )
    configure_file(ChessC.pc.in ChessC.pc @ONLY)
    target_include_directories(ChessC PRIVATE ${CHESSC_INCLUDE_DIRS})

    install(TARGETS ChessC
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
    install(FILES ${CMAKE_BINARY_DIR}/ChessC.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
    )
endif(BUILD_CORE)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif(BUILD_TESTS)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif(BUILD_EXAMPLES)

if(RUN_TESTS)
    
endif(RUN_TESTS)