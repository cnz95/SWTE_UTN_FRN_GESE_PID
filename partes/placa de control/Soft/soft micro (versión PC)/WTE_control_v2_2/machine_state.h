#ifndef MACHINE_STATE_H
#define MACHINE_STATE_H

#endif // MACHINE_STATE_H



//// VARIABLE AUXILIAR
static uint8_t st_aux = 0;



// public functions prototypes

/* Function:
 * Parameters:
 * Returned values:
 */
void gui_communication_task();

/* Function:
 * Parameters:
 * Returned values:
 */
void auto_data_sending_task();

/* Function:
 * Parameters:
 * Returned values:
 */
void com_check_task();

/* Function:
 * Parameters:
 * Returned values:
 */
void t_control_task();



// //////////////////// PARA PRUEBAS //////////////////////
// para probar (asignar los valores de viento y tiempos de la simulación)
#include <vector>
#include <string>
using namespace std;
void set_wind_time_2(vector<string> wind_str_pp, vector<string>time_str_pp);
// //////////////////// PARA PRUEBAS //////////////////////
