/*
    This sketch demonstrates how we can output a value in both channels of the MCP4822.
*/

#include <MCP4822.h>

// Define the MCP4822 instance, giving it the SS (Slave Select) pin
MCP4822 dac(10);

// We define an int variable to store the voltage in mV so 500mV = 0.5V
int voltage = 500;

void setup() {
    // We call the init() method to initialize the instance
    // The init method will laso initialize the SPI library
    dac.init();

    // The channels are turned off at startup so we need to turn the channel we need on
    dac.turnOnChannelA();
    dac.turnOnChannelB();

    // We configure the channels in High gain
    // It is also the default value so it is not really needed
    dac.setGainA(MCP4822::High);
    dac.setGainB(MCP4822::High);
}

void loop() {
    // We set channel A to output 500mV
    dac.setVoltageA(voltage);

    // We set channel B to output 1000mV
    dac.setVoltageB(voltage * 2);

    // We send the command to the MCP4822
    // This is needed every time we make any change
    dac.updateDAC();

    // After this the DAC will output 0.5 Volt in channel A and 1 Volt in B

    while (1) {
        // loop forever
    }
}
