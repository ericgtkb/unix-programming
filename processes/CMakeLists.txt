add_executable(pid pid.c)
add_executable(shell shell.c)
add_executable(uidgid uidgid.c)

target_link_libraries(pid unixprog)
target_link_libraries(shell unixprog)
target_link_libraries(uidgid unixprog)
