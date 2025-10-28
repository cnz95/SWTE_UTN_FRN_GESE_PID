Información del hardware para medición de V, I, P, Q y S, utilizado. Es el desarrollado por Damián para proyecto anterior.


### Características Principales

Borneras entrada:

* 3 borneras de 2 contactos

A0 A1 | B0 B1 | C0 C1

ahora esta midiendo Vlínea -> RS ST TR
//puede medir Vfase -> RN SN TN

Borneras salida:

* bornera única de 3 contactos

S0 S1 S2 -> a través de fusible y sensor de corriente



Medición de voltaje:

Mide los voltajes entre cada par de terminales de cada bornera de entrada -> depende de como lo conectes si tira V de línea o de fase

Ej: V1 = VA0 - VA1

Medición de corriente:

Se miden 3 corrientes, la que pasa desde A0 hasta S0, la que pasa desde A1 hasta S1, y la que pasa desde A2 hasta S2.



### Pruebas Verificación

Utilizando 3 cargas en triángulo de 20 Ohm c/u

Aplicando una consigna del 5% desde la PC:
- se aplica un voltaje analógico de 249 mV
- se aplica el torque 2.8 Nm (según indica el variador de velocidad)
- - el equivalente al 100% sería 56 Nm
- - el parámetro interno de la "consigna recibida" está en 2.78 Nm
- se aplica una potencia de 0.11 kW (según variador)
- se obtiene una velocidad de giro de 355 rpm (verificado medición interna y con encóder)

* el Tmáximo indicado por el variador es de 42.45
* la Pmáx indicada por el variador es de 6.38 kW

Aplicando una consigna del 10% desde la PC:
- se aplica un voltaje analógico de 497 mV
- se aplica el torque 5.5 Nm (según indica el variador de velocidad)
- - el equivalente al 100% sería 55 Nm
- - el parámetro interno de la "consigna recibida" está en 5.41 Nm
- se aplica una potencia de 0.46 kW (según variador)
- se obtiene una velocidad de giro de 810 rpm (verificado medición interna y con encóder)

* el Tmáximo indicado por el variador es de 42.45 Nm
* la Pmáx indicada por el variador es de 6.38 kW

Aplicando 8m/s
1100 rpm
7.45 Nm

Aplicando 7m/s
890 rpm
6 Nm


Notas: en el soft se utiliza:
* T_referencia = 51.2 Nm
* Omega = 500 rpm
* valor_final = valor_original * 100 / REF


Aplicando 9m/s (MODIF)
Omega = 3.96 V  -> 79% = 1137 rpm
T = 736 mV  -> 15% = 8.09 Nm

Torque(GEN) [Nm]
24,29

Omega(GEN) [rpm]
378,84

Aplicando 8m/s (MODIF)
Omega = 3.12 V  -> 62% = 895 rpm
T = 616 mV  -> 12% = 6.78 Nm

Torque(GEN) [Nm]
20,33

Omega(GEN) [rpm]
298,48

Aplicando 7m/s (MODIF, inestable)

Torque(GEN) [Nm]
13,9

Omega(GEN) [rpm]
202,8

Aplicando 10m/s (MODIF, prueba breve)
Omega = >4.72 V  -> 94% = 1355 rpm
T = >864 mV  -> 17.3% = 9.50 Nm

Torque(GEN) [Nm]
28,51

Omega(GEN) [rpm]
451,55

**Siguientes pruebas !**
- Cambiar la configuración del variador para que permita velocidades mayores a la nominal y eso se indique correctamente en el rango de 0 a 5 V. Con estos cambios, probar la regulación de velocidad a 10m/s


#### Código

versión:  v2_2