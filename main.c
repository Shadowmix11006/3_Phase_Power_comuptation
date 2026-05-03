#include <stdio.h>
#include "string.h"
#include "IO.h"
#include "Computation.h"
#include "stdlib.h"
#include "batch.h"


int main() {
    int total_records = 0; // ounts the number of samples in csv
    int count = 0; // counts the number of times compute funtion has run
    char filePath[256]; // defninf the maximum size of the string
    int y = 0; // varuable for the loop
    FILE *file = 0; // FILE variale to store outpute file ptr and pass onto computation
    waveform_sample *ptr = 0; // the pointer to the strt returned by IO

    // main loop to reinter file path or directory if needed
    do {
    printf("Enter the file path or directory path : \n");
    fgets(filePath, sizeof(filePath),stdin); // using f gets instead of scan f to make it more professinal and work better//
    printf("Is this is right file location?\n %s \npres 1 for yes and 0 for no and input the file type again:\n",  filePath);
    scanf("%d", &y);
    filePath[strcspn(filePath, "\n")] = 0;// strips \n from file path

    if (y == 1)
        {
            if (strstr(filePath, ".csv")) { // if file is ending with .csv enters this loop

                //Calli funtions to peform actions below
                ptr = IO(filePath, &total_records, &file, "results.txt"); // calling the file open function
                int size = sizeof(waveform_sample);//calculating size to pass into computation

                //computation
                computation(&(ptr->phase_A_voltage), &ptr->Health_A, total_records, size, file, &count,'A');// computing diffrent metrics phase A
                computation(&(ptr->phase_B_voltage), &ptr->Health_B, total_records, size, file, &count,'B');// computing diffrent metrics Phase B
                computation(&(ptr->phase_C_voltage), &ptr->Health_C, total_records, size, file, &count,'C');// computing diffrent metrics phase C
                printf("File result has been updated");
            } else {
                while ((getchar()) !='\n'); // this is to clear the buffer so we dont misinterprest the enter or \n when this loops
                //printf("Is this is right file directory?\n %s \npres 1 for yes and 0 for no and input the file type again:\n",filePath);
                //scanf("%d", &y);
                batch(filePath);
                filePath[strcspn(filePath, "\n")] = 0; // removing the enter key if any pressed

            }
        }
    } while (y == 0);

    // printf("count : %d", count); // test code need to remove
    // freeing memory and closing file
    free(ptr); // freeing memory
    fclose(file); // freeing file ptr memory

    return 0;
}