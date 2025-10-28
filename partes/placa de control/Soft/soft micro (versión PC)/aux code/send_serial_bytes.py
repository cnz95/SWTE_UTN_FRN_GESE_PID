

# funciones

#### init_UART ####

# Función: inicializa el puerto serie a utilizar para la comunicación

# Parámetros
# port_name: nombre del puerto en forma de cadena de caracteres

# Valores de retorno
# USB_port: instancia del puerto serie

import serial

def init_UART(port_name):
	# iniciar instancia de puerto USB
	USB_port = serial.Serial(port_name)
	# configurar
	# USB_port.baudrate = 9600
	USB_port.timeout = 1 #### #### #### #### segundos ??? #### #### #### ####
	return USB_port


#### close_UART ####

# Función: cierra el puerto serie

# Parámetros
# USB_port: instancia del puerto serie

# Valores de retorno
# :

def close_UART(USB_port):
	# cerrar puerto
	USB_port.close()


#### Tx_UART ####

# Función: Envía datos mediante el puerto serie que se le indique

# Parámetros:
# msg: vector de valores enteros sin signo de 8 bits, que se enviarán, en el orden dado,
#      por medio del puerto serie
# USB_port: instancia del puerto serie mediante el cual se van a enviar los datos

def Tx_UART(msg, USB_port):
	# si msg es de tipo byte
	if( type(msg)==bytes):
		# print(msg)
		USB_port.write(msg)
	# si msg es de tipo entero
	if( type(msg)==int ):
		# print(str(msg))
		USB_port.write(msg.to_bytes(1,'big'))
	# si msg es de tipo list
	if( type(msg)==list ):
		# for element in bytearray(msg):
		for element in msg:
			# print(str(element))
			USB_port.write(element.to_bytes(1,'big'))



from numpy import random

# pedir puerto a uilizar
print('Ingrese el nombre del puerto a utilizar')
USB_port_name = input()

# iniciar puerto usb
USB_port = init_UART(USB_port_name)

flag_repeat = True
# bucle
while(flag_repeat == True):
	# solicitar cantidad de bytes
	print('Ingrese la cantidad de bytes a enviar')
	cant = int(input())
	
	print('Los bytes serán aleatorios ? (y/n)')
	flag_random = lower(input())
	
	if(flag_random=='y'):
		# generar lista aleatoria y enviar
		# list_bytes = [random.sample(range(256), cant) for i in range(cant)]
		list_nums = random.randint(256, size=(cant))
		list_bytes = [int(x) for x in list_nums]
		print(list_bytes)
		Tx_UART(list_bytes, USB_port)
	else:
		# ingresar valores 0111 1011 = (64+32+16=112) + (8+2+1=11) = d123 = h7B
		print('Ingrese los valores en formato decimal (d123) o hexadecimal (h7B), uno a la vez')
		list_bytes = [int(input()) for i in range(cant)]
		print(list_bytes)
		Tx_UART(list_bytes, USB_port)
	# preguntar si repetir
	print('Generar otra trama ? (s/n)')
	res = input()
	
	if(res=='s' or res=='S'):
		flag_repeat = True
	else:
		flag_repeat = False

# cerrar puerto USB
close_UART(USB_port)

