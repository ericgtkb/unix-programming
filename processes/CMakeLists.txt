add_executable(pid pid.c)
target_link_libraries(pid unixprog)

add_executable(shell shell.c)
target_link_libraries(shell unixprog)

add_executable(uidgid uidgid.c)
target_link_libraries(uidgid unixprog)

add_executable(fork fork.c)
target_link_libraries(fork unixprog)

add_executable(vfork vfork.c)
target_link_libraries(vfork unixprog)

add_executable(wait wait.c)
target_link_libraries(wait unixprog)

add_executable(forktwice forktwice.c)
target_link_libraries(forktwice unixprog)

