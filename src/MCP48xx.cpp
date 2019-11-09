#include "MCP48xx.h"

MCP48xx::MCP48xx(uint8_t cs) : cs(cs) {
    /* Setting channel bits*/
    command[Channel::A] = command[Channel::A] | (0u << 15u);
    command[Channel::B] = command[Channel::B] | (1u << 15u);
}

void MCP48xx::init() {
    SPI.begin();
    pinMode(cs, OUTPUT);
    digitalWrite(cs, HIGH);
}

MCP48xx::~MCP48xx() {
    SPI.end();
}

void MCP48xx::setVoltage(uint16_t value, Channel channel) {
    if (value > 4095) {
        value = 4095;
    }
    command[channel] = command[channel] & 0xF000u;
    command[channel] = command[channel] | value;
}

void MCP48xx::setVoltageA(uint16_t value) {
    setVoltage(value, Channel::A);
}

void MCP48xx::setVoltageB(uint16_t value) {
    setVoltage(value, Channel::B);
}

void MCP48xx::shutdownChannel(Channel channel) {
    command[channel] = command[channel] | (0u << 12u);
    if (channel == Channel::A) {
        isAActive = false;
    } else {
        isBActive = false;
    }
}

void MCP48xx::shutdownChannelA() {
    shutdownChannel(Channel::A);
}

void MCP48xx::shutdownChannelB() {
    shutdownChannel(Channel::B);
}

void MCP48xx::turnOnChannel(Channel channel) {
    command[channel] = command[channel] | (1u << 12u);
    if (channel == Channel::A) {
        isAActive = true;
    } else {
        isBActive = true;
    }
}

void MCP48xx::turnOnChannelA() {
    turnOnChannel(Channel::A);
}

void MCP48xx::turnOnChannelB() {
    turnOnChannel(Channel::B);
}

void MCP48xx::setGain(Gain gain, Channel channel) {
    command[channel] = command[channel] | (gain << 13u);
}

void MCP48xx::setGainA(Gain gain) {
    setGain(gain, Channel::A);
}

void MCP48xx::setGainB(Gain gain) {
    setGain(gain, Channel::B);
}

void MCP48xx::updateDAC() {

    /* begin transaction using maximum clock frequency of 20MHz */
    SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));

    if (isAActive) {
        digitalWrite(cs, LOW); //select device
        SPI.transfer16(command[Channel::A]); // sent command for the A channel
        digitalWrite(cs, HIGH); //deselect device
    }
    if (isBActive) {
        digitalWrite(cs, LOW);
        SPI.transfer16(command[Channel::B]); // sent command for the B channel
        digitalWrite(cs, HIGH);
    }

    SPI.endTransaction();
}
