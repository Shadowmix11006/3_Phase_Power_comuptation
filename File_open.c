#include "File_open.h"
#include <stdio.h>
#include <stdlib.h>

// Opening a file location which has been taken from the user
waveform_sample* File_open(char path[256], int *final_count)
{
    static int read = 0; // number of rows or lines read and put into strut
    static int N = 0; // line in file also total number of lines in file
    static int x = 0; // just a placeholder for user to choose
    int records = 0; // variable to update each row of array to strut
    char buff[256];// buffer charector

    printf("File_open in progress\n");//just put here to make sure it funtion has run
    FILE *file;
    file = fopen(path, "r");

    //Making sure errors are spotted and explained to the user with path name which ahs been inputed
    if (file == NULL)
{
        printf("Error opening file %s\n", path);
        return NULL;
}

    // using a loop with fgets so it eds at each \n and increments thereby counting the number of line **THIS IS PROBABLY HELLA INEFFICENT**
    do {
        fgets(buff, sizeof(buff), file);
        N ++;
    }while(!feof(file));

    //showing user how many lines were detected
    printf("Number of lines ditected is %d \n", N);
    rewind(file);

    //allocation memory to the ptr log
    waveform_sample *log = (waveform_sample*)malloc(N*sizeof(waveform_sample));

    //memory allocation failing error :)
    if (log == NULL){
        printf("memory allocation failed");
        return NULL;
    }
    //askign the user if this csv file has a header and skipping it if it does
    x = 0;
    printf("does this file cointain a row of header??\n 1 for yes and 0 for no :)\n");
    scanf("%d", &x);
    if (x == 1) {
        fgets(buff, sizeof(buff), file);//the line skipper i call it it reads to the next \n or end of line and updates the pointer to that ;)
    }

do
{
    //defining and reading each element from out csv file read should be 8 if every element of the line has been read
    read = fscanf(file,
                  "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
                  &log[records].timestamp,
                  &log[records].phase_A_voltage,
                  &log[records].phase_B_voltage,
                  &log[records].phase_C_voltage,
                  &log[records].line_current,
                  &log[records].frequency,
                  &log[records].power_factor,
                  &log[records].thd_percent);

    if (read == 8) {
        records++; // increments record by 1 if all 8 have been read successfully
    }

    if (read != 8 && !feof(file)) // Error if cant read opuputting the line and element the error is at
{
            printf("File format incorrect in line %d, element %d \n", records, read);
            printf("would you like me to skip line? 1 for yes and 0 for no\n");   // gives you an option to skip the line
            scanf("%d", &x);
            while ((getchar()) != '\n'); // this is to clear the buffer so we dont misinterprest the enter or \n when this loops
            if (x == 1){
                fgets(buff, sizeof(buff), file);
            }
};
        if (ferror(file)) // Error if file cant be read
{
            printf("Error reading file.\n");
            return NULL;
};
} while(!feof(file));

if (records < N){
    printf("waring only %d lines were read while a total of %d lines exist", records, N);
};

    fclose(file); // closing the file
    *final_count = records;

    // confirming the file has been read right
    printf("\n*** %d records read. ***\n\n", records);

//    for (int i = 0; i < records; i++)
//        printf("%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
//        log[i].timestamp,
//        log[i].phase_A_voltage,
//        log[i].phase_B_voltage,
//        log[i].phase_C_voltage,
//        log[i].line_current,
//        log[i].frequency,
//        log[i].power_factor,
//        log[i].thd_percent);


    return log;
};