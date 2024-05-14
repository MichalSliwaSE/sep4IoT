#include "water_temperature.h"
#include <stdio.h>
#include <stdlib.h>
#include "includes.h"

#define arrayLenght 30

int temperatures[arrayLenght];
static int start_index = (int)arrayLenght/2;


int* generate_temperatures(){
    int number = 1;
    for(uint8_t i = 0; i < arrayLenght; i++){
        temperatures[i] = number;
        number++;
        // printf("%0.1f ", temperatures[i]);
    }
    return temperatures;
}

int compare(const void *a, const void *b) {
    int *ptr_a = (int *)a;
    int *ptr_b = (int *)b;

    return (*ptr_a - *ptr_b);
}

void sortArray(){
    size_t arr_size = sizeof(temperatures) / sizeof(temperatures[0]);

    // Sort the array using qsort
    qsort(temperatures, arr_size, sizeof(int), compare);

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

int water_temperature_get(){
    if((int)rand()%2 == 0 && start_index < arrayLenght){
        start_index++;
    }else{
        start_index--;
    }
    return temperatures[start_index];
    // printf("\n%0.1f\n", temperatures[index]);
}