#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#endif // COMMUNICATION_H



// public functions prototypes

/* Function: receives the turbine data, verifies it and sends the corresponding message
 * Parameters: -
 * Returned values: flag indicating if proccess was sucessfull
 */
bool rx_turb_data();

/* Function: receives the simulation data, verifies it and sends the corresponding message
 * Parameters: -
 * Returned values: flag indicating if proccess was sucessfull
 */
bool rx_sim_data();

// para probar (asignar los valores de viento y tiempos de la simulación)
#include <vector>
#include <string>
using namespace std;
void set_wind_time(vector<string> wind_str_p, vector<string> time_str_p);
