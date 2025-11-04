// Name, etc
// Brett Haensgen
// Lab 9 - System Calls
// Section 121
// pmod.c

#include <unistd.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    nice(10);

    struct timespec t = {1, 837272638};
    nanosleep(&t, NULL);

    printf("Goodbye\n");
    return 0;
}