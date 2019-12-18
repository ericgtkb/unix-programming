add_executable(in2out in2out.c)
target_link_libraries(in2out unixprog)

add_executable(seek seek.c)
target_link_libraries(seek unixprog)

add_executable(hole hole.c)
target_link_libraries(hole unixprog)

add_executable(fileflags fileflags.c)
target_link_libraries(fileflags unixprog)

