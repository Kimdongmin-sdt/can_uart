#include "mbed.h"
#include "src/Demonstrator_V1_0.h"
#include "src/HardwareArduino.h"

HardwareArduino hardware_loc;

int main(void)
{
    printf("Main.cpp, %s function\n", __func__);

    Demo_setup(&hardware_loc);

    while (true) {
        Demo_loop();
    }
    return 0;
}