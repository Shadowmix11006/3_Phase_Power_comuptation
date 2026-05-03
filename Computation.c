#include "Computation.h"
#include <math.h>
#include "IO.h"
#include <stdio.h>

void computation(char* ptr, uint8_t* health_ptr, int count, int size, FILE *file, int *run_count, char phase)
{
    double Vrms = 0; // Vrms value
    double sum_sqr = 0; //for sum in funtions
    double sum = 0; // sum
    double min = 0; // storing min
    double max = 0; // stong max
    double pp = 0; // peak to peak value
    double offset = 0;// DC offset value
    int clip = 0; // numbre of clipped samples
    double var = 0;//variance
    double mean = 0;// mean

    //error if no count read by file open
    if (ptr == NULL || count <= 0) {
        printf("Error: No data available for computation.\n");
        return;
    }


    printf("computation started for phase %c....\n", phase);//just put here to make sure it runs
    fprintf(file,"  computation started for phase %c\n\n", phase);//just put here to make sure it runs

    //loop cycling through every value of strut
    for (int i = 0; i < count; i++ ){
        double val = *(double*)((char*)(ptr+(i*size)));//converts ugly pointer logic to one nice vaariable
        //summation of sqred values
        sum_sqr = (sum_sqr + val * val );

        //max min for peak-peak
        if (min > val){
            min = val;
        }
        if (max < val){
            max = val;
        }

        //DC offset sumation
        sum += val;
        //printf("clip? : %d\n", *((uint8_t*)((char*)health_ptr + (i * size))));
        //Clipping detection
        if (val > 324.9 || val < -324.9){
            clip++;
            *((uint8_t*)((char*)health_ptr + (i * size))) = (1 << 0); // Set Bit 0 for "Clipped"
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

    //checking tolerence compliance
    if (Vrms > 252 || Vrms < 208) {
        fprintf(file, "Vrms out of 10% tolerance\n");
    }


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
    fprintf(file, "Clipped data below: \n");

    //second loop for variance caluculation and also printing the clipped values based on te helth metric to demonstaste bitwise operation
    mean = (sum / (double)count);
    for (int i = 0; i < count; i++ ){
        double val = *(double*)((char*)(ptr+(i*size))); // same ugly arable conversion
        var += (val - mean) * (val - mean);
        if (*((uint8_t *) ((char *) health_ptr + (i * size))) != 0 ){ //logic to print value based on bitise health
            fprintf(file, "%lf\n" , val);
        }
    }
    var = var/((double)count-1);
    fprintf(file, "Variance of the phase is : %lf\n", var);//pritning variance
    fprintf(file, "SD of phase is : %lf\n---------------------------\n\n", (sqrt(var)));//printing SD

    *run_count += 1; // adds to the number of time the program has been run

};
