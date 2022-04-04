/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#if !DEVICE_CAN
#error [NOT_SUPPORTED] CAN not supported for this target
#endif

#include "../include/interface.h"
#include "../include/rgb_sensor.h"
#include "../include/proximity_sensor.h"
#include "../include/can_interface.h"
#include "../include/uart_interface.h"

#define SENSOR_DATA_MAX_KIND 5
#define SENSOR_DATA_MAX_LEN  6

Ticker ticker;
UnbufferedSerial _can_sensor_uart(MBED_CONF_APP_CAN_SENSOR_UART_TX, MBED_CONF_APP_CAN_SENSOR_UART_RX, 115200);
CAN can_instance(MBED_CONF_APP_IECN_CAN_BOARD_RX, MBED_CONF_APP_IECN_CAN_BOARD_TX);
CANMessage can_sensor_msg;
EventQueue queue(32);
char sensor_data[SENSOR_DATA_MAX_KIND][SENSOR_DATA_MAX_LEN];
char msg_char = 'h';
#define MAX_BUFSIZE 39

void write_to_can_sensor()
{
    const char can_sensor_request_msg[] = ";06\r\n";
    while (true)
    {
        printf("write request to can!\n");
        _can_sensor_uart.write(can_sensor_request_msg, strlen(can_sensor_request_msg));


        ThisThread::sleep_for(1000ms);
    }
}

void write_to_can_bus()
{
    printf("%s !!\n", __func__);
    can_sensor_msg.id = 0x05;
    can_instance.write(can_sensor_msg);
}

void read_from_can_sensor()
{
    bool is_readable = _can_sensor_uart.readable();
        _can_sensor_uart.read(&msg_char, 1);
    if (is_readable) {
    }
#if 0
    char receive_msg_from_can_sensor[MAX_BUFSIZE + 1];
    char msg_char = 0;
    int idx = 0;
    const char STX_CHAR = ';';
    const char END_CHAR = '\n';
    int framer_state = STX_CHAR;
    memset(receive_msg_from_can_sensor, 0x00, sizeof(receive_msg_from_can_sensor));
    bool is_readable = _can_sensor_uart.readable();
    while (is_readable) {
        printf("readable!!\n");
        _can_sensor_uart.read(&msg_char, 1);
        printf("msg_char : %c\n", msg_char);
        receive_msg_from_can_sensor[idx++] = msg_char;
    }

    printf("receive_msg_from_can_sensor : %s\n", receive_msg_from_can_sensor);
    int receive_msg_from_can_sensor_len = strlen(receive_msg_from_can_sensor);
    int sensor_idx = 0;
    int data_idx = 0;
    for (int i = 0; i < receive_msg_from_can_sensor_len; i++) {
        if (receive_msg_from_can_sensor[i] != ',') {
            sensor_data[sensor_idx][data_idx++] = receive_msg_from_can_sensor[i];
        } else {
            sensor_idx++;
            data_idx = 0;
        }
    }

    int can_msg_idx = 0;
    for (int i = 1; i < SENSOR_DATA_MAX_KIND; i++) {
        uint16_t temp = 0;
        sscanf(&(sensor_data[i][0]), "%x", &temp);
        printf("sensor_data[%d] : %s\n", i, sensor_data[i]);
        uint16_t *idx_ptr = &temp;
        for (int j = 0; j < 2; j++) {
            can_sensor_msg.data[can_msg_idx++] = *idx_ptr++;
        }
    }
#endif

    // queue.call(write_to_can_bus);
#if 0
    can_sensor_msg.id = 0x05;
    can_instance.write(can_sensor_msg);
#endif
}

int main()
{
    printf("main()\n");
    can_instance.frequency(125 * 1000);
    //_can_sensor_uart.attach(&read_from_can_sensor, SerialBase::RxIrq);
    Thread t_write_to_can_sensor, t_write_to_can_bus, t_read_from_can_sensor;
    t_write_to_can_sensor.start(write_to_can_sensor);
    t_write_to_can_bus.start(callback(&queue, &EventQueue::dispatch_forever));
    char counter = 0;

    while (1) {
        printf("msg_char : %c\n", msg_char);
        ThisThread::sleep_for(500ms);
    }
}
