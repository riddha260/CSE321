#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 4

int results[3];
char names[3][100]; 

void* calculate_ascii_sum(void* arg) {
    int index = *(int*)arg;
    int sum = 0;

    for (int i = 0; names[index][i] != '\0'; i++) {
        sum += names[index][i];
    }

    pthread_exit((void*)(long)sum); 
}

void* compare_results(void* arg) {
    if (results[0] == results[1] && results[1] == results[2]) {
        printf("Youreka\n");
    } else if (results[0] == results[1] || results[1] == results[2] || results[0] == results[2]) {
        printf("Miracle\n");
    } else {
        printf("Hasta la vista\n");
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_indices[3]; // Indices for thread arguments

    // Take input for names
    for (int i = 0; i < 3; i++) {
        printf("Enter a name: ");
        scanf("%s", names[i]);
    }

    for (int i = 0; i < 3; i++) {
        thread_indices[i] = i; 
        pthread_create(&threads[i], NULL, calculate_ascii_sum, &thread_indices[i]);
    }


    for (int i = 0; i < 3; i++) {
        void* result;
        pthread_join(threads[i], &result);
        results[i] = (int)(long)result; 
        printf("%s: %d\n", names[i], results[i]); 
    }

    pthread_create(&threads[3], NULL, compare_results, NULL);
    pthread_join(threads[3], NULL); 

    return 0;
}

