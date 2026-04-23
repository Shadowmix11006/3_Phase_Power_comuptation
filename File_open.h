#include <stdio.h>
#ifndef File_open

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

int File_open(char[256]);

#endif
