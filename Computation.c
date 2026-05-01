#include "Computation.h"
#include <math.h>
#include "IO.h"
#include <stdio.h>

void computation(char* ptr, int count, int size, FILE *file, int *run_count, char phase)
{
    double Vrms = 0; // Vrms value
    double sum_sqr = 0; //for sum in funtions
    double sum = 0; // sum
    double min = 0;
    double max = 0;
    double pp = 0; // peak to peak value
    double offset = 0;// DC offset value
    int clip = 0; // numbre of clipped samples
    double var_sum = 0;// sum of variance
    double var = 0;//variance

    //error if no count read by file open
    if (ptr == NULL || count <= 0) {
        printf("Error: No data available for computation.\n");
        return;
    }


    printf("        computation started for phase %c\n", phase);//just put here to make sure it runs
    fprintf(file,"        computation started for phase %c\n\n", phase);//just put here to make sure it runs

    //loop cycling through every value of strut
    for (int i = 0; i < count; i++ ){
        //printf("phase A voltage?:%lf :", *(double)((char*)(ptr+(i*size))));//remove only for testing
        //summation of sqred values
        char* ptr_update = ((char*)(ptr+(i*size)));
        sum_sqr = (sum_sqr + *(double*)((char*)(ptr+(i*size))) * *(double*)((char*)(ptr+(i*size))) );
        var_sum += *(double*)((char*)(ptr+(i*size)));

        //max min for peak-peak
        if (min > *(double*)((char*)(ptr+(i*size)))){
            min = *(double*)((char*)(ptr+(i*size)));
        }
        if (max < *(double*)((char*)(ptr+(i*size)))){
            max = *(double*)((char*)(ptr+(i*size)));
        }

        //DC offset sumation
        sum += *(double*)((char*)(ptr+(i*size)));

        //Clipping detection
        if (*(double*)((char*)(ptr+(i*size))) > 324.9 || *(double*)((char*)(ptr+(i*size))) < -324.9){
            clip++;
            *((uint8_t*)((char*)(ptr+(i*size)+(7-*run_count)*8+*run_count))) = ~*((uint8_t*)((char*)(ptr+(i*size)+(7-*run_count)*8+*run_count))) << 1;// bitwise flg fo clipping

        }

    }

    //final division for RMS calculation of each phase
    Vrms = sqrt(sum_sqr / (double)count);
    //checking tolarance compience below
    if (Vrms < 207 || Vrms > 253){
        fprintf(file, "WOW RMS of Phase %c is outside complient range\n", phase);
    }

    //printing rms value
    fprintf(file,"Calculated RMS : %lf\n", Vrms);// printing out the RMS of each phase

    //peak voltage
    fprintf(file, "Peak voltage : %lf\n", (Vrms*1.4142));

    //peak to peak fr each phase
    pp = (max-min);
    fprintf(file, "max and min are %lf & %lf\n", max, min);
    fprintf(file, "peak to peak value is : %lf\n", pp);

    //DC offset computaion
    offset = ((1/(double)count) * sum);
    fprintf(file, "DC offset is : %lf\n", offset);

    //Clipped sample
    fprintf(file, "No of clipped data points : %d\n", clip);

    for (int i = 0; i < count; i++ ){
        var += *(double*)((char*)(ptr+(i*size))) - (var_sum/(double)count);
    }
    var = var/((double)count-1);
    fprintf(file, "Variance of the phase is : %lf", var);
    fprintf(file, "SD of phase is : %lf\n---------------------------\n\n", (sqrt(var)));

    *run_count += 1; // adds to the number of time the program has been run

};
