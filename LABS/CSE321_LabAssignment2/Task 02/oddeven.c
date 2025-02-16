#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) { 
        return 1;
    }


    for (int i = 1; i < argc; i++) {
        long num = strtol(argv[i], NULL, 10); 

        if (num % 2 == 0) {
            printf("%ld is even\n", num);
        } else {
            printf("%ld is odd\n", num);
        }
    }

    return 0;
}

