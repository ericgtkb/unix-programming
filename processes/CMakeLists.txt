add_executable(pid pid.c)
target_link_libraries(pid unixprog)

add_executable(shell shell.c)
target_link_libraries(shell unixprog)

add_executable(uidgid uidgid.c)
target_link_libraries(uidgid unixprog)

