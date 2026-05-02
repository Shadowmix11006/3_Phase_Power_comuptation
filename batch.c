#include "batch.h"
#include "dirent.h"
#include "stdio.h"
#include "Computation.h"
#include "IO.h"

void batch(char path[256]){
    struct dirent *enter;
    DIR *dir = opendir(path);
    FILE *file;
    int total_records = 0;
    int count = 0;
    char f_name[260];
    char full_name[512];
    char result[] = "_results.txt";

    printf("Starting batch processing........");

    if (dir == NULL){
        printf("Error opening directory");
        return;
    }

    while ((enter = readdir(dir))){
        if (strstr(enter->d_name, ".csv")){
            strcpy(f_name,enter->d_name);
            char full_path[512];
            strcpy(full_name, strcat(f_name, result));
            snprintf(full_path, sizeof(full_path), "%s/%s", path, enter->d_name);

            // doing all computation and rest with csv file
            waveform_sample *log_ptr = IO(full_path, &total_records, &file, full_name); // calling the file open function
            int size = sizeof(waveform_sample);//calculating size to pass into computation

            //computation
            computation(&(log_ptr->phase_A_voltage), &log_ptr->Health_A, total_records, size, file, &count, 'A');// computing diffrent metrics phase A
            computation(&(log_ptr->phase_B_voltage), &log_ptr->Health_B, total_records, size, file, &count, 'B');// computing diffrent metrics Phase B
            computation(&(log_ptr->phase_C_voltage), &log_ptr->Health_C, total_records, size, file, &count, 'C');// computing diffrent metrics phase C
            printf("count : %d", count);

        }
    }
}