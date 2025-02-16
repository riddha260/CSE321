#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char str[100];
    int is_palindrome = 1; 

    printf("Enter a string: ");
    scanf("%s", str);

    char *start = str;                      
    char *end = str + strlen(str) - 1;      

    
    while (start < end) {
        if (tolower(*start) != tolower(*end)) {  
            is_palindrome = 0;                 
            break;
        }
        start++;   
        end--;     
    }

    if (is_palindrome) {
        printf("Palindrome\n");
    } else {
        printf("Not Palindrome\n");
    }

    return 0;
}

