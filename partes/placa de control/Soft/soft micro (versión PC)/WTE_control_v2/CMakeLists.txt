cmake_minimum_required(VERSION 3.5)

project(WTE_control_v2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(WTE_control_v2 main.cpp machine_state.cpp machine_state.h simulation.cpp simulation.h communication.cpp communication.h data_handler.cpp data_handler.h Timer.hpp PC/TimerImp.hpp control_io.cpp control_io.h)

install(TARGETS WTE_control_v2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
