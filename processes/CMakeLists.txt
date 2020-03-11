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

add_executable(echoall echoall.c)
target_link_libraries(echoall unixprog)

add_executable(exec exec.c)
target_link_libraries(exec unixprog)

add_executable(interp interp.c)
target_link_libraries(interp unixprog)

add_executable(testsystem testsystem.c)
target_link_libraries(testsystem unixprog)

add_executable(usesystem usesystem.c)
target_link_libraries(usesystem unixprog)

add_executable(printuids printuids.c)
target_link_libraries(printuids unixprog)

add_executable(nice nice.c)
target_link_libraries(nice unixprog)

add_executable(times times.c)
target_link_libraries(times unixprog)

