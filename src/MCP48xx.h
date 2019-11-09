#ifndef MCP48XX_LIB_MCP48XX_H
#define MCP48XX_LIB_MCP48XX_H

#include <Arduino.h>
#include <SPI.h>


class MCP48xx {


private:
    const uint8_t cs;
    uint16_t command[2] = {0};
    bool isAActive = false;
    bool isBActive = false;

public:

    enum Channel : uint8_t {
        A = 0u, B = 1u
    };

    enum Gain : uint8_t {
        High = 0u, Low = 1u
    };

    explicit MCP48xx(uint8_t cs);

    ~MCP48xx();

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


#endif //MCP48XX_LIB_MCP48XX_H