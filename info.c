// Name, etc
// Brett Haensgen
// Lab 9 - System Calls
// Section 121
// info.c

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <sys/sysinfo.h>


int main(int argc, char* argv[])
{
    // Current time of day
    struct timespec t;
    if(clock_gettime(CLOCK_REALTIME, &t) == 0) {
        long long ns = t.tv_sec * 1000000000 + t.tv_nsec;
        printf("Time in nanoseconds: %lld\n", ns);
    }

    // System network name
    char hostname[100];
    if(gethostname(hostname, 100) == 0 && hostname[0] != '\0') {
        printf("System network name: %s\n", hostname);
    }

    // OS and system hardware
    struct utsname sys;
    if(uname(&sys) == 0) {
        if(sys.sysname[0] != '\0') {
            printf("OS name: %s\n", sys.sysname);
        }

        if(sys.release[0] != '\0' && sys.version[0] != '\0') {
            printf("OS release: %s\nOS version: %s\n", sys.release, sys.version);
        }

        if(sys.machine[0] != '\0') {
            printf("System hardware type: %s\n", sys.machine);
        }
    }

    // Number of CPUs
    int cpu = sysconf(_SC_NPROCESSORS_CONF);
    if(cpu > 0) {
        printf("Number of CPUs: %d\n", cpu);
    }

    // Total and Free Memory
    struct sysinfo mem;
    if(sysinfo(&mem) == 0) {
        long total = mem.totalram;
        long free = mem.freeram;
        printf("Total memory (bytes): %ld\nFree memory (bytes): %ld\n", total, free);
    }

    return 0;
}