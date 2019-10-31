#include "MCP4822.h"

MCP4822::MCP4822(uint8_t cs) : cs(cs) {
    /* Setting channel bits*/
    command[MCP4822Channel::A] = command[MCP4822Channel::A] | (1u << 15u);
    command[MCP4822Channel::B] = command[MCP4822Channel::B] | (0u << 15u);

    turnOnChannel(MCP4822Channel::A);
    turnOnChannel(MCP4822Channel::B);
    setGain(MCP4822Gain::High, MCP4822Channel::A);
    setGain(MCP4822Gain::High, MCP4822Channel::B);
}

void MCP4822::init() {
    SPI.begin();
    pinMode(cs, OUTPUT);
    digitalWrite(cs, HIGH);
}

MCP4822::~MCP4822() {
    SPI.end();
}

void MCP4822::setVoltage(uint16_t value, MCP4822Channel channel) {
    if (value > 4095) {
        value = 4095;
    }
    command[channel] = command[channel] | value;
}

void MCP4822::setVoltageA(uint16_t value) {
    if (value > 4095) {
        value = 4095;
    }
    command[MCP4822Channel::A] = command[MCP4822Channel::A] | value;
}

void MCP4822::setVoltageB(uint16_t value) {
    if (value > 4095) {
        value = 4095;
    }
    command[MCP4822Channel::B] = command[MCP4822Channel::B] | value;
}

void MCP4822::shutdownChannel(MCP4822Channel channel) {
    command[channel] = command[channel] | (0u << 12u);
}

void MCP4822::shutdownChannelA() {
    command[MCP4822Channel::A] = command[MCP4822Channel::A] | (0u << 12u);
}

void MCP4822::shutdownChannelB() {
    command[MCP4822Channel::B] = command[MCP4822Channel::B] | (0u << 12u);
}

void MCP4822::turnOnChannel(MCP4822Channel channel) {
    command[channel] = command[channel] | (1u << 12u);
}

void MCP4822::turnOnChannelA() {
    command[MCP4822Channel::A] = command[MCP4822Channel::A] | (1u << 12u);
}

void MCP4822::turnOnChannelB() {
    command[MCP4822Channel::B] = command[MCP4822Channel::B] | (1u << 12u);
}

void MCP4822::setGain(MCP4822Gain gain, MCP4822Channel channel) {
    command[channel] = command[channel] | (gain << 13u);
}

void MCP4822::setGainA(MCP4822Gain gain) {
    command[MCP4822Channel::A] = command[MCP4822Channel::A] | (gain << 13u);
}

void MCP4822::setGainB(MCP4822Gain gain) {
    command[MCP4822Channel::B] = command[MCP4822Channel::B] | (gain << 13u);
}

void MCP4822::updateDAC() {

    /* begin transaction using maximum clock frequency of 20MHz */
    SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
    digitalWrite(cs, LOW); //select device

    SPI.transfer16(command[MCP4822Channel::A]);// sent command for the A channel

    /*prepare the device to receive command for the B channel*/
    digitalWrite(cs, HIGH);
    digitalWrite(cs, LOW);

    SPI.transfer16(command[MCP4822Channel::B]);// sent command for the B channel

    digitalWrite(cs, HIGH); //deselect device
    SPI.endTransaction();
}
