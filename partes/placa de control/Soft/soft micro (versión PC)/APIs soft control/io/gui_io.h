#pragma once
#include <cstdint>

namespace wte
{

struct wind_turbine_parameters_t
{
    static constexpr uint32_t torque_len        = 50;
    static constexpr uint32_t w_len             = 50;
    static constexpr uint32_t wind_speed_len    = 50;
    float torque    [torque_len];
    float w         [w_len];
    float wind_speed[wind_speed_len];
};

}//namespace wte
