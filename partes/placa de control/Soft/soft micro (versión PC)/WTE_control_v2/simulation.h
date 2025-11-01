#ifndef SIMULATION_H
#define SIMULATION_H

#endif // SIMULATION_H

/*// esto es lo que creo que tendría que agregar
struct command_metadata_t
{
    char name[12];
    bool (*processor)(const char*,uint32_t);
};

void uart_rx_init(const command_metadata_t* info,uint32_t len);
*/

// public functions prototypes

/* Function: determines de new torque setpoint from current pair torque-omega
 * Parameters:
 * Returned values:
 */
float control_algorithm(float current_torque, float current_omega, float current_wind, float set_torque);

/* Function:
 * Parameters:
 * Returned values:
 */
float read_torque();

/* Function:
 * Parameters:
 * Returned values:
 */
float read_omega();

/* Function:
 * Parameters:
 * Returned values:
 */
void write_setpoint(float setpoint);

/* Function:
 * Parameters:
 * Returned values:
 */
void start_simulation();


