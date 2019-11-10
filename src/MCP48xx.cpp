#include "MCP48xx.h"


template<uint8_t BITS_RES>
MCP48xx<BITS_RES>::MCP48xx(uint8_t cs) : cs(cs) {
    /* Setting channel bits*/
    command[Channel::A] = command[Channel::A] | (0u << 15u);
    command[Channel::B] = command[Channel::B] | (1u << 15u);

    SPI.begin();
}

template<uint8_t BITS_RES>
void MCP48xx<BITS_RES>::init() {
    pinMode(cs, OUTPUT);
    digitalWrite(cs, HIGH);
}

template<uint8_t BITS_RES>
MCP48xx<BITS_RES>::~MCP48xx() {
    SPI.end();
}

template<uint8_t BITS_RES>
void MCP48xx<BITS_RES>::setVoltage(uint16_t value, Channel channel) {
    if (value > (1u << BITS_RES) - 1) {
        value = (1u << BITS_RES) - 1;
    } else {
        value = value >> (12u - BITS_RES);
    }
    command[channel] = command[channel] & 0xF000u;
    command[channel] = command[channel] | value;
}

template<uint8_t BITS_RES>
void MCP48xx<BITS_RES>::setVoltageA(uint16_t value) {
    setVoltage(value, Channel::A);
}

template<uint8_t BITS_RES>
void MCP48xx<BITS_RES>::setVoltageB(uint16_t value) {
    setVoltage(value, Channel::B);
}

template<uint8_t BITS_RES>
void MCP48xx<BITS_RES>::shutdownChannel(Channel channel) {
    command[channel] = command[channel] | (0u << 12u);
    if (channel == Channel::A) {
        isAActive = false;
    } else {
        isBActive = false;
    }
}

template<uint8_t BITS_RES>
void MCP48xx<BITS_RES>::shutdownChannelA() {
    shutdownChannel(Channel::A);
}

template<uint8_t BITS_RES>
void MCP48xx<BITS_RES>::shutdownChannelB() {
    shutdownChannel(Channel::B);
}

template<uint8_t BITS_RES>
void MCP48xx<BITS_RES>::turnOnChannel(Channel channel) {
    command[channel] = command[channel] | (1u << 12u);
    if (channel == Channel::A) {
        isAActive = true;
    } else {
        isBActive = true;
    }
}

template<uint8_t BITS_RES>
void MCP48xx<BITS_RES>::turnOnChannelA() {
    turnOnChannel(Channel::A);
}

template<uint8_t BITS_RES>
void MCP48xx<BITS_RES>::turnOnChannelB() {
    turnOnChannel(Channel::B);
}

template<uint8_t BITS_RES>
void MCP48xx<BITS_RES>::setGain(Gain gain, Channel channel) {
    command[channel] = command[channel] | (gain << 13u);
}

template<uint8_t BITS_RES>
void MCP48xx<BITS_RES>::setGainA(Gain gain) {
    setGain(gain, Channel::A);
}

template<uint8_t BITS_RES>
void MCP48xx<BITS_RES>::setGainB(Gain gain) {
    setGain(gain, Channel::B);
}


template<uint8_t BITS_RES>
void MCP48xx<BITS_RES>::updateDAC() {

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
