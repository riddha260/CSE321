#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* execute_thread(void* arg) {
    int thread_id = *(int*)arg;
    printf("Thread-%d running\n", thread_id);
    sleep(1); 
    printf("Thread-%d closed\n", thread_id);
    return NULL;
}

int main() {
    pthread_t thread_ids[5]; 
    int thread_numbers[5];  

    for (int t = 0; t < 5; t++) {
        thread_numbers[t] = t + 1; 
        pthread_create(&thread_ids[t], NULL, execute_thread, &thread_numbers[t]);
        pthread_join(thread_ids[t], NULL); 
    }

    return 0;
}

