#include "water_temperature.h"
#include "includes.h"

#define arrayLenght 15

double temperatures[arrayLenght];

double generate_temperatures(){
    double temperature = (double)(rand() % 401) / 10.0;
    return temperature;
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

double water_temperature_get(){
    uint8_t index = rand()%arrayLenght;
    // printf("\n%0.1f\n", temperatures[index]);
    return temperatures[index];
}

void water_temperature_init(){
    // printf("\nMock water templerature sensir initialized\n");
    for(uint8_t i = 0; i < arrayLenght; i++){
        temperatures[i] = generate_temperatures();
        // printf("%0.1f ", temperatures[i]);
    }
    // printf("\n");
    sortArray();
}