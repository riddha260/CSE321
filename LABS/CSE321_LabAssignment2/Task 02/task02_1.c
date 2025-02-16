#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int file = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (file < 0) {
        perror("Error opening/creating file");
        return 1;
    }

    char input[100];
    printf("Enter text to save in file or type '-1' to stop :\n");

    while (1) {
        printf("> ");
        fgets(input, sizeof(input), stdin);

        if (strcmp(input, "-1\n") == 0)
            break;

        write(file, input, strlen(input));
    }

    close(file);
    printf("File operation completed.\n");
    return 0;
}

