#ifndef __RGB_SENSOR__H
#define __RGB_SENSOR__H

#include "interface.h"

typedef struct
{
    uint32_t _temp_green_value;
    uint32_t _temp_red_value;
    uint32_t _temp_blue_value;
    uint32_t _temp_nofilter_value_value;
} rgb_sensor_t;

class rgb_sensor
{
public:
    rgb_sensor()
    :   _green_value{0},
        _red_value{0},
        _blue_value{0},
        _nofilter_value{0}
    {};
    ~rgb_sensor(){};
    void set_rgb_data();

private:
    uint32_t _green_value;
    uint32_t _red_value;
    uint32_t _blue_value;
    uint32_t _nofilter_value;
};

#endif