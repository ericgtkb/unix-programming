set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_library(unixprog error.c pathalloc.c prexit.c)

target_include_directories(unixprog PUBLIC ${INCLUDE_DIR})