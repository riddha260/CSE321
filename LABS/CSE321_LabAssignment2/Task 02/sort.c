#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a); 
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./sort num1,num2,num3,...\n");
        return 1;
    }

    int size = argc - 1;
    int arr[size];
    for (int i = 0; i < size; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    qsort(arr, size, sizeof(int), compare);

    printf("Sorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

