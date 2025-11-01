
#include <cstdint>


#include "Timer.hpp"
#include "PC/TimerImp.hpp"


#include "machine_state.h"
#include "simulation.h"
#include "communication.h"


#include<iostream>//ESTO DESPUÉS VUELA

using namespace std;//ESTO NO SI SE SI DSPS VUELA



enum class state_sim_t
{
    waiting_config,
    config_turb,
    config_sim,
    config_completed,
    simulating
};

static state_sim_t _state_sim = state_sim_t::waiting_config;

// según entiendo, sería hacer las siguientes funciones:
// - check_state()
// - set state
// y la variable no es necesario tocarla directamente
// también se puede hacer esa magia que hizo damián de definir el tipo de valores que se le puede pasar a la función sin recibir error
// -> aunque no sería necesario en esta primero etapa



// una forma que se me ocurre es dejar los estados del coso en general acá -> suena conveniente dejarlo en donde definamos algo en base a ese estado
// en torque_control definimos si la configuración ya fué cargada (si es posible iniciar la simulación)

// state of serial communication
static enum class state_com_t
{
    shutdown,
    init,
    read_frame,
    process_frame,
    find_command,
    invoke_processor,
    ignore_and_wait_eof
}_state_com = state_com_t::shutdown;

// data sending mode to PC(GUI)
static enum class data_send_mode_t : uint8_t
{
    on_request,
    auto_send
}_data_send_mode = data_send_mode_t::on_request;



// INTENTO DE USAR CONSTANTES PARA LOS PERIODOS DE LOS TIMERS
const auto PER_AUTO_SENDING = 500ms;
const auto PER_CHECKING = 2s;
const auto PER_T_UPDATING = 1s;



// private functions prototypes

/* Function: returns the current state of the state machine
 * Parameters: -
 * Returned values: current state
 */
state_sim_t get_state();

/* Function: sets the state to a given value, previous checking that the change is valid
 * Parameters: new_state: the new state
 * Returned values: flag that indicates if the state could be assigned
 */
bool set_state(state_sim_t new_state);

/* Function: initializes the matrix to store the torque characteristics
 * Parameters: width and height of matrix
 * Returned values: -
 */
void init_matrix(uint8_t width, uint8_t height);

/* Function: initializes the simulation variables
 * Parameters: -
 * Returned values: -
 */
void init_sim();




// public functions implementations

void gui_communication_task()
{
    // recibir comandos enviados desde la PC (si no se implementa con una interrupción)
    // // recibir datos de la turbina y de la simulación -> acá o en otra tarea ???

    /* cuando se recibe el comando de cargar datos:
     * - se recibe una trama con: dimensiones de las características, vector con valores de viento, vector con valores de omega, matriz de valores de torque, lista de valores a viento a simular, duración de c/valor de viento, y creo que nada más...
     * - se inicializan la matriz y todos los vectores
     * - se asigna los valores correspondientes
     * - se cambia el estado a "configured"
     * cuando se recibe el comando de iniciar simulación:
     * - se inicializan las variables que identifican la velocidad de viento y el tiempo que esta debe durar
     * - se inicializan los timers necesarios
     * - se cambia el estado a "simulating"
     * - cuando se cumpla el tiempo se actualizan las variables
     * - cuando se terminen los valores solicitados se detienen los timer
     * - se cambia el estado a "configured"
     * - - si en la mitad de la simulación se envía el comando detener simulación se saltea a las últimas 2 acciones
    */

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // PODRÍA HACER LOS PASOS QUE DEBERÍA HACER LA FUNCIÓN QUE RESPONDE AL COMANDO DE CARGAR DATOS
    // e ir implementando las funciones que sean necesarias para inicializar las variables y guardar los datos recibidos
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    // se recibe el comando DATOS_TURB (secuencia de datos de turbina)
    // se debería llamar a una función que recibe los datos y los manda a las variables correspondientes
    // - rx_turb_data
    // se recibe el comando CARACT_SIM (secuencia de características de la simulación)
    // se debería llamar a una función que recibe los datos y los manda a las variables correspondientes
    // - rx_sim_data
    // cada fc debería verificar que los datos sean correctos y ... [enviar la rta] o [retornar un flag]
    // (en principio vamos a suponer que no va a haber problema en que se envíe la rta en la misma función)
    // de todas maneras se debería devolver el flag para que acá se cambie de estado cuando corresponda
    // MSJ_DATOS_OK		// comprobación de datos correcta
    // MSJ_DATOS_ERROR		// comprobación de datos incorrecta
    // -> POR PRECAUCIÓN, al menos al principio, ESTOS COMANDOS DEBERÍAN TENER EFECTO SOLO CUANDO NO SE ESTÁ EJECUTANDO LA SIMULACIÓN
    //// HACER //// HACER //// HACER //// HACER //// HACER //// HACER //// HACER //// HACER //// HACER //// HACER //// HACER //// ^ ^
    //// HACER //// HACER //// HACER //// HACER //// HACER //// HACER //// HACER //// HACER //// HACER //// HACER //// HACER //// | |
    //// HACER //// HACER //// HACER //// HACER //// HACER //// HACER //// HACER //// HACER //// HACER //// HACER //// HACER //// | |


    // se recibe el comando INIC_SIM (iniciar simulación)
    // si falta algo:
    // - se envía los mensajes de lo que falta
    // FALTAN DATOS DE TURBINA o FALTAN DATOS DE SIMULACIÓN
    // -> de esta manera ESTE COMANDO TIENE EFECTO SOLO CUANDO SE ESPERA INICIAR LA SIMULACIÓN
    // - se queda en el mismo estado que estaba
    // si todo ok:
    // - se inicializan las variables necesarias
    // - se envía la confirmación de que se inició el proceso

    // los siguientes comandos solo tienen efecto DURANTE la simulación
    // FIN_CURVA (indicación para finalizar simulación de las condiciones actuales (viento))
    // FIN_SIM (indicación para finalizar/detener simulación completa)

    // mensajes que se intercambian DURANTE la simulación (todos enviados desde el uC o solo son respuestas de la PC)
    // MSJ_NO_EXISTE_CRUCE	// no se encontró cruce con curva
    // MSJ_TORQ_CONS_DIF	// error: diferencia excesiva entre torque leído y consigna
    // MSJ_OMEGA_SUP_MAX2	// error: segundo umbral máximo de omega superado
    // MSJ_ESTAS_AHI		// consulta a PC, verificación presencia (estás ahí?"/"acá estoy")
    // MSJ_ACA_ESTOY		// respuesta PC, verificación presencia (estás ahí?"/"acá estoy")


    static Tim32_ms tmr_aux;

    if(tmr_aux > 3s && st_aux==0)
    {
        // PRUEBA //
        // PRUEBA //
//        vector<vector<float>> m_aux = { {1.1, 1.2}, {2.1, 2.2}, {3.1, 3.2}};
//        vector<float> v_aux(2); // valores de viento
//        vector<vector<float>> m_aux(3,v_aux); //vector y valores de omega
//        cout<<"se inició la simulación !!! \n";
//        cout<<"PRUEBA: \n";
//        cout<<"matriz size(): "<<m_aux.size()<<" \n"; // 3 -> cant de valores de omega -> filas ?
//        cout<<"matriz [0].size(): "<<m_aux[0].size()<<" \n"; // 2 -> cant de valores de viento -> columnas ?
//        cout<<"PRUEBA: \n";


        cout<<"se inició la simulación !!! \n";
        bool flag_ok;
        flag_ok = rx_sim_data();
        set_state(state_sim_t::config_sim);
        flag_ok = rx_turb_data();
        set_state(state_sim_t::config_turb);

        set_state(state_sim_t::simulating);
        tmr_aux.restart();
        st_aux = 1;
    }
    if(tmr_aux > 25s && st_aux==1)
    {
        cout<<"se detuvo la simulación \n";
        set_state(state_sim_t::config_completed);
        set_state(state_sim_t::waiting_config);
        tmr_aux.restart();
        st_aux = 0;
    }
}

void auto_data_sending_task()
{
    // read speed and torque at motor, and voltaje and current at load
    // send data periodically
    if( (get_state()==state_sim_t::simulating) && (_data_send_mode==data_send_mode_t::auto_send) )
    {
        static Tim32_ms tmr_auto_send;
        if(tmr_auto_send > PER_AUTO_SENDING)
        {
            cout<<"sending data, every 500ms \n";
            tmr_auto_send.restart();
        }
    }
}

void com_check_task()
{
    // check communication with PC(GUI), when simulating and after Tch ms from last received message
    static Tim32_ms tmr_com_check;

    if(get_state()==state_sim_t::simulating)
    {
        if(tmr_com_check > PER_CHECKING)
        {
            cout<<"checking communication, every 2s \n";
            tmr_com_check.restart();
        }
    }
}


// VERIFICAR DONDE IRÍA !!!
#include <vector>
#include "data_handler.h"

static float setpoint;
static uint8_t i_wind_current;
static Tim32_ms tmr_wind_condition;

void t_control_task()
{
    // // determinar T y W
    // // // leer entradas analógicas y convertirlas a velocidad de giro y torque (según las escalas correspondientes)
    // // // // leer entradas analógicas crudas
    // // ejecutar algoritmo de control (el que sea)
    // // establecer salida analógica (consigna)

    if(get_state() == state_sim_t::simulating)
    {
        static Tim32_ms tmr_torque_update;
        //t0.start();
        if(tmr_torque_update.elapsed() > PER_T_UPDATING)
        {
            cout<<"Update Torque, every 1s \n"; // SOLO PARA REFERENCIA


            tmr_torque_update.restart();

            float torque, omega;
            // read current torque and omega
            torque = read_torque();
            omega = read_omega();

            // ACÁ FALTARÍA HACER LA ACTUALIZACIÓN DEL i_wind_current CONTROLANDO EL TIEMPO
            // - tengo la función init_sim(), esa podría servir para algo

            vector<float> *wind_sim = read_wind_sim();
            vector<float> *time_sim = read_time_sim();
            uint8_t dim_time = (*time_sim).size();
            //float float_prueba = (*time_sim)[i_wind_current] *1000.01;
            uint16_t time_sim_int = (uint16_t) ((*time_sim)[i_wind_current]) *1000 ;

            if(tmr_wind_condition > time_sim_int)
            {
                tmr_wind_condition.restart();
                i_wind_current++;
                cout<<"#### #### #### #### #### WIND CONDITION CHANGED #### ####";
                if( i_wind_current >= dim_time )
                {
                    set_state(state_sim_t::config_completed);
                    tmr_wind_condition.stop(); // solo por precaución, no debería ser necesario
                    i_wind_current = 0; // solo por precaución, no debería ser necesario
                    setpoint = 0; // solo por precaución, no debería ser necesario

                    cout<<"#### #### #### #### #### END WIND CONDITIONS #### ####";
                }
            }


            // GENERAR VALORES DE TORQUE Y OMEGA PARA PROBAR EL ALGORITMO
            torque = setpoint;
            omega = torque*(255/7) + 0.02; // ( 7 Nm ; 255 rpm )

            // determine torque setpoint and identify posible errors
            setpoint = control_algorithm(torque, omega, (*wind_sim)[i_wind_current], setpoint);


            write_setpoint(setpoint);
        }
    }
}



// private functions implementations

state_sim_t get_state()
{
    return _state_sim;
}

bool set_state(state_sim_t new_state)
{
    bool flag_ok = false;
    if(_state_sim == state_sim_t::waiting_config) // si se esperan los datos de configuración
    {
        if(new_state == state_sim_t::config_sim)
        {
            _state_sim = state_sim_t::config_sim;
            flag_ok = true;
        }
        if(new_state == state_sim_t::config_turb)
        {
            _state_sim = state_sim_t::config_turb;
            flag_ok = true;
        }
    }
    if(_state_sim == state_sim_t::config_sim) // si la simulación ya fué configurada
    {
        if(new_state == state_sim_t::config_turb)
        {
            _state_sim = state_sim_t::config_completed;
            flag_ok = true;
        }
        if(new_state == state_sim_t::waiting_config) // reset config
        {
            _state_sim = state_sim_t::waiting_config;
            flag_ok = true;
        }
    }
    if(_state_sim == state_sim_t::config_turb) // si los datos de turbina ya fueron configurados
    {
        if( new_state == state_sim_t::config_sim )
        {
            _state_sim = state_sim_t::config_completed;
            flag_ok = true;
        }
        if(new_state == state_sim_t::waiting_config) // reset config
        {
            _state_sim = state_sim_t::waiting_config;
            flag_ok = true;
        }
    }
    if(_state_sim == state_sim_t::config_completed) // si todos los parámetros ya fueron configurados
    {
        if(new_state == state_sim_t::simulating)
        {
            _state_sim = state_sim_t::simulating;
            init_sim();
            flag_ok = true;
        }
        if(new_state == state_sim_t::waiting_config) // reset config
        {
            _state_sim = state_sim_t::waiting_config;
            flag_ok = true;
        }
    }
    if(_state_sim == state_sim_t::simulating) // si la simulación está en marcha
    {
        if(new_state == state_sim_t::config_completed) // finalizar simulación
        {
            _state_sim = state_sim_t::config_completed;
            flag_ok = true;
        }
    }

    return flag_ok;
}

void init_sim()
{
    // initialize simulation
    setpoint = 0;
    i_wind_current = 0;
    tmr_wind_condition.restart();

    cout<<"#### #### #### #### #### SIMULATION INITIALIZED #### ####";
}




