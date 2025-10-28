# Documentación de la etapa de Conversión e Inyección a la Red

En este archivo se recopila la documentación de la etapa de Conversión e Inyección a la Red. Las distintas pruebas e información requeridas se presentan en orden de inicio de ejecución/compilación.

* Este archivo se inició cuando este bloque del sistema ya se encontraban en proceso de construcción y pruebas, por lo que no se encuentra completa la documentación previa.

El nombre del archivo se puede ir modificando para reflejar su última actualización. (A DEFINIR)

## Prueba SWTE: I-V vs T-W (2025-04 - 2025-04)

### Objetivos

Medición de I y V y contrastación con T y W, a fin de determinar la correlación entre la curva de máxima potencia y la salida del generador (que a su vez es la entrada del convertidor para eólica recientemente adquirido). Esta información es requerida por el convertidor para configurar su funcionamiento y, logicamente, obtener la máxima potencia del generador eólico.

### Requisitos

Mapeo suficientemente fino en las cercanías de la curva de máxima potencia. Idealmente en todo el rango de operación del emulador, para evitar repetir mediciones en caso de cambiar las condiciones de operación.

### Configuración

* carga resistiva, conectada en triángulo, distintos valores
	- se medirá la resistencia construida antes de realizar la prueba
* I y V trifásica medida con la placa de Damián (VER FUNCIONAMIENTO PLACA !!!)
	- se realizarán al menos 3 mediciones de las tensiones y corrientes a fin de promediarlas y reducir el efecto del ruido
	- Para el mapeo I-V vs T-W se utilizará un promedio de los valores por fase obtenidos
* control configurado para seguir las características de la turbina / establecer un torque fijo a elección

**Opción 2 (debido a falla de placa Damián):**
* V de línea medido con multímetro AMPROBE 37XR-A, entre 2 líneas (Error: 1.2%+10)
* I de línea medida con punta de corriente PA-655 y multímetro FLUKE 111, en 1 sola línea (Error: 3%+30mA y 1%+3) (se podría utilizar el osciloscopio para medir el voltaje y a la vez visualizar la forma de onda, aunque no es necesario esto último)
   - las mediciones se consideran representativas de todo el sistema dada la naturaleza balanceada del mismo
   - lo conveniente de esta asignación es que el amprobe introduce mayor error al medir corriente (2.5%+10), la opción del osc también introduce un mínimo de 3.25% de error sobre el voltaje medido

**Opción 3 (debido a falla de placa Damián y error punta de corriente):**
* V de línea medido con multímetro AMPROBE 37XR-A (1.5%+3), entre 2 líneas
* I de línea medida con multímetro FLUKE 111 (Error: 1%+3), en 1 sola línea
   - las mediciones se consideran representativas de todo el sistema dada la naturaleza balanceada del mismo
   - lo conveniente de esta asignación es que se evita el error de la punta de corriente, pero es necesario abrir el circuito


### Detalles

Se optó por establecer valores de torque a elección para realizar un barrido más fino. Empezando por las áreas de interés.

Dado que la relación entre la velocidad de giro (W) y el torque (T) obtenidos dependerá de la carga, conmutando la carga resistiva entre distintos valores y repitiendo el barrido de valores de torque se puede obtener un mapeo más completo. (Sujeto a los cambios que pueda pedir Bufanio)

* Se generó código en python para convertir lo datos crudos a un formato utilizable



## Pruebas Convertidor Eólico: Vdc vs V-I (2025-05 - 2025-05)

### Objetivos

Relevar el comportamiento del convertidor eólico adquirido, utilizando la configuración genérica (que no considera la maximización de la potencia generada) y la configuración optimizada (mppt, aproximado "por puntos").

El relevamiento permitirá verificar con certeza el comportamiento del emulador bajo distintas configuraciones.

* Esta prueba no se implementó por los tiempos al no ser esencial para completar el trabajo solicitado.

### Requisitos

Se debería relevar las diferentes condiciones/configuraciones bajo las que funciona el dispositivo.

Barrido suficientemente fino, idealmente igual al realizado en la "Prueba: I-V vs T-W", puede ser menos detallado, solo lo suficiente para verificar el comportamiento del convertidor.

### Configuración

* La mediciones del voltaje y corriente se puede realizar mediante los métodos utilizados anteriormente, o se puede omitir, dado que debería mantenerse la relación del T-W (observado en la PC) con el I-V -> SIN EMBARGO CAMBIA LA CARGA, hay que ver cuanto afecta
* V y I monofásica (salida) medida con punta de corriente y voltímetro
  - ALTERNATIVA pinza de corriente -> evaluar, tiene una resolucion grande
* P y Vdc detectados e indicados por el convertidor

//// pinza disponible: fluke 336 ////

se puede hacer un barrido con pasos más grandes que las pruebas I-V vs T-W, dado que el objetivo es verificar el comportamiento del convertidor

### Detalles

* Esta prueba no se implementó por los tiempos al no ser esencial para completar el trabajo solicitado.




## Pruebas SWTE + Convertidor Eólico: 

### Objetivos

Relevar las características de la energía inyectada a la red con el conjunto Emulador+Convertidor, a fin de evaluar dichas características respecto a lo típico en un generador eólico real y contrastar la consistencia de los resultados respecto a las pruebas anteriores (la consistencia de la emulación de la turbina).

### Requisitos

Relevar los valores de velocidad de viento que se hayan utilizado en los trabajos anteriores.

### Configuración

* Conexión del Convertidor (conectado a la red) como carga del generador del SWTE
* Se tomarán los valores de V y P de salida desde el display del convertidor y, a fin de verificación, mediante el analizador de calidad de energía.
	- opcionalmente, también se medirá I y V trifásica con multímetros
	- se realizarán al menos 3 mediciones de todas las cantidades a fin de promediarlas y reducir el efecto del ruido
	- Luego de las primeras mediciones se utilizó solo los datos del convertidor dado que estos representaban de forma aceptablemente exacta los parámetros de salida y ofrecían una mejor resolución
* control configurado para seguir las características de la turbina


### Detalles

* Esta prueba se repitió a fin de evaluar distintos casos:
	- datos I-V obtenidos de gráfica interpolada en excel
	- datos I-V calculados por profe Bufanio
	- datos I-V de la última prueba + Dumpload de 85 V
	- datos I-V de la última prueba + Dumpload de 90 V (esta última resultó en la desconexión por sobretensión en las velocidades de viento mayores)
* Las últimas mediciones se realizaron con un Dumload menor para evitar la desconexión automática


