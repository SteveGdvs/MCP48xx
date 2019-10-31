#include "MCP4822.h"

MCP4822::MCP4822(uint8_t cs) : cs(cs) {
    /* Setting channel bits*/
    command[Channel::A] = command[Channel::A] | (0u << 15u);
    command[Channel::B] = command[Channel::B] | (1u << 15u);
}

void MCP4822::init() {
    SPI.begin();
    pinMode(cs, OUTPUT);
    digitalWrite(cs, HIGH);
}

MCP4822::~MCP4822() {
    SPI.end();
}

void MCP4822::setVoltage(uint16_t value, Channel channel) {
    if (value > 4095) {
        value = 4095;
    }
    command[channel] = command[channel] | value;
}

void MCP4822::setVoltageA(uint16_t value) {
    if (value > 4095) {
        value = 4095;
    }
    command[Channel::A] = command[Channel::A] | value;
}

void MCP4822::setVoltageB(uint16_t value) {
    if (value > 4095) {
        value = 4095;
    }
    command[Channel::B] = command[Channel::B] | value;
}

void MCP4822::shutdownChannel(Channel channel) {
    command[channel] = command[channel] | (0u << 12u);
}

void MCP4822::shutdownChannelA() {
    command[Channel::A] = command[Channel::A] | (0u << 12u);
}

void MCP4822::shutdownChannelB() {
    command[Channel::B] = command[Channel::B] | (0u << 12u);
}

void MCP4822::turnOnChannel(Channel channel) {
    command[channel] = command[channel] | (1u << 12u);
}

void MCP4822::turnOnChannelA() {
    command[Channel::A] = command[Channel::A] | (1u << 12u);
}

void MCP4822::turnOnChannelB() {
    command[Channel::B] = command[Channel::B] | (1u << 12u);
}

void MCP4822::setGain(Gain gain, Channel channel) {
    command[channel] = command[channel] | (gain << 13u);
}

void MCP4822::setGainA(Gain gain) {
    command[Channel::A] = command[Channel::A] | (gain << 13u);
}

void MCP4822::setGainB(Gain gain) {
    command[Channel::B] = command[Channel::B] | (gain << 13u);
}

void MCP4822::updateDAC() {

    /* begin transaction using maximum clock frequency of 20MHz */
    SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
    digitalWrite(cs, LOW); //select device

    SPI.transfer16(command[Channel::A]);// sent command for the A channel

    /*prepare the device to receive command for the B channel*/
    digitalWrite(cs, HIGH);
    digitalWrite(cs, LOW);

    SPI.transfer16(command[Channel::B]);// sent command for the B channel

    digitalWrite(cs, HIGH); //deselect device
    SPI.endTransaction();
}
