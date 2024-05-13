#include "water_temperature.h"
#include <stdio.h>
#include <stdlib.h>
#include "includes.h"

#define arrayLenght 40

double temperatures[arrayLenght];
static uint8_t index = (int)arrayLenght/2;


double* generate_temperatures(){
    double number = 9.5;
    for(uint8_t i = 0; i < arrayLenght; i++){
        temperatures[i] = number+0.5;
        number+= 0.5;
        // printf("%0.1f ", temperatures[i]);
    }
    return temperatures;
}

int compare(const void *a, const void *b) {
    double *ptr_a = (double *)a;
    double *ptr_b = (double *)b;

    return (*ptr_a - *ptr_b);
}

void sortArray(){
    size_t arr_size = sizeof(temperatures) / sizeof(temperatures[0]);

    // Sort the array using qsort
    qsort(temperatures, arr_size, sizeof(double), compare);

    // Print the sorted array
    // printf("\nSorted array: ");
    // for (size_t i = 0; i < arr_size; i++) {
    //     printf("%0.1f ", temperatures[i]);
    // }
    // printf("\n");
}

void water_temperature_init(){
    // printf("\nMock water templerature sensir initialized\n");
    generate_temperatures();
    // printf("\n");
    sortArray();
}

double water_temperature_get(){
    if((int)rand()%2 == 0 && index < arrayLenght){
        index++;
    }else{
        index--;
    }
    return temperatures[index];
    // printf("\n%0.1f\n", temperatures[index]);
}