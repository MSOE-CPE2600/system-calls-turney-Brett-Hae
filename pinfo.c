// Name, etc
// Brett Haensgen
// Lab 9 - System Calls
// Section 121
// pinfo.c

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/resource.h>
#include <sched.h>
#include <errno.h>

char* string(int s) {
    switch (s) {
        case 0: return "SCHED_OTHER";
        case 1: return "SCHED_FIFO";
        case 2: return "SCHED_RR";
        case 3: return "SCHED_BATCH";
        case 4: return "SCHED_IDLE";
        case 5: return "SCHED_DEADLINE";
        default: return "UNKNOWN";
    }
}

int main(int argc, char* argv[])
{
    pid_t pid;

    if(argc > 1) {
        pid = atoi(argv[1]);
    } else {
        pid = getpid();
    }

    if(kill(pid, 0) != 0) {
        printf("PID does not exist\n");
        return -1;
    }

    int priority = getpriority(PRIO_PROCESS, pid);
    int schedule = sched_getscheduler(pid);

    if(errno == -1 || schedule == -1) {
        printf("Error with priority and/or schedule\n");
        return -1;
    }

    printf("Process ID: %d\nPriority: %d\nScheduling: %s\n", pid, priority, string(schedule));
    return 0;
}