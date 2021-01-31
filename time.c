#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    if (argc == 0 || argc == 1)
    {
        printf(1, "Error: Insufficient arguments.\n");
        exit();
    }
    int pid = fork();
    if (pid < 0)
        printf(1, "Error: Fork not created.\n");
    else if (pid == 0)
    {
        if (exec(argv[1], argv + 1) < 0)
        {
            printf(1, "Error: Command %s could not be executed.\n", argv[1]);
            exit();
        }
        exit();
    }
    else if (pid > 0)
    {
        int wtime, rtime;
        int wpid = waitx(&wtime, &rtime);
        printf(1, "Process with PID: %d has executed command %s with the following details:-\nWaiting time: %d\n Running time: %d\n", wpid, argv[1], wtime, rtime);
    }

    exit();
}