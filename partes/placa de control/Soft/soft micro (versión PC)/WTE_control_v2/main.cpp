
// libraries

#include "Timer.hpp"
#include "PC/TimerImp.hpp"


#include "machine_state.h"


#include<iostream>//ESTO DESPUÉS VUELA

using namespace std;//ESTO NO SE SI DSPS VUELA


int main()
{
    cout<<"start\n";
    // inicialization
    // configuración E/S digitales y analógicas
    // configuración DAC
    // // permitir seleccionar la cantidad de bits
    // configuración ADC
    // // permitir seleccionar la cantidad de bits
    // configuración Timer
    // // encapsulamiento para poder cambiar de la PC al uC


    /*// esto es lo que creo que tendría que agregar
     * // si uso el formato de comunicación de damián creo que tendría que hacer 2 estructuras de estas,
     * // una contendría lo comandos de comunicación (tal cual esta) y los de los cambios en la simulación
     * // cada uno tendría su propia función "init"
    //define supported commands on uart, and install processors for them
    constexpr wte::command_metadata_t commands[] =
        {
            {"read"	,wte::read },
            {"write",wte::write},
            {"reset",wte::reset},
            {"conf" ,wte::conf },
            {"help" ,wte::help }
        };
    wte::uart_rx_init( commands , sizeof(commands)/sizeof(wte::command_metadata_t) );
    */
    /* // comandos que yo voy a necesitar -> HAY QUE FILTRAR TODAVÍA
     * -> la idea hacer más directa la recepción de cada configuración/datos de la simulación
     *    -> Ej: recibir data turbina, una cadena con el comando configurar, la cosa que indica que son datos de turbina y todos los datos+xor
     * -> y procesar todo en simulation.cpp
**Datos turbina y simulación:**
DATOS_TURB			// secuencia de datos de turbina
CARACT_SIM			// secuencia de características de la simulación
MSJ_ESPERA_DATOS	// esperando datos -> se decidió omitirlo para simplificar el proceso
MSJ_DATOS_OK		// comprobación de datos correcta
MSJ_DATOS_ERROR		// comprobación de datos incorrecta
INIC_SIM            // iniciar simulación (opcional)

**Ejecución de la simulación**
MSJ_FIN_CURVA		// indicación para finalizar simulación actual
MSJ_FIN_SIM			// indicación para finalizar/detener simulación completa
MSJ_NO_EXISTE_CRUCE	// no se encontró cruce con curva
MSJ_TORQ_CONS_DIF	// error: diferencia excesiva entre torque leído y consigna
MSJ_OMEGA_SUP_MAX2	// error: segundo umbral máximo de omega superado

**Comprobación de conexión**
MSJ_ESTAS_AHI		// consulta a PC, verificación presencia (estás ahí?"/"acá estoy")
MSJ_ACA_ESTOY		// respuesta PC, verificación presencia (estás ahí?"/"acá estoy")

**Otros comandos y mensajes que podrían implementarse:**
MSJ_FIN_SIM_PROC	// finSim procesado correctamente
MSJ_REG_PERM		// régimen permanente alcanzado
MSJ_REG_TRAN		// régimen permanente NO alcanzado (régimen transitorio)
MSJ_FIN_CURVA_PROC	// finCurva procesado correctamente
MSJ_ERROR			// error

REVERSIÓN HASTA EL MOMENTO
un comando sería un "CONFIG" que puede ir seguido de
DATOS_TURB
CARACT_SIM -> CONDICIONES SIMULACIÓN
... podría agregarse otros (proceso más detallado)
y dsps todos los datos
dsps de procesar los datos el uC responde con un
MSJ_DATOS_OK
MSJ_DATOS_ERROR

otro comando "INIC_SIM" para indicar que se debe iniciar la simulación
no necesita ningún otro dato adicional
el uC puede responder si se pudo iniciar la simulación o no (puede faltar cargar datos)

* si la PC va a indicar que quiere que le envíen los datos en forma periódica eso debería ocurrir acá
* -> aunque el uC puede responder en todo momento a ese comando y la PC lo tendría que indicar en el momento correcto

**Ejecución de la simulación** -> no veo razón para que esto cambie
comandos a recibir durante la simulación
MSJ_FIN_CURVA		// indicación para finalizar simulación actual
MSJ_FIN_SIM			// indicación para finalizar/detener simulación completa
en tanto, el uC puede enviar durante la simulación
MSJ_NO_EXISTE_CRUCE	// no se encontró cruce con curva
MSJ_TORQ_CONS_DIF	// error: diferencia excesiva entre torque leído y consigna
MSJ_OMEGA_SUP_MAX2	// error: segundo umbral máximo de omega superado

faltaría revisar lo de:
**Comprobación de conexión**
**Otros comandos y mensajes que podrían implementarse:**
-> pero esta cuestión PUEDE ESPERAR
-> - podría ser una especie de "clear simulation"
    */


    // tasks

    static Tim32_ms t0;
    bool f_aux = true;

    while(true)
    {
        // torque control
        t_control_task();
        // GUI communication
        gui_communication_task();
        // automatic data sending
        auto_data_sending_task();
        // communication checking
        com_check_task();

        if(t0.elapsed() > 10s)
        {
            cout<<"Running loop (10s) \n";
            t0.restart();
        }
    }
    return 0;
}


