#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

static int total_process_count = 1; 

void count_processes(pid_t pid) {
    if (pid == 0) { 
        total_process_count++;
        if (getpid() % 2 != 0) { 
            if (fork() == 0) { 
                total_process_count++;
            }
        }
        _exit(0); 
    }
}

int main() {
    pid_t p1, p2, p3;
    
    p1 = fork();
    count_processes(p1);
    if (p1 > 0) wait(NULL); 

    p2 = fork();
    count_processes(p2);
    if (p2 > 0) wait(NULL); 

    p3 = fork();
    count_processes(p3);
    if (p3 > 0) wait(NULL); 

    if (p1 > 0 && p2 > 0 && p3 > 0) {
        printf("Total number of processes created: %d\n", total_process_count);
    }

    return 0;
}


