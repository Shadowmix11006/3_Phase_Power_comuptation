#include <stdio.h>
#include "string.h"
#include "File_open.h"

int main() {
    char filePath[256]; // defninf the maximum size of the string
    int x = 0;

    do {
        x = 0;
        printf("Enter the file path to read csv log fie: \n");
        fgets(filePath, sizeof(filePath),stdin); // using f gets instead of scan f to make it more professinal and work better

        filePath[strcspn(filePath, "\n")] = 0; // removing the enter key if any pressed

        printf("Is this is right file location?\n %s \npres 1 for yes and 0 for no and input the file type again:\n", filePath);
        scanf("%d", &x);
        while ((getchar()) != '\n'); // this is to clear the buffer so we dont misinterprest the enter or \n when this loops

    } while (x == 0); // making a loop to confirm the file location

    File_open(filePath); // calling the file open function

    return 0;
}