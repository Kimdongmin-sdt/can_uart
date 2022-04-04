#include "../include/can_interface.h"

using namespace _can_interface;

void can_interface::init_can_comm_interface()
{
    _can_comm         = new CAN(CAN_RX, CAN_TX);  // rx, tx
    _can_sensor_uart  = new BufferedSerial(CAN_SENSOR_TX, CAN_SENSOR_RX); // tx, rx
    _can_comm->frequency(BITRATE_125_K);
}

void can_interface::init_thread()
{
}

can_interface::can_interface()
{
    init_can_comm_interface();

    init_thread();
}

void can_interface::write_to_can_bus()
{

}