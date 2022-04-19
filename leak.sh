EXEC=minishell;
ARGS=$1;
valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --track-origins=yes --log-file=valgrind_log ./$EXEC $ARGS;grep -A1 "valgrind" valgrind_log|grep $EXEC
