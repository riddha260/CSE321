#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *args[100]; 
    args[0] = "./sort"; 
    int index = 1;

    char *split = strtok(argv[1], ",");
    while (split != NULL) {
        args[index++] = split; 
        split = strtok(NULL, ",");
    }
    args[index] = NULL; 

    pid_t pid = fork();

    if (pid == 0) {
        execv("./sort", args);
        exit(1);
    } else if (pid > 0) {
        wait(NULL); 
        
        args[0] = "./oddeven";
        execv("./oddeven", args);
        exit(1);
    }

    return 0;
}


