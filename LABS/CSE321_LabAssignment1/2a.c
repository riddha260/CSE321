#include <stdio.h>

int main() {
    int num1, num2, result;
    printf("first number: ");
    scanf("%d", &num1); 
    printf("second number: ");
    scanf("%d", &num2); 

    if (num1 > num2) {
        result = num1 - num2; 
        printf("First number is greater and the result of subtraction: %d\n", result);
    } 
    else if (num1 < num2) {
        result = num1 + num2; 
        printf("First number is smaller and the result of addition: %d\n", result);
    } 
    else {
        result = num1 * num2; 
        printf("Numbers are equal. Result of multiplication: %d\n", result);
    }

    return 0; 
}

