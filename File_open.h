#include <stdio.h>
#ifndef File_open_h
    #define File_open_h

//Defining what is inside the strut
typedef struct
{
    double timestamp;
    double phase_A_voltage;
    double phase_B_voltage;
    double phase_C_voltage;
    double line_current;
    double frequency;
    double power_factor;
    double thd_percent;
}waveform_sample;

waveform_sample* File_open(char path[256], int *final_count);

#endif