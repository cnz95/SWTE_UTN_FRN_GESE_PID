# Documentación: software GUI emulador (PC)

Este software ejecuta la GUI para que el operador del banco de pruebas pueda realizar la simulación del rotor y las condiciones que requiera.

Las funciones básicas que debe permitir configurar son:  
* características del rotor
* velocidad de viento
* duración de cada nivel de velocidad de viento

Las funciones avanzadas son:
* cambiar el paso de pala según algún comando externo
* cambiar el pitch??? según algun comando externo -> cuando el viento no le da de frente
* simular otras condiciones particulares (rotura, fallas, etc.)


## Interfaz con el uC

El software de la GUI debe resolver la comunicación con el uC que ejecuta el algoritmo de control. Se debe intercambiar la información y los comandos necesarios para que el uC puede ejecutar el proceso de simulación de forma prácticamente independiente. Es decir la GUI enviar toda la información necesaria y luego solo indica cuando iniciar y cuando finalizar la simulación.

### Comunicación uC-GUI

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

MSJ_INIC_SIM		// iniciar simulación (opcional)

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

MSJ_ESTAS_AHI		// consulta a PC, verificación presencia
MSJ_ACA_ESTOY		// respuesta PC, verificación presencia

**Otros comandos y mensajes que podrían implementarse:**

MSJ_FIN_SIM_PROC	// finSim procesado correctamente
MSJ_REG_PERM		// régimen permanente alcanzado
MSJ_REG_TRAN		// régimen permanente NO alcanzado (régimen transitorio)
MSJ_FIN_CURVA_PROC	// finCurva procesado correctamente
MSJ_ERROR			// error





## Estructura

GUI tareas
* Leer datos de turbina desde csv
* * Procesar los datos para obtener un formato enviable al uC
* Leer datos de un registro de vientos desde otro csv
* * Procesar los datos para obtener un formato enviable al uC
* Añadir una capa de abstracción sobre la comunicación serie con el uC
* Iniciar y mantener el control sobre el proceso de simulación

### Diagrama de flujo

### Bloques que lo componen

### Prioridad en la implementación





