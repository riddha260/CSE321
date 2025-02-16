#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5
#define NUM_INTS_PER_THREAD 5

void* print_numbers(void* arg) {
    int thread_num = *(int*)arg;
    int start = thread_num * NUM_INTS_PER_THREAD + 1; 
    int end = start + NUM_INTS_PER_THREAD - 1;       

    for (int i = start; i <= end; i++) {
        printf("Thread %d prints %d\n", thread_num, i);
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    for (int t = 0; t < NUM_THREADS; t++) {
        thread_args[t] = t;
        pthread_create(&threads[t], NULL, print_numbers, &thread_args[t]);
    }

    for (int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    return 0;
}
