#include "control_io.h"
//#include "Serial/Serial.h"

// PARA EDITAR ESTO EMPEZAR OTRA VERSIÓN //

#include<iostream>//ESTO DESPUÉS VUELA

using namespace std;//ESTO NO SI SE SI DSPS VUELA
// PROVISORIO
bool read_digital_in(digital_in channel)
{
    //
    bool aux_flag = true;
    cout<<"leer entrada:";
    return aux_flag;
}
// PARA EDITAR ESTO EMPEZAR OTRA VERSIÓN //
void write_digital_out(digital_out channel,bool state)
{
    cout<<"setear salida:";
}
// PARA EDITAR ESTO EMPEZAR OTRA VERSIÓN //
bool read_digital_out(digital_out channel)
{
    bool aux_flag = true;
    cout<<"leer salida:";
    return aux_flag;
}
// PARA EDITAR ESTO EMPEZAR OTRA VERSIÓN //
float read_analog_in(analog_in channel)
{
    float aux_float = 11.11;
    if( channel == analog_in::in0 )
        cout<<"leer entrada an0"<<"\n";
    if( channel == analog_in::in1 )
        cout<<"leer entrada an1"<<"\n";
    return aux_float;
}
// PARA EDITAR ESTO EMPEZAR OTRA VERSIÓN //
void write_analog_out(analog_out channel,float value)
{
    if( channel == analog_out::out0 )
        cout<<"escribir salida an0, valor: "<<value<<"\n";
    if( channel == analog_out::out1 )
        cout<<"escribir salida an1, valor: "<<value<<"\n";
}
// PARA EDITAR ESTO EMPEZAR OTRA VERSIÓN //
float read_analog_out(analog_out channel)
{
    float aux_float = 99.99;
    if( channel == analog_out::out0 )
        cout<<"leer salida an0"<<"\n";
    if( channel == analog_out::out1 )
        cout<<"leer salida an1"<<"\n";
    return aux_float;
}
// PARA EDITAR ESTO EMPEZAR OTRA VERSIÓN //




/*
namespace wte
{

static Serial _com;

static void parse_answer(char* ans,uint32_t len);

bool init_io(const char *serial_port, uint32_t baudrate)
{
    if( !_com.connect(serial_port,baudrate) )
        return false;
    _com.tx_write("\rreset\r");
    _com.tx_write("conf quiet\r");
    char ans[1024];
    do
        parse_answer(ans,1024);
    while( strcmp(ans," > reset") );
    return true;
}
bool read_digital_in(digital_in channel)
{
    switch( channel )
    {
    case digital_in::in0:
        _com.tx_write("read di0\r");
        break;
    case digital_in::in1:
        _com.tx_write("read di1\r");
        break;
    case digital_in::in2:
        _com.tx_write("read di2\r");
        break;
    case digital_in::in3:
        _com.tx_write("read di3\r");
        break;
    case digital_in::io_in0:
        _com.tx_write("read dio0\r");
        break;
    case digital_in::io_in1:
        _com.tx_write("read dio1\r");
        break;
    case digital_in::io_in2:
        _com.tx_write("read dio2\r");
        break;
    case digital_in::io_in3:
        _com.tx_write("read dio3\r");
        break;
    }
    char ans[1024];
    parse_answer(ans,1024);
    return atoi(ans) != 0;
}
void write_digital_out(digital_out channel,bool state)
{
    char data[128];
    switch( channel )
    {
    case digital_out::out0:
        sprintf(data,"write do0 %d\r",state?1:0);
        break;
    case digital_out::out1:
        sprintf(data,"write do1 %d\r",state?1:0);
        break;
    case digital_out::out2:
        sprintf(data,"write do2 %d\r",state?1:0);
        break;
    case digital_out::out3:
        sprintf(data,"write do3 %d\r",state?1:0);
        break;
    case digital_out::out4:
        sprintf(data,"write do4 %d\r",state?1:0);
        break;
    case digital_out::io_out0:
        sprintf(data,"write dio0 %d\r",state?1:0);
        break;
    case digital_out::io_out1:
        sprintf(data,"write dio1 %d\r",state?1:0);
        break;
    case digital_out::io_out2:
        sprintf(data,"write dio2 %d\r",state?1:0);
        break;
    case digital_out::io_out3:
        sprintf(data,"write dio3 %d\r",state?1:0);
        break;
    }
    _com.tx_write(data);
}
bool read_digital_out(digital_out channel)
{
    _com.tx_write("read all\r");
    char ans[1024];
    parse_answer(ans,1024);
    uint32_t last_arg_idx = 0;
    for( uint32_t i=0 ; i<strlen(ans) ; i++ )
        if( ans[i] == ' ' )
            last_arg_idx = i+1;
    static union
    {
        struct
        {
            uint8_t out0 : 1;
            uint8_t out1 : 1;
            uint8_t out2 : 1;
            uint8_t out3 : 1;
            uint8_t out4 : 1;
            uint8_t rsv  : 2;
            uint8_t msb  : 1;
        };
        uint8_t raw;
    }digital_out;
    static union
    {
        struct
        {
            uint8_t io_out0 : 1;
            uint8_t io_out1 : 1;
            uint8_t io_out2 : 1;
            uint8_t io_out3 : 1;
            uint8_t rsv : 3;
            uint8_t msb : 1;
        };
        uint8_t raw;
    }digital_io_out;
    last_arg_idx += 2;
    digital_out.raw    = ans[last_arg_idx++];
    digital_io_out.raw = ans[last_arg_idx++];
    switch( channel )
    {
    case digital_out::out0:
        return digital_out.out0;
    case digital_out::out1:
        return digital_out.out1;
    case digital_out::out2:
        return digital_out.out2;
    case digital_out::out3:
        return digital_out.out3;
    case digital_out::out4:
        return digital_out.out4;
    case digital_out::io_out0:
        return digital_io_out.io_out0;
    case digital_out::io_out1:
        return digital_io_out.io_out1;
    case digital_out::io_out2:
        return digital_io_out.io_out2;
    case digital_out::io_out3:
        return digital_io_out.io_out3;
    }
}
float read_analog_in(analog_in channel)
{
    if( channel == analog_in::in0 )
        _com.tx_write("read an0\r");
    else if( channel == analog_in::in1 )
        _com.tx_write("read an1\r");
    char data[1024];
    parse_answer(data,1024);
    return atof(data);
}
void write_analog_out(analog_out channel,float value)
{
    char data[1024];
    value = std::min(std::max(0.0f,value),100.0f);
    if( channel == analog_out::out0 )
        sprintf(data,"write an0 %.2f\r",value);
    else if( channel == analog_out::out1 )
        sprintf(data,"write an1 %.2f\r",value);
    _com.tx_write(data);
}
float read_analog_out(analog_out channel)
{
    _com.tx_write("read all\r");
    char ans[1024];
    parse_answer(ans,1024);
    float in0,in1,out0,out1,dig;
    sscanf(ans,"%f %f %f %f %d",&in0,&in1,&out0,&out1,&dig);
    if( channel == analog_out::out0 )
        return out0;
    return out1;
}

//static function implementation
static void parse_answer(char* ans,uint32_t len)
{
    uint32_t idx = 0;
    while( idx < len-1 )
    {
        if( _com.rx_available() != 0 )
            ans[idx++] = _com.rx_read();
        if( idx != 0 )
            if( ans[idx-1] == '\n' )
                break;
    }
    ans[idx-1] = '\0';
}

}	//namespace wte
*/

