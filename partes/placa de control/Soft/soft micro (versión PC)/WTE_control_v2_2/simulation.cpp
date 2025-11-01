
#include "Timer.hpp"
#include "PC/TimerImp.hpp"

#include "control_io.h"
#include "data_handler.h"

#include <vector>

const analog_in AN_IN_TORQUE = analog_in::in1; // torque an1
const analog_in AN_IN_OMEGA = analog_in::in0; // omega an0
const analog_out AN_OUT_TORQUE = analog_out::out0; // setpoint torque an0
const digital_out D_O_ENABLE = digital_out::out0; // enable do0
const digital_out D_O_TURN_LEFT = digital_out::out1; // turn left
const digital_out D_O_TURN_RIGHT = digital_out::out2; // turn right


#include<iostream>//ESTO DESPUÉS VUELA

using namespace std;//ESTO NO SI SE SI DSPS VUELA


// public functions implementation
const float INC_TORQUE = 0.2;

float control_algorithm(float current_torque, float current_omega, float current_wind, float set_torque)
{
    //
    cout<<"Executed control algorithm \n";

//    vector<vector<float>> *m_torque = read_torque_matrix();
//    vector<float> *v_omega = read_omega_vector();
//    vector<float> *v_wind = read_wind_vector();

//    uint8_t dim_omega = (*v_omega).size();
//    uint8_t dim_wind = (*v_wind).size();

    vector<vector<float>> m_torque(*read_torque_matrix());
    vector<float> v_omega(*read_omega_vector());
    vector<float> v_wind(*read_wind_vector());

    uint8_t dim_omega = v_omega.size();
    uint8_t dim_wind = v_wind.size();

    uint8_t i_omega, i_wind;

    float x1, x2, y1, y2, m, k, torque_interp;

    while(i_wind < dim_wind)
    {
        if( (v_wind[i_wind] <= current_wind) && (current_wind <= v_wind[i_wind]) )
        {
            while(i_omega < dim_omega)
            {
                if( (v_omega[i_omega] <= current_omega) && (current_omega <= v_omega[i_omega+1]) )
                {
                    x1 = v_omega[i_omega];
                    x2 = v_omega[i_omega+1];
//                    y2 = m_torque[i_omega+1][v_wind[i_wind]];
//                    y1 = m_torque[i_omega][v_wind[i_wind]];
                    y2 = m_torque[i_omega+1][i_wind];
                    y1 = m_torque[i_omega][i_wind];
                    m = (y2-y1) / (x2-x1);
                    k = (-m*x1) + y1;
                    torque_interp = (m*current_omega) + k;
                    //torque_interp=y2+(((y2-y1)/(x2-x1))*(current_wind-x1));
                    if(current_torque - torque_interp < 0)
                    {
                        set_torque += INC_TORQUE;
                    }
                    else
                    {
                        set_torque -= INC_TORQUE;
                    }
                    i_omega = dim_omega;
                }
                i_omega++;
            }
            i_wind = dim_wind;
        }
        i_wind++;
    }

    return set_torque;
}

float read_torque()
{
    //
    float torque;
    torque = read_analog_in(AN_IN_TORQUE);
    return torque;
}

float read_omega()
{
    float omega;
    omega = read_analog_in(AN_IN_OMEGA);
    return omega;
}

void write_setpoint(float setpoint)
{
    write_analog_out(AN_OUT_TORQUE,setpoint);
}

void start_simulation()
{
    // initialize values and start motor
    write_setpoint(0);
    write_digital_out(D_O_ENABLE, true);
    write_digital_out(D_O_TURN_RIGHT, true);
    Tim32_ms tmr_enable_pulse;
    tmr_enable_pulse.restart();
    while(tmr_enable_pulse<10ms);
    write_digital_out(D_O_TURN_RIGHT, false);
}

//void stop_simulation(float setpoint, const auto time_step)
void stop_simulation(float setpoint)
{
    // initialize values and start motor
    //float ;
    const auto time_step = 400ms;
    Tim32_ms tmr_ramp_step;
    while(setpoint>0)
    {
        while(tmr_ramp_step<time_step);
        tmr_ramp_step.restart();

        setpoint -= INC_TORQUE;
        if(setpoint>0)
        {
            write_setpoint(setpoint);
        }
        else
        {
            write_setpoint(0);
            tmr_ramp_step.stop();
        }
    }
    //write_setpoint(0); // can be a descendent ramp -> DEBERÍA
    write_digital_out(D_O_ENABLE, false);
    write_digital_out(D_O_TURN_RIGHT, false);
}


//static vector<vector<float>> matrix_torque;


void init_handler()
{
    //
}



// private functions implementation




