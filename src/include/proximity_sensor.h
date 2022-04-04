#ifndef __PROXIMITY_SENSOR__H
#define __PROXIMITY_SENSOR__H

#include "interface.h"

class proximaty_sensor
{
public:
    proximaty_sensor()
    {
        _rpm = 0;
        _input_pin = new DigitalIn(MBED_CONF_APP_PROXIMITY_INPUT_PIN);
    }
    ~proximaty_sensor(){}
    uint32_t                    get_rpm() const;
    void                        set_rpm();

private:
    uint32_t _rpm;
    DigitalIn *_input_pin;

};

#endif