set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_library(unixprog error.c)

target_include_directories(unixprog PUBLIC ${INCLUDE_DIR})