#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>

struct shared {
    char sel[100];
    int b;
};

int main() {
    int pipefd[2];
    char buffer[100];

    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }
 
    int shmid = shmget(IPC_PRIVATE, sizeof(struct shared), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("Shared memory creation failed");
        exit(1);
    }

    struct shared *shmptr = (struct shared *)shmat(shmid, NULL, 0);
    if (shmptr == (void *)-1) {
        perror("Shared memory attachment failed");
        exit(1);
    }

    shmptr->b = 1000; // Initial balance
    printf("Provide Your Input From Given Options:\n");
    printf("1. Type a to Add Money\n");
    printf("2. Type w to Withdraw Money\n");
    printf("3. Type c to Check Balance\n");

    scanf("%s", shmptr->sel); // Get user selection
    printf("Your selection: %s\n", shmptr->sel);

    pid_t pid = fork();

    if (pid == 0) { 
        // Child Process
        close(pipefd[0]); // Close read end

        if (strcmp(shmptr->sel, "a") == 0) { 
            int amount;
            printf("Enter amount to be added:\n");
            scanf("%d", &amount);
            if (amount > 0) {
                shmptr->b += amount;
                printf("Balance added successfully.\nUpdated balance: %d\n", shmptr->b);
            } else {
                printf("Adding failed, Invalid amount.\n");
            }
        } 
        else if (strcmp(shmptr->sel, "w") == 0) { 
            int amount;
            printf("Enter amount to be withdrawn:\n");
            scanf("%d", &amount);
            if (amount > 0 && amount <= shmptr->b) {
                shmptr->b -= amount;
                printf("Balance withdrawn successfully.\nUpdated balance: %d\n", shmptr->b);
            } else if (amount > shmptr->b) {
                printf("Withdrawal failed, Insufficient balance.\n");
            } else {
                printf("Withdrawal failed, Invalid amount.\n");
            }
        } 
        else if (strcmp(shmptr->sel, "c") == 0) { 
            printf("Your current balance is: %d\n", shmptr->b);
        } 
        else {
            printf("Invalid selection.\n");
        }

        // Write acknowledgment to pipe
        strcpy(buffer, "Thank you for using the service.\n");
        write(pipefd[1], buffer, strlen(buffer) + 1);
        close(pipefd[1]);
        exit(0);
    } 
    else if (pid > 0) { 
        // Parent Process
        close(pipefd[1]); // Close write end
        wait(NULL); // Wait for the child process to finish

        read(pipefd[0], buffer, sizeof(buffer)); // Read acknowledgment
        printf("%s", buffer);
        close(pipefd[0]);

        // Detach and remove shared memory
        shmdt(shmptr);
        shmctl(shmid, IPC_RMID, NULL);
    } 
    else { 
        // Fork failed
        perror("Fork failed");
        exit(1);
    }

    return 0;
}


