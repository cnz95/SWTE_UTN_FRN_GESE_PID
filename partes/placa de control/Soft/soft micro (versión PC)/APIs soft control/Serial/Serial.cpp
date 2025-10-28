#include "Serial.h"
#include "serialib.h"
#include <cstring>

Serial::~Serial()
{
    disconnect();
}
bool Serial::connect(const char* serial_port,uint32_t baudrate)
{
    return (_com.openDevice(serial_port,baudrate) != 1);
}
void Serial::disconnect()
{
    if( _com.isDeviceOpen() )
        _com.closeDevice();
}
uint32_t Serial::rx_available()
{
    return _com.available();
}
uint8_t Serial::rx_read()
{
    char data;
    _com.readChar(&data);
    return data;
}
bool Serial::tx_ready()
{
    return true;
}
void Serial::tx_write(uint8_t data)
{
    tx_write(&data,1);
}
void Serial::tx_write(const uint8_t *data,uint32_t len)
{
    _com.writeBytes(data,len);
}
void Serial::tx_write(const char *data, uint32_t len)
{
    _com.writeBytes(data,len);
}
void Serial::tx_write(const char *data)
{
    _com.writeBytes(data,strlen(data));
}
