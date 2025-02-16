#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t parent_to_child, child_to_grandchild;

    parent_to_child = fork(); 

    if (parent_to_child == 0) { 
        child_to_grandchild = fork(); 

        if (child_to_grandchild == 0) {
            printf("I am grandchild\n");
        } else {
            waitpid(child_to_grandchild, NULL, 0); 
            printf("I am child\n");
        }
    } else {
        waitpid(parent_to_child, NULL, 0); 
        printf("I am parent\n");
    }

    return 0;
}

