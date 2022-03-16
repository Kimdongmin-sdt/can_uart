
//!*****************************************************************************
//!  \file      HardwareArduino.cpp
//!*****************************************************************************
//!
//!  \brief		Generic Hardware Layer abstraction of a physical layer
//!
//!  \author    Markus Gafner (gnm7)
//!
//!  \date      2019-09-13
//!
//!*****************************************************************************
//!
//!	 Copyright 2019 Bern University of Applied Sciences and Balluff AG
//!
//!	 Licensed under the Apache License, Version 2.0 (the "License");
//!  you may not use this file except in compliance with the License.
//!  You may obtain a copy of the License at
//!
//!	     http://www.apache.org/licenses/LICENSE-2.0
//!
//!	 Unless required by applicable law or agreed to in writing, software
//!	 distributed under the License is distributed on an "AS IS" BASIS,
//!	 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//!	 See the License for the specific language governing permissions and
//!	 limitations under the License.
//!
//!*****************************************************************************

//!**** Header-Files ************************************************************
#include "HardwareArduino.h"
#include <SPI.h>
#include <stdio.h>

//!**** Macros ******************************************************************

//!**** Data types **************************************************************

//!**** Function prototypes *****************************************************

//!**** Data ********************************************************************

//!**** Implementation **********************************************************

HardwareArduino::HardwareArduino()
{
    // Define all SPI signals for the Geckoboard as inputs. if not, MOSI cant be thrown to 0V

#if ARDUINO_FUNC
    pinMode(50, in);
    pinMode(52, in);
    pinMode(53, in);
#else
    IOLINK_spi 	  = new SPI(MBED_CONF_APP_IO_LINK_SPI_MOSI,
                           MBED_CONF_APP_IO_LINK_SPI_MISO,
                           MBED_CONF_APP_IO_LINK_SPI_SCK);
	IOLINK_spi_cs = new DigitalOut(MBED_CONF_APP_IO_LINK_SPI_CS, 1);
#endif
}


HardwareArduino::~HardwareArduino()
{
}

//!*****************************************************************************
//!function :      begin
//!*****************************************************************************
//!  \brief        Initialices the Class after generation
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void HardwareArduino::begin(){
#if ARDUINO_FUNC
	Serial.begin(115200);

	Serial.print("\nBeginne mit der Initialisierung\n");

	SPI.begin();
	SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
	delay(1000);

	Serial_Write("Init_SPI finished");
	wait_for(1*1000);
#else
	// Setup the spi for 8 bit data, high steady state clock,
    // second edge capture, with a 1MHz clock rate
	/*
	mode | POL PHA
	-----+--------
	  0  |  0   0
	  1  |  0   1
	  2  |  1   0
	  3  |  1   1
    */
   	printf("\nBeginne mit der Initialisierung\n");

    IOLINK_spi->format(8, 0);				// bit, spi mode
	IOLINK_spi->frequency(SPI_FREQUENCY);
	printf("Init_SPI finished\n");

#define DURATION_MULTIPLE		1
#define SLEEP_DURATION 			1000 * DURATION_MULTIPLE
	ThisThread::sleep_for(SLEEP_DURATION);

#endif
}

//!*****************************************************************************
//!function :      IO_Write
//!*****************************************************************************
//!  \brief        Sets a pin to the specified logical value
//!
//!  \type         local
//!
//!  \param[in]	   PinNames   name of the Pin
//!  			   uint8_t    state of the logical signal
//!
//!  \return       void
//!
//!*****************************************************************************
void HardwareArduino::IO_Write(PinNames pinname, uint8_t state)
{
    PinName pinnumber = get_pinnumber(pinname);
#if ARDUINO_FUNC
	digitalWrite(pinnumber, state);
#else
	DigitalOut output_pin(pinnumber, state);
#endif
}

//!*****************************************************************************
//!function :      IO_PinMode
//!*****************************************************************************
//!  \brief        Sets a pin to the specified mode
//!
//!  \type         local
//!
//!  \param[in]	   PinNames   name of the Pin
//!  			   PinMode    mode of the pin
//!
//!  \return       void
//!
//!*****************************************************************************
void HardwareArduino::IO_PinMode(PinNames pinname, PinMode mode)
{
    PinName pinnumber = get_pinnumber(pinname);
    switch (mode) {
    case out:
        // pinMode(pinnumber, OUTPUT);
        {
            DigitalOut output_pin(pinnumber, 1);
        }
        break;
    case in_pullup:
        // pinMode(pinnumber, INPUT_PULLUP);
        {
            DigitalIn input_pin(pinnumber);
            input_pin.mode(PullUp);
        }
        break;
    case in:
        // pinMode(pinnumber, INPUT);
        {
            DigitalIn output_pin(pinnumber);
        }
        break;
    }
}

//!*****************************************************************************
//!function :      Serial_Write
//!*****************************************************************************
//!  \brief        Writes a c-string to the serial connection
//!
//!  \type         local
//!
//!  \param[in]	   char const * pointer to the data, which gets print out
//!
//!  \return       void
//!
//!*****************************************************************************
void HardwareArduino::Serial_Write(char const * buf)
{
#if ARDUINO_FUNC
	Serial.println(buf);
#else
	printf("%s, buf : %s\n", __func__, buf);
#endif
}

//!*****************************************************************************
//! function :      Serial_Write
//!*****************************************************************************
//!  \brief        Writes a number to the serial connection
//!
//!  \type         local
//!
//!  \param[in]	   int	      the number which should get printed
//!
//!  \return       void
//!
//!*****************************************************************************
void HardwareArduino::Serial_Write(int number)
{
#if ARDUINO_FUNC
    Serial.print(number);
#else
#endif
}

//!*****************************************************************************
//!function :      SPI_Write
//!*****************************************************************************
//!  \brief        Writes some data to the specified SPI-Connection
//!
//!  \type         local
//!
//!  \param[in]	   uint8_t    channel number
//!				   uint8_t*   pointer to the data structure
//!				   uint8_t    length of the data in bytes
//!
//!  \return       void
//!
//!*****************************************************************************
void HardwareArduino::SPI_Write(uint8_t channel, uint8_t * data, uint8_t length)
{
    switch (channel) {
    case 0:
        // Enable chipselect -> output high (low-active)
        IO_Write(port01CS, 0);
        break;
    case 1:
        // Enable chipselect -> output high (low-active)
        IO_Write(port23CS, 0);
        break;
    }

    printf("send, data[0] : 0x%02x,\t data[1] : 0x%02x\n", (data[0]), data[1]);
    for (int i = 0; i < length; i++) {
        data[i] = IOLINK_spi->write(data[i]);
    }

    printf("recv, data[0] : 0x%02x,\t data[1] : 0x%02x\n", (data[0]), (data[1]));

    ThisThread::sleep_for(50ms);
    // Disable chipselect -> output high (low-active)
    IO_Write(port01CS, 1);
    IO_Write(port23CS, 1);
}

//!*****************************************************************************
//!function :      wait_for
//!*****************************************************************************
//!  \brief        delay the thread for the given time
//!
//!  \type         local
//!
//!  \param[in]	   uint32_t    delay time im miliseconds
//!
//!  \return       void
//!
//!*****************************************************************************
void HardwareArduino::wait_for(uint32_t delay_ms)
{
    ThisThread::sleep_for(delay_ms);
}

//!*****************************************************************************
//!function :      get_pinnumber
//!*****************************************************************************
//!  \brief        returns the pinnumber for the given pin (see enum PinNames)
//!
//!  \type         local
//!
//!  \param[in]	   PinNames    the enumerated pinname
//!
//!  \return       the hardware-pinnumber
//!
//!*****************************************************************************
PinName HardwareArduino::get_pinnumber(PinNames pinname)
{
	switch (pinname) {
		case port01CS:		return PB_12;	// SPI0_cs0
		case port01IRQ:		return PD_0;	// empty D port pin number

		case port23CS:		return PC_0;
		case port23IRQ:		return PC_2;
		case port0DI:		return PC_3;
		case port1DI:		return PC_8;
		case port2DI:		return PC_9;
		case port3DI:		return PC_10;

		case port0LedGreen: return PC_11;
		case port0LedRed:	return PC_11;
		case port0LedRxErr:	return PC_11;
		case port0LedRxRdy:	return PC_11;

		case port1LedGreen: return PC_11;
		case port1LedRed:	return PC_11;
		case port1LedRxErr:	return PC_11;
		case port1LedRxRdy:	return PC_11;

		case port2LedGreen: return PC_11;
		case port2LedRed:	return PC_11;
		case port2LedRxErr:	return PC_11;
		case port2LedRxRdy:	return PC_11;

		case port3LedGreen: return PC_11;
		case port3LedRed:	return PC_11;
		case port3LedRxErr:	return PC_11;
		case port3LedRxRdy:	return PC_11;

	}
	return PinName();
}