# Documentación: software control (microcontrolador)

Este software realiza el control de las variable controlada (Torque) en función de la variable realimentada (Velocidad de giro), para lograr que en el eje del generador se aplique las condiciones necesarias para emular el comportamiento del rotor eólico, con la máxima exactitud y presición posibles.

Las variables con las que interactúa este sistema (de forma directa) son el Torque y la Velocidad de giro del motor.

Las características TWV de la turbina y las condiciones de la simulación a implementar se reciben desde la GUI que se ejecuta en la PC.

Las características TWV de la turbina se reciben "escaladas" para utilizarse en forma directa sobre el motor.

Aclaración: este soft debería incluir el funcionamiento básico del comportamiento dinámico (cálculo de aceleración y cálculo de torque de compensación) aunque inicialmente se mantenga deshabilitado y luego sea una configuración opcional

## Implementación APIs comunicación

Para la implementación inicial en la PC, se desarrollaron 2 API que solucionan la comunicación con el uC (funcionando como puente de comandos) y la comunicación con la GUI (simulando la comunicación serial).  
El objetivo es que al trasladar el software al microcontrolador, solo se deba modificar la implementación de las funciones de la API. Es decir, que no se requiera ninguna modificación fuera de las funciones que implementa la API.

### API soft control - variador (e/s digitales y analógicas)

Esta API debería permitir enviar comandos para leer las E/S analógicas y digitales y para establecer las salidas analógicas y digitales.  
Este proceso debe hacerse en forma directa, de manera que cada comando represente una orden directa al hardware (ejs: establecer nivel alto/bajo en una salida digital, leer nivel en una entrada analógica, etc.).
* Damián: esta parte ya está (las funciones que tenemos para usar en la PC tienen la misma forma que tienen en el microcontrolador)


**Configuración puerto**

@brief This function initialize the underlying serial port used to send commands to the control board.  
This must be called before read/write any digital/analog channel  
@param serial_port specify the serial port ej: "\\\\.\\COMx"  
@param baudrate specify the speed in bauds  
@returns true on ok, false on error  
bool  init_io(const char* serial_port,uint32_t baudrate);  


**E/S Digitales**

@brief Reads a digital input channel  
bool read_digital_in (digital_in  channel);  

@brief Writes a digital output channel  
void write_digital_out(digital_out channel,bool state);  

@brief Read a digital output channel  
bool read_digital_out(digital_out channel);  


**E/S Analógicas**

@brief reads the adc analog channel  
@param channel identify the adc channel to read  
@returns value between 0 to 100 in float format  
float read_analog_in (analog_in channel);


@brief writes the dac analog channel  
@param channel identify the dac channel to write  
@param value to write in the range [0:100]  
void  write_analog_out (analog_out channel,float value);


@brief reads the dac analog channel  
@param channel identify the dac channel to write  
@returns value between 0 to 100 in float format  
float read_analog_out (analog_out channel);




### API comunicación software-GUI(simulando serial bus)

// funciones que implementa
// argumentos y acciones que ejecuta

#### Comunicación uC-GUI

La comunicación se basa en una serie de comandos que indican las órdenes que se dan al microcontrolador, desde la GUI, y mensajes que envían información. Estos comandos y mensajes pueden ser un byte sencillo o una cadena de caracteres.  

**Datos turbina y simulación:**

Para el caso de las características de la turbina y los datos de la simulación que se deben enviar al microcontrolador, se utiliza un comando para indicar al microcontrolador que se van a enviar los datos, y se espera la respuesta del microcontrolador para comenzar a enviar la trama de datos. Al final de la trama se debe agregar algún tipo de redundancia que permita detectar errores en los datos, y reenviarlos en caso de que sea necesario. El microcontrolador indica si los datos se recibieron correctamente.  

Comandos:

DATOS_TURB			// secuencia de datos de turbina  
CARACT_SIM			// secuencia de características de la simulación  
MSJ_ESPERA_DATOS	// esperando datos  
MSJ_DATOS_OK		// comprobación de datos correcta  
MSJ_DATOS_ERROR		// comprobación de datos incorrecta

Adicionalmente el proceso de simulación puede empezar automáticamente luego de cargar los datos o utilizarse un comando adicional.

INIC_SIM		// iniciar simulación (opcional)

**Ejecución de la simulación**

Durante el proceso de simulación se envían las acciones a ejecutar por el microcontrolador: finalizar la simulación y finalizar la simulación de las condiciones actuales.

MSJ_FIN_CURVA		// indicación para finalizar simulación actual  
MSJ_FIN_SIM			// indicación para finalizar/detener simulación completa

El microcontrolador, por su parte, envía mensajes con información del proceso o indicando cuando ocurriera algún error.

MSJ_NO_EXISTE_CRUCE	// no se encontró cruce con curva
MSJ_TORQ_CONS_DIF	// error: diferencia excesiva entre torque leído y consigna
MSJ_OMEGA_SUP_MAX2	// error: segundo umbral máximo de omega superado

**Comprobación de conexión**

Cuando el microcontrolador no recibe un mensaje o comando desde la PC, durante más de cierto tiempo, se envía un comando a la PC, para que indique que permanece conectada. Si este intercambio no es exitoso se debería detener inmediatemente el funcionamiento del emulador.

MSJ_ESTAS_AHI		// consulta a PC, verificación presencia (estás ahí?"/"acá estoy")
MSJ_ACA_ESTOY		// respuesta PC, verificación presencia (estás ahí?"/"acá estoy")

**Otros comandos y mensajes que podrían implementarse:**

MSJ_FIN_SIM_PROC	// finSim procesado correctamente
MSJ_REG_PERM		// régimen permanente alcanzado
MSJ_REG_TRAN		// régimen permanente NO alcanzado (régimen transitorio)
MSJ_FIN_CURVA_PROC	// finCurva procesado correctamente
MSJ_ERROR			// error





## Estructura

La idea es que sea una especie de multitarea o scheduler -> es decir, una configuración inicial seguida de un bucle infinito en el que se llame a funciones que se encargan de ejecutar las tareas del programa.

Configuración inicial:
* configuración E/S digitales y analógicas
* configuración DAC
* * permitir seleccionar la cantidad de bits
* configuración ADC
* * permitir seleccionar la cantidad de bits
* configuración Timer
* * encapsulamiento para poder cambiar de la PC al uC

Las tareas principales serían:
* el algoritmo de control del Torque
* * determinar T y W
* * * leer entradas analógicas y convertirlas a velocidad de giro y torque (según las escalas correspondientes)
* * * * leer entradas analógicas crudas
* * establecer salida analógica (consigna)
* recibir comandos enviados desde la PC (si no se implementa con una interrupción)
* * recibir datos de la turbina y de la simulación -> acá o en otra tarea ???

NOTA: es necesario encapsular el funcionamiento del timer para poder pasar de la PC al uC sin problemas

### Diagrama de flujo

### Bloques que lo componen

### Prioridad en la implementación





