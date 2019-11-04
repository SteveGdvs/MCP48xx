/*
    This sketch demonstrates how we can output a value in channel A of the MCP4822
    and cycle  through different values in a loop
*/

#include <MCP4822.h>

// Define the MCP4822 instance, giving it the SS (Slave Select) pin
MCP4822 dac(10);

// We define an int variable to store the voltage in mV
int voltage = 100;

void setup() {
    // We call the init() method to initialize the instance
    // The init method will laso initialize the SPI library
    dac.init();

    // The channels are turned off at startup so we need to turn the channel we need on
    dac.turnOnChannelA();

    // We configure the channel A in High gain
    // It is also the default value so it is not really needed
    dac.setGainA(MCP4822::High);
}

void loop() {
    // We set channel A to output the value in voltage
    dac.setVoltageA(voltage);

    // We send the command to the MCP4822
    // This is needed every time we make any change
    dac.updateDAC();


    // The maximux value that the MCP4822 can output is 4095 mV
    // so when we go higher we start again from 100 mV
    if (voltage > 4095) {
        voltage = 100;
    }

    voltage = voltage + 100;

    delay(1000);
}
