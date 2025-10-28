#include <iostream>
#include "io/control_io.h"

int main()
{
    wte::init_io("\\\\.\\COM31",460800);
    std::cout << wte::read_digital_in(wte::digital_in::io_in0) << std::endl;
    wte::write_digital_out(wte::digital_out::io_out2,true);
    wte::write_digital_out(wte::digital_out::out0,true);
    wte::write_analog_out(wte::analog_out::out0,55.3f);
    wte::write_analog_out(wte::analog_out::out1,33.5f);
    std::cout << "----------------------" << std::endl;
    std::cout << "out0:    " << wte::read_digital_out(wte::digital_out::out0) << std::endl;
    std::cout << "out1:    " << wte::read_digital_out(wte::digital_out::out1) << std::endl;
    std::cout << "out2:    " << wte::read_digital_out(wte::digital_out::out2) << std::endl;
    std::cout << "out3:    " << wte::read_digital_out(wte::digital_out::out3) << std::endl;
    std::cout << "out4:    " << wte::read_digital_out(wte::digital_out::out4) << std::endl;
    std::cout << "io_out0: " << wte::read_digital_out(wte::digital_out::io_out0) << std::endl;
    std::cout << "io_out1: " << wte::read_digital_out(wte::digital_out::io_out1) << std::endl;
    std::cout << "io_out2: " << wte::read_digital_out(wte::digital_out::io_out2) << std::endl;
    std::cout << "io_out3: " << wte::read_digital_out(wte::digital_out::io_out3) << std::endl;

    std::cout << "----------------------" << std::endl;
    std::cout << "read in  an0:\t" << wte::read_analog_in(wte::analog_in::in0) << std::endl;
    std::cout << "read in  an1:\t" << wte::read_analog_in(wte::analog_in::in1) << std::endl;
    std::cout << "read out an0:\t" << wte::read_analog_out(wte::analog_out::out0) << std::endl;
    std::cout << "read out an1:\t" << wte::read_analog_out(wte::analog_out::out1) << std::endl;

    return 0;
}
