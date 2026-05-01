#include <stdio.h>
#include "string.h"
#include "IO.h"
#include "Computation.h"

int main() {
    char filePath[256]; // defninf the maximum size of the string
    int x = 0;
    int total_records = 0;
    int count = 0;
    FILE *file;

    do {
        x = 0;
        printf("Enter the file path to read csv log fie: \n");
        fgets(filePath, sizeof(filePath),stdin); // using f gets instead of scan f to make it more professinal and work better

        filePath[strcspn(filePath, "\n")] = 0; // removing the enter key if any pressed

        printf("Is this is right file location?\n %s \npres 1 for yes and 0 for no and input the file type again:\n", filePath);
        scanf("%d", &x);
        while ((getchar()) != '\n'); // this is to clear the buffer so we dont misinterprest the enter or \n when this loops

    } while (x == 0); // making a loop to confirm the file location

    //Calli funtions to peform actions below
    waveform_sample *log_ptr = IO(filePath, &total_records, &file); // calling the file open function
    int size = sizeof(waveform_sample);//calculating size to pass into computation

    //computation
    computation(&(log_ptr->phase_A_voltage), total_records, size, file, &count, 'A');// computing diffrent metrics phase A
    computation(&(log_ptr->phase_B_voltage), total_records, size, file, &count, 'B');// computing diffrent metrics Phase B
    computation(&(log_ptr->phase_C_voltage), total_records, size, file, &count, 'C');// computing diffrent metrics phase C
    printf("count : %d", count);

    return 0;
}