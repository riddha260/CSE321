#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MaxCrops 5 
#define warehouseSize 5 

sem_t empty; 
sem_t full;  
int in = 0;
int out = 0;
char crops[warehouseSize] = {'R', 'W', 'P', 'S', 'M'}; 
char warehouse[warehouseSize] = {'N', 'N', 'N', 'N', 'N'}; 

pthread_mutex_t mutex;

void display_warehouse_state() {
    printf("Current Warehouse State: ");
    for (int i = 0; i < warehouseSize; i++) {
        printf("%c ", warehouse[i]);
    }
    printf("\n");
}

void *Farmer(void *far) {
    int farmer_id = *(int *)far; 

    for (int i = 0; i < MaxCrops; i++) {
        sem_wait(&empty); 
        pthread_mutex_lock(&mutex); 

        warehouse[in] = crops[in % warehouseSize]; 
        printf("Farmer %d: Insert crops %c at %d\n", farmer_id, crops[in % warehouseSize], in);
        in = (in + 1) % warehouseSize; 

        display_warehouse_state(); 

        pthread_mutex_unlock(&mutex); 
        sem_post(&full); 

        sleep(rand() % 2); 
    }

    pthread_exit(NULL);
}

void *ShopOwner(void *sho) {
    int shop_id = *(int *)sho; 

    for (int i = 0; i < MaxCrops; i++) {
        sem_wait(&full); 
        pthread_mutex_lock(&mutex); 

        printf("Shop owner %d: Remove crops %c from %d\n", shop_id, warehouse[out], out);
        warehouse[out] = 'N'; 
        out = (out + 1) % warehouseSize; 

        display_warehouse_state(); 

        pthread_mutex_unlock(&mutex); 
        sem_post(&empty); 

        sleep(rand() % 2); 
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t Far[5], Sho[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, warehouseSize); 
    sem_init(&full, 0, 0); 

    int a[5] = {1, 2, 3, 4, 5}; 

    for (int i = 0; i < 5; i++) {
        pthread_create(&Far[i], NULL, Farmer, &a[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_create(&Sho[i], NULL, ShopOwner, &a[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(Far[i], NULL);
        pthread_join(Sho[i], NULL);
    }


    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

