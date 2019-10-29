#ifndef MCP4822_LIB_MCP4822_H
#define MCP4822_LIB_MCP4822_H

#include <Arduino.h>
#include <SPI.h>

enum MCP4822Channel : uint8_t {
    A = 0u, B = 1u
};
enum MCP4822Gain : uint8_t {
    High = 0u, Low = 1u
};

class MCP4822 {


private:
    const uint8_t cs;
    uint16_t command[2]= {0};

public:
    explicit MCP4822(uint8_t cs);

    void init();

    void setVoltage(uint16_t value, MCP4822Channel channel);

    void setVoltageA(uint16_t value);

    void setVoltageB(uint16_t value);

    void shutdownChannel(MCP4822Channel channel);

    void shutdownChannelA();

    void shutdownChannelB();

    void turnOnChannel(MCP4822Channel channel);

    void turnOnChannelA();

    void turnOnChannelB();

    void setGain(MCP4822Gain gain, MCP4822Channel channel);

    void setGainA(MCP4822Gain gain);

    void setGainB(MCP4822Gain gain);

};


#endif //MCP4822_LIB_MCP4822_H