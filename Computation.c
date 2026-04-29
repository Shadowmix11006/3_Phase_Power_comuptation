#include "Computation.h"
#include <math.h>
#include "File_open.h"
#include <stdio.h>

void computation(double* ptr, int count)
{
    double Vrms = 0; // Vrms value
    double sum_sqr = 0; //for sum in funtions
    double sum = 0; // sum
    double min = 0;
    double max = 0;
    double pp = 0; // peak to peak value
    double offset = 0;// DC offset value
    int clip = 0; // numbre of clipped samples

    //error if no count read by file open
    if (ptr == NULL || count <= 0) {
        printf("Error: No data available for computation.\n");
        return;
    }


    printf("computation started\n");//just put here to make sure it runs

    //loop cycling through every value of strut
    for (int i = 0; i < count; i++ ){
        //printf("phase A voltage?:%lf :", *(ptr+(i*8)));//remove only for testing
        //summation of sqred values
        sum_sqr = (sum_sqr + *(ptr+(i*8)) * *(ptr+(i*8)) );

        //max min for peak-peak
        if (min > *(ptr+(i*8))){
            min = *(ptr+(i*8));
        }
        if (max < *(ptr+(i*8))){
            max = *(ptr+(i*8));
        }

        //DC offset sumation
        sum = (sum + *(ptr+(i*8)));

        //Clipping detection
        if (*(ptr+(i*8)) > 324.9 || *(ptr+(i*8)) < -324.9){
            clip++;
        }

    }

    //final division for RMS calculation of each phase
    Vrms = sqrt(sum_sqr / (double)count);
    //checking tolarance compience below
    if (Vrms < 207 || Vrms > 253){
        printf("WOW RMS of Phase A is outside complient range");
    }

    //printing rms value
    printf("Calculated RMS for:\n phase A : %lf\n", Vrms);// printing out the RMS of each phase

    //peak to peak fr each phase
    pp = (max-min);
    printf("max and min are %lf & %lf\n", max, min);
    printf("peak to peak value is : %lf\n", pp);

    //DC offset computaion
    offset = ((1/(double)count) * sum);
    printf("DC offset is : %lf\n", offset);

    //Clipped sample
    printf("No of clipped ones : %d", clip);
};
