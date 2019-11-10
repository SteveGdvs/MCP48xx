/*
    This sketch demonstrates how we can output a value in both channels of MCP4822 or MCP4812 or MCP4802.
*/

#include <MCP48xx.h>

// Define the MCP4822 instance, giving it the SS (Slave Select) pin
// The constructor will also initialize the SPI library
// We can also define a MCP4812 or MCP4802
MCP4822 dac(10);

// We define an int variable to store the voltage in mV so 100mV = 0.1V
int voltage = 100;

void setup() {
    // We call the init() method to initialize the instance

    dac.init();

    // The channels are turned off at startup so we need to turn the channel we need on
    dac.turnOnChannelA();
    dac.turnOnChannelB();

    // We configure the channels in High gain
    // It is also the default value so it is not really needed
    dac.setGainA(MCP4822::High);
    dac.setGainB(MCP4822::High);
}

// We loop from 100mV to 2000mV for channel A and 4000mV for channel B
void loop() {
    // We set channel A to output 500mV
    dac.setVoltageA(voltage);

    // We set channel B to output 1000mV
    dac.setVoltageB(voltage * 2);

    // We send the command to the MCP4822
    // This is needed every time we make any change
    dac.updateDAC();

    if (voltage * 2 > 4000) {
        voltage = 100;
    }

    voltage = voltage + 100;

    delay(1000);
}
