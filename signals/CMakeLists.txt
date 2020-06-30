add_executable(usersignals usersignals.c)
target_link_libraries(usersignals unixprog)

add_executable(nonreentrant nonreentrant.c)
target_link_libraries(nonreentrant unixprog)

add_executable(usesleep1 usesleep1.c sleep1.c)
target_link_libraries(usesleep1 unixprog)

add_executable(usesleep2 usesleep2.c sleep2.c)
target_link_libraries(usesleep2 unixprog)

add_executable(readwithtimeout readwithtimeout.c)
target_link_libraries(readwithtimeout unixprog)

add_executable(betterreadwithtimeout betterreadwithtimeout.c)
target_link_libraries(betterreadwithtimeout unixprog)

add_executable(sigprocmask sigprocmask.c)
target_link_libraries(sigprocmask unixprog)

add_executable(siglongjmp siglongjmp.c)
target_link_libraries(siglongjmp unixprog)

add_executable(sigsuspend1 sigsuspend1.c)
target_link_libraries(sigsuspend1 unixprog)

add_executable(sigsuspend2 sigsuspend2.c)
target_link_libraries(sigsuspend2 unixprog)

# Use only one of badsystem.c and bettersystem.c
add_executable(usesystemwithed usesystemwithed.c bettersystem.c)
target_link_libraries(usesystemwithed unixprog)

add_executable(sigtstp sigtstp.c)
target_link_libraries(sigtstp unixprog)

