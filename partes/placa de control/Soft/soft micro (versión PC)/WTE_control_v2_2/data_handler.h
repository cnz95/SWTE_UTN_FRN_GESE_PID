#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#endif // DATA_HANDLER_H

#include <stdint.h>
#include <vector>

using namespace std;

// public functions prototypes

void init_turb_data(uint8_t width, uint8_t height);

bool write_turb_data(vector<float> omega_new, vector<float> wind_new, vector<vector<float>> torque_new);

vector<vector<float>>* read_torque_matrix();

vector<float>* read_omega_vector();

vector<float>* read_wind_vector();

void init_sim_data(uint8_t dim);

bool write_sim_data(vector<float> wind_sim_new, vector<float> time_sim_new);

vector<float>* read_wind_sim();

vector<float>* read_time_sim();


