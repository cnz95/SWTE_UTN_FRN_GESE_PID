#pragma once

#include <cstdint>
#include "serialib.h"

class Serial
{
public:
    ~Serial();
    bool     connect(const char* serial_port,uint32_t baudrate);
    void     disconnect();

    uint32_t rx_available();
    uint8_t  rx_read();

    bool     tx_ready();
    void     tx_write(uint8_t data);
    void     tx_write(const uint8_t *data,uint32_t len);
    void     tx_write(const char* data,uint32_t len);
    void     tx_write(const char* data);
private:
    serialib _com;
};
