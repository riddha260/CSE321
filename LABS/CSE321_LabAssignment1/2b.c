#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *input_file, *output_file;
    char current_char, previous_char = '\0'; 

    input_file = fopen("input.txt", "r");


    output_file = fopen("output.txt", "w");


    while ((current_char = fgetc(input_file)) != EOF) {
        if (!(isspace(current_char) && isspace(previous_char))) {
            fputc(current_char, output_file);
        }
        previous_char = current_char; 
    }

    fclose(input_file);
    fclose(output_file);

    printf("File processed: Extra spaces removed.\n");
    return 0;
}
