#include <stdio.h>
#include "stdint.h"
#ifndef IO_h
    #define IO_h

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
    uint8_t Health_A;
    uint8_t Health_B;
    uint8_t Health_C;
}waveform_sample;

waveform_sample* IO(char path[256], int *final_count, FILE **file_out);

#endif