cmake_minimum_required(VERSION 3.15)
project(unix_programming C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(lib)
add_subdirectory(files)
add_subdirectory(fileio)
add_subdirectory(stdio)
add_subdirectory(processes)
add_subdirectory(datafiles)
add_subdirectory(procenv)
add_subdirectory(procrelation)
add_subdirectory(signals)

