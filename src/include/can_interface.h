#ifndef __CAN_INTERFACE__H
#define __CAN_INTERFACE__H

#include "interface.h"

#if !DEVICE_CAN
#error [NOT_SUPPORTED] CAN not supported for this target
#endif

namespace _can_interface
{
    #define BITRATE_500_K                  500 * 1000
    #define BITRATE_125_K                  125 * 1000
    #define CAN_RX                         MBED_CONF_APP_IECN_CAN_BOARD_RX
    #define CAN_TX                         MBED_CONF_APP_IECN_CAN_BOARD_TX
}

namespace _can_sensor_interface
{
    #define polling_rate_to_can_sensor     500
    #define BITRATE_500_K                  500 * 1000
    #define BITRATE_125_K                  125 * 1000
    #define CAN_SENSOR_RX                  MBED_CONF_APP_CAN_SENSOR_UART_RX
    #define CAN_SENSOR_TX                  MBED_CONF_APP_CAN_SENSOR_UART_TX
}

class can_interface
{
public :
    can_interface();
    ~can_interface(){}
    void write_to_can_bus();
    void init_can_comm_interface();
    void init_thread();

private:
    CAN                   *_can_comm;
    BufferedSerial        *_can_sensor_uart;
    //Thread                *_can_thread;
};

#endif