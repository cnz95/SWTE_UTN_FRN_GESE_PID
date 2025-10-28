

from tkinter import filedialog
import os.path
import pandas
from matplotlib import pyplot
from tkinter import messagebox
from tkinter import *

import numpy


# constantes
CHAR_SEPARATOR = ','
N_ROW_HEADER = 14

TITLE = 'Plot CSV'
VERSION = ''

# Abrir archivo
print('Abriendo archivo...')

# seleccionar archivo
current_directory = os.path.abspath('') # forma corta jeje
directory = filedialog.askopenfilename(initialdir=current_directory, title="Seleccionar archivo", filetypes=(('Archivos de valores separados por coma','*.csv'), ('Archivos de texto','*.txt')))

print('Indique la cantidad de filas de cabecera para leer los datos')
print('Para csv tektronix 14 por defecto')
N_ROW_HEADER = int(input())


# leer archivo
csv_file = pandas.read_csv(directory, sep=CHAR_SEPARATOR, header=N_ROW_HEADER)

# mostrar datos leídos
print(f'Archivo abierto: {directory}')
print('Contenido:')
print(csv_file)

# seleccionar datos de cada eje
print(f'Las columnas existentes son:\n{list(csv_file)}')
print('Ingrese la columna a utilizar como abcisa')
x_name = input()
print('Ingrese la columna a utilizar como ordenada')
y_name = input()

if(x_name == 'nan'):
	x_vector = [x for x in range(csv_file.shape[0])]
	# new_column = {'column_aux':x_vector}
	csv_file['column_aux'] = x_vector
	x_name = 'column_aux'
	
	print('Contenido actualizado:')
	print(csv_file)

print(f'Cantidad de filas: {csv_file.shape[0]}')
# x_vector = [x for x in range(csv_file.shape[0])]
# new_column = {'column_aux':x_vector}
# print(new_column)

csv_file_downsampled = csv_file.iloc[::10, :]
# csv_file_downsampled = csv_file

print(csv_file_downsampled)

# graficar con matplotlib

print(csv_file_downsampled[x_name])
print(csv_file_downsampled[y_name])

# # definir una figura
fig = pyplot.figure()
ax = fig.gca()
ax.set_xticks(numpy.arange(-0.1,0.1,0.01))

# graficar
pyplot.grid(axis='both')
pyplot.plot(csv_file_downsampled[x_name],csv_file_downsampled[y_name])
pyplot.show()



flag_r = True

while(flag_r):
	print('Ingrese x inicial:')
	x1 = input()
	print('Ingrese x final:')
	x2 = input()
	print('Ingrese paso:')
	x3 = input()

	print(f'{x1};{x2};{x3}')



	#### permitir elegir un segmento de los datos y graficarlos
	csv_file_segm = csv_file[ (csv_file[x_name] >= float(x1)) & (csv_file[x_name] <= float(x2)) ]
	print( csv_file_segm )


	# definir una figura
	fig = pyplot.figure()
	ax = fig.gca()
	ax.set_xticks(numpy.arange(float(x1),float(x2),float(x3)))

	# graficar
	pyplot.grid(axis='both')
	# pyplot.plot(csv_file_segm['TIME'],csv_file_segm['CH1'])
	# pyplot.plot(csv_file_segm['TIME'],csv_file_segm['CH2'])
	pyplot.plot(csv_file_segm[x_name],csv_file_segm[y_name])
	# pyplot.plot(csv_file_segm['TIME'],csv_file_segm['CH4'])
	pyplot.show()
	
	print('Visualizar otro segmento ? (y/n)')
	res = input()
	if(res != 'y'):
		flag_r = False


