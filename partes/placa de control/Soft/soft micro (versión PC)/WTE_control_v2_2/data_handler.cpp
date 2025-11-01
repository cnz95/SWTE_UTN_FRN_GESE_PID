

#include <vector>
#include <stdint.h>

using namespace std;

vector<float> *omega_addr;
vector<float> *wind_addr;
static vector<vector<float>> *torque_addr;

vector<float> *wind_sim_addr;
vector<float> *time_sim_addr;

void init_turb_data(uint8_t dim_omega, uint8_t dim_wind)
{
    static vector<float> vector_omega(dim_omega);
    static vector<float> vector_wind(dim_wind);
    static vector<vector<float>> matrix_torque(dim_omega,vector_wind);
    torque_addr = &matrix_torque;
    omega_addr = &vector_omega;
    wind_addr = &vector_wind;
}

bool write_turb_data(vector<float> omega_new, vector<float> wind_new, vector<vector<float>> torque_new)
{
    bool flag_ok = false;
    uint8_t dim_omega_new, dim_wind_new, dim_omega_new_vec, dim_wind_new_vec, dim_omega, dim_wind;
    dim_omega_new = torque_new.size();
    dim_wind_new = torque_new[0].size();
    dim_omega_new_vec = omega_new.size();
    dim_wind_new_vec = wind_new.size();
    dim_omega = (*torque_addr).size();
    dim_wind = (*torque_addr)[0].size();
    // verify data size
    if( (dim_omega==dim_omega_new) && (dim_wind_new==dim_wind) && (dim_omega_new_vec==dim_omega) && (dim_wind_new_vec==dim_wind) )
    {
        flag_ok = true;
        *torque_addr = torque_new;
        *omega_addr = omega_new;
        *wind_addr = wind_new;
    }
    return flag_ok;
}

vector<vector<float>>* read_torque_matrix()
{
    return torque_addr;
}

vector<float>* read_omega_vector()
{
    return omega_addr;
}

vector<float>* read_wind_vector()
{
    return wind_addr;
}


void init_sim_data(uint8_t dim)
{
    static vector<float> wind_sim(dim);
    static vector<float> time_sim(dim);
    wind_sim_addr = &wind_sim;
    time_sim_addr = &time_sim;
}

bool write_sim_data(vector<float> wind_sim_new, vector<float> time_sim_new)
{
    bool flag_ok = false;
    uint8_t dim_wind_sim, dim_time_sim, dim_wind_sim_new, dim_time_sim_new;
    dim_wind_sim_new = wind_sim_new.size();
    dim_time_sim_new = time_sim_new.size();
    dim_wind_sim = (*wind_sim_addr).size();
    dim_time_sim = (*time_sim_addr).size();
    // verify data size
    if( (dim_wind_sim==dim_wind_sim_new) && (dim_time_sim==dim_time_sim_new) )
    {
        flag_ok = true;
        *wind_sim_addr = wind_sim_new;
        *time_sim_addr = time_sim_new;
    }
    return flag_ok;
}

vector<float>* read_wind_sim()
{
    return wind_sim_addr;
}

vector<float>* read_time_sim()
{
    return time_sim_addr;
}


