#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf(1, "Error: Invalid number of arguments.\n");
        exit();
    }
    int newp = 0, pid = 0;
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        newp *= 10;
        newp += (argv[1][i] - '0');
    }
    for (int i = 0; i < strlen(argv[2]); i++)
    {
        pid *= 10;
        pid += (argv[2][i] - '0');
    }
    if(newp < 0 || newp > 100)
    {
        printf(1,"Error: Invalid value of priority.\n");
        exit();
    }
    int oldp = set_priority(newp,pid);
    if(oldp == -1)
        printf(1,"Error: no process exists with given PID.\n");
    else
        printf(1,"Process with PID: %d updated from priority %d to %d.\n",pid,oldp,newp);
    exit();
}