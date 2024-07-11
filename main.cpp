
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "max30102.hpp"

uint32_t approxRollingAverage (uint32_t avg, uint32_t new_sample, uint32_t N) {
    avg -= avg / N;
    avg += new_sample / N;
    return avg;
}

int main() {

    // init uart
    stdio_init_all();
    printf("Start\n");

    max30102 device;
    uint32_t sample;
    uint32_t avg;
    uint32_t samples[32];

    while(true){
        
        // read red and ir data from fifo
        device.read_fifo();
        uint8_t read = device.read_fifo_read_ptr();
        sample = device.spo2;
        samples[read] = sample;

        // print smoothed out data
        uint32_t sum=0;
        for(uint8_t i = 0; i < 31; i++){
            sum+=samples[i];
        }
        uint32_t avg = sum/32;
        printf("%d\n",avg);

        // print die temperature
        double temp = device.read_temperature();
        printf("%f°c\n",temp);

    }

    return 0;
}
