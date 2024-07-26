#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *file;
    const char *filename = "example.txt";
    const char *initialText = "Hello, this is my code.\n";
    char buffer[50];
    char userText[100];


    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return EXIT_FAILURE;
    }


    if (fwrite(initialText, sizeof(char), strlen(initialText), file) != strlen(initialText)) {
        perror("Error writing to file");
        fclose(file);
        return EXIT_FAILURE;
    }

   // prompts user to enter text
    printf("Enter additional text to write to the file: ");
    if (fgets(userText, sizeof(userText), stdin) == NULL) {
        perror("Error reading user input");
        fclose(file);
        return EXIT_FAILURE;
    }


    if (fwrite(userText, sizeof(char), strlen(userText), file) != strlen(userText)) {
        perror("Error writing user input to file");
        fclose(file);
        return EXIT_FAILURE;
    }

    fclose(file);

    // Opening the file in read mode
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return EXIT_FAILURE;
    }


    if (fseek(file, 0, SEEK_SET) != 0) {
        perror("Error seeking to beginning of file");
        fclose(file);
        return EXIT_FAILURE;
    }

    printf("Contents of the file:\n");
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }


    fclose(file);

    return EXIT_SUCCESS;
}
