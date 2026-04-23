#include "File_open.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

int x = 0;
int y = 0;
// Opening a file location which has been taken from the user
int File_open(char path[256])
{
    printf("File_open in progress\n");
    FILE *file;
    file = fopen(path, "r");

    //Making sure errors are spotted and explained to the user with path name which ahs been inputed
    if (file == NULL)
{
        printf("Error opening file %s\n", path);
        return 1;
}

    int read = 0; // number of rows or lines read and put into strut
    int record = 0; // line in file also total number of lines in file
    char buff[256];// buffer charector

    // using a loop with fgets so it eds at each \n and increments thereby counting the number of line **THIS IS PROBABLY HELLA INEFFICENT**
    do {
        fgets(buff, sizeof(buff), file);
        record++;
    }while(!feof(file));


    printf("Number of lines ditected is %d \n", record);
    rewind(file);

    // Processing file into struct into memory
    waveform_sample *log = (waveform_sample*)malloc(record*sizeof(waveform_sample));
    if (log == NULL){
        printf("memory allocation failed");
        return 1;
    }
    //askign the user if this csv file has a header and skipping it if it does
    x = 0;
    printf("does this file cointain a row of header??\n 1 for yes and 0 for no :)\n");
    scanf("%d", &x);
    if (x == 1) {
        fgets(buff, sizeof(buff), file);//the line skipper i call it it reads to the next \n or end of line and updates the pointer to that ;)
    }
    record = 0;
do
{
    //defining and reading each element from out csv file read should be 8 if every element of the line has been read
    read = fscanf(file,
                  "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
                  &log[record].timestamp,
                  &log[record].phase_A_voltage,
                  &log[record].phase_B_voltage,
                  &log[record].phase_C_voltage,
                  &log[record].line_current,
                  &log[record].frequency,
                  &log[record].power_factor,
                  &log[record].thd_percent);

    if (read == 8) record++; // increments record by 1 if all 8 have been read successfully

    if (read != 8 && !feof(file)) // Error if cant read opuputting the line and element the error is at
{
            printf("File format incorrect in line %d, element %d \n", record, read);
            printf("would you like me to skip line? 1 for yes and 0 for no\n");   // gives you an option to skip the line
            scanf("%d", &x);
            while ((getchar()) != '\n'); // this is to clear the buffer so we dont misinterprest the enter or \n when this loops
            if (x == 1)
                fgets(buff, sizeof(buff), file);
};
        if (ferror(file)) // Error if file cant be read
{
            printf("Error reading file.\n");
            return 1;
};
} while(!feof(file));

    fclose(file); // closing the file

    // confirming the file has been read right
    printf("\n*** %d records read. ***\n\n", record);

    for (int i = 0; i < record; i++)
        printf("%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
        log[i].timestamp,
        log[i].phase_A_voltage,
        log[i].phase_B_voltage,
        log[i].phase_C_voltage,
        log[i].line_current,
        log[i].frequency,
        log[i].power_factor,
        log[i].thd_percent);
    return 0;
};