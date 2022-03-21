#include "mbed.h"
#include "../include/Demonstrator_V1_0.h"
#include "../include/HardwareMbed.h"
HardwareMbed hardware_loc;

int main(void)
{
    printf("Main.cpp, %s function\n", __func__);
    Demo_setup(&hardware_loc);

    while (true) {
        Demo_loop();
    }
    return 0;
}