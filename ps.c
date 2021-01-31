#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        printf(1,"Error: Invalid number of arguments.\n");
        exit();
    }
    pinfo();
    exit();
}