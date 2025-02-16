#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid_child, pid_grandchild1, pid_grandchild2, pid_grandchild3;

    printf("Parent process ID: %d\n", getpid());

    pid_child = fork();

    if (pid_child == 0) { 
        printf("Child process ID: %d\n", getpid());

        pid_grandchild3 = fork();
        if (pid_grandchild3 == 0) {
            printf("Grand Child process ID: %d\n", getpid());
            return 0; 
        }
        wait(NULL); 

        pid_grandchild1 = fork();
        if (pid_grandchild1 == 0) {
            printf("Grand Child process ID: %d\n", getpid());
            return 0; 
        }
        wait(NULL); 

        pid_grandchild2 = fork();
        if (pid_grandchild2 == 0) {
            printf("Grand Child process ID: %d\n", getpid());
            return 0; 
        }
        wait(NULL); 

        return 0; 
    }

    wait(NULL); 
    return 0;
}


