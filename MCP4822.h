#ifndef MCP4822_LIB_MCP4822_H
#define MCP4822_LIB_MCP4822_H

#include <Arduino.h>
#include <SPI.h>


class MCP4822 {

    enum Channel : uint8_t {
        A = 0u, B = 1u
    };

    enum Gain : uint8_t {
        High = 0u, Low = 1u
    };

private:
    const uint8_t cs;
    uint16_t command[2] = {0};
    bool isAActive = false;
    bool isBActive = false;

public:
    explicit MCP4822(uint8_t cs);

    ~MCP4822();

    void init();

    void setVoltage(uint16_t value, Channel channel);

    void setVoltageA(uint16_t value);

    void setVoltageB(uint16_t value);

    void shutdownChannel(Channel channel);

    void shutdownChannelA();

    void shutdownChannelB();

    void turnOnChannel(Channel channel);

    void turnOnChannelA();

    void turnOnChannelB();

    void setGain(Gain gain, Channel channel);

    void setGainA(Gain gain);

    void setGainB(Gain gain);

    void updateDAC();

};


#endif //MCP4822_LIB_MCP4822_H