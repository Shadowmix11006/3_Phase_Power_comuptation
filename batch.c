#include "batch.h"
#include "dirent.h"
#include "stdio.h"
#include "Computation.h"
#include "IO.h"

void batch(char path[256]){
    struct dirent *enter; // dirent structure to enter directory
    DIR *dir = opendir(path); // DIR ptr to open path
    FILE *file; // FILE ptr to open file
    int total_records = 0; // counts total number of samples in a file
    int count = 0; // counts number of times computation has run
    char f_name[260];// file name that was grabbed from file
    char full_name[512];// name of output file genrated sing f anme
    char result[] = "_results.txt"; // string to append to the end of the file name

    printf("Starting batch processing........");

    if (dir == NULL){// error handling
        printf("Error opening directory");
        return;
    }

    //main loop for opening each csv file and reading and computing each on eof them
    while ((enter = readdir(dir))){
        if (strstr(enter->d_name, ".csv")){// makes sure only .csv files are being prcessed
            strcpy(f_name,enter->d_name);// makes _name the name of the file
            char full_path[512];// defines this variable to output
            strcpy(full_name, strcat(f_name, result));//combines file name and reult
            snprintf(full_path, sizeof(full_path), "%s/%s", path, enter->d_name);//makes a string file which we can give to IO to process

            printf("File %s has been updated", full_name);
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