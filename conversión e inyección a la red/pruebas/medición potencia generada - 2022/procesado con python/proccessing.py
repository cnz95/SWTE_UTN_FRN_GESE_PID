# C:\Ing\WTE\detección de potencia generada\datos pruebas\proccessing with python

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

TITLE = 'Procesar datos'
VERSION = ''


global csv_file_downsampled

global list_res_I
global list_res_V
global list_res_W
global list_res_T
global list_v_viento

list_res_I = []
list_res_V = []
list_res_W = []
list_res_T = []
list_v_viento = []


def show_plot():
	
	global csv_file_downsampled
	
	# definir una figura
	fig = pyplot.figure()
	ax = fig.gca()
	ax.set_xticks(numpy.arange(-20,20,1))
	
	# graficar
	pyplot.grid(axis='both')
	pyplot.plot(csv_file_downsampled['TIME'],csv_file_downsampled['CH1'])
	pyplot.plot(csv_file_downsampled['TIME'],csv_file_downsampled['CH2'])
	pyplot.plot(csv_file_downsampled['TIME'],csv_file_downsampled['CH3'])
	pyplot.plot(csv_file_downsampled['TIME'],csv_file_downsampled['CH4'])
	pyplot.show()


def plot_new():
	
	# seleccionar archivo
	current_directory = os.path.abspath('') # forma corta jeje
	directory = filedialog.askopenfilename(initialdir=current_directory, title="Seleccionar archivo", filetypes=(('Archivos de valores separados por coma','*.csv'), ('Archivos de texto','*.txt')))
	
	# leer archivo
	csv_file = pandas.read_csv(directory, sep=CHAR_SEPARATOR, header=N_ROW_HEADER)
	
	print(csv_file)
	
	global csv_file_downsampled
	csv_file_downsampled = csv_file.iloc[::100, :]
	# csv_file_downsampled = csv_file
	
	print(csv_file_downsampled)
	
	# graficar con matplotlib
	
	print(csv_file_downsampled['TIME'])
	print(csv_file_downsampled['CH1'])
	
	
	show_plot()
	
	# # recortar y volver a graficar
	# df_2 = csv_file_downsampled.query('-15.5 < TIME < -11')
	# pyplot.plot(df_2['TIME'],df_2['CH1'])
	
	# pyplot.show()
	
	# # calcular promedio del tramo recortado
	# average = numpy.mean(df_2['CH1'])
	# print(average)
	
	# preguntar si graficar otro
	# flag_rta = messagebox.askyesno('Graficar otro ?','Graficar otro ?')


def bt_cmd_show():
	show_plot()


def bt_cmd_plot():
	plot_new()


def bt_cmd_show_segm():
	global csv_file_downsampled
	
	per_start = en_per1_start.get()
	per_end = en_per1_end.get()
	
	# recortar y volver a graficar
	cad = f'{per_start} < TIME < {per_end}'
	df_2 = csv_file_downsampled.query(cad)
	pyplot.plot(df_2['TIME'],df_2['CH1'])
	pyplot.plot(df_2['TIME'],df_2['CH2'])
	pyplot.plot(df_2['TIME'],df_2['CH3'])
	pyplot.plot(df_2['TIME'],df_2['CH4'])

	pyplot.show()


def bt_cmd_calc():
	
	global csv_file_downsampled
	
	v_viento = en_v_viento.get()
	per_start = en_per1_start.get()
	per_end = en_per1_end.get()
	
	# recortar
	cad = f'{per_start} < TIME < {per_end}'
	df_2 = csv_file_downsampled.query(cad)
	
	# calcular promedio del tramo recortado
	ave1 = numpy.mean(df_2['CH1'])
	ave2 = numpy.mean(df_2['CH2'])
	ave3 = numpy.mean(df_2['CH3'])
	ave4 = numpy.mean(df_2['CH4'])
	print(ave1)
	print(ave2)
	print(ave3)
	print(ave4)
	
	global list_res_I
	global list_res_V
	global list_res_W
	global list_res_T
	global list_v_viento
	# cálculo final y mostrar
	list_v_viento.append(v_viento)
	print(f'Velocidad de viento:   {v_viento}')
	
	# corriente
	res = ave1*0.1/0.02 # considerando 20mV/A y la compensación x10 del osc (estaba ajustado para puntas con atenuación)
	list_res_I.append(round(res,4))
	print(f'Corriente:   {round(res,2)} A')
	
	# tensión
	res = ave4 # N/C
	list_res_V.append(round(res,4))
	print(f'Tensión:   {round(res,2)} V')
	
	# omega
	res = ave2*(1500/5)*(1/3)
	list_res_W.append(round(res,4))
	print(f'Omega:   {round(res,2)} rpm')
	
	# torque
	res = ave3*(10.09/5)*(3)
	list_res_T.append(round(res,4))
	print(f'Torque:   {round(res,2)} Nm')
	
	print(list_res_I)


def bt_cmd_save():
	global list_res_I
	global list_res_V
	global list_res_W
	global list_res_T
	# df para guardar datos
	df_save = pandas.DataFrame({'Velocidad viento':list_v_viento,'Corriente [A]':list_res_I,'Tensión [V]':list_res_V,'Omega [rpm]':list_res_W,'Torque [Nm]':list_res_T})
	print(df_save)
	
	# seleccionar destino
	current_directory = os.path.abspath('') # forma corta jeje
	directory = filedialog.asksaveasfilename( initialdir=current_directory, initialfile='archivo.csv', title="Guardar archivo", filetypes=(('Archivos de valores separados por coma','*.csv'), ('Archivos de texto','*.txt')))
	
	if(directory[-4:] != '.csv'):
		directory = directory + '.csv'
	
	df_save.to_csv(directory, sep = ';',decimal=',', encoding='latin_1', index=False)
	



# crear ventana y configurarla
root = Tk()
root.title(f'{TITLE} {VERSION}')
root.iconbitmap('llama-blue-int1_C_fondo2.ico')

# # inicializar widgets

# button graficar
bt_plot = Button(root, text='Graficar otro', padx=15, pady=4, command = bt_cmd_plot)
# button mostrar gráfico
bt_show = Button(root, text='Mostrar Gráfico', padx=15, pady=4, command = bt_cmd_show)
# entries para periodo
en_per1_start = Entry(root, width=20, borderwidth=5)
en_per1_end = Entry(root, width=20, borderwidth=5)
# button para mostrar segmento
bt_show_segm = Button(root, text='Mostrar', padx=15, pady=4, command = bt_cmd_show_segm)
# entry para valor de velocidad de viento
en_v_viento = Entry(root, width=20, borderwidth=5)
# button para calcular y agregar
bt_calc = Button(root, text='Calcular y agregar', padx=15, pady=4, command = bt_cmd_calc)
# button para guardar datos
bt_save = Button(root, text='Guardar', padx=15, pady=4, command = bt_cmd_save)


# # posicionar widgets
bt_plot.grid(row=0, column=0, columnspan=2, padx=10, pady=20)
bt_show.grid(row=0, column=2, columnspan=1, padx=10, pady=20)

en_per1_start.grid(row=1, column=0, padx=10, pady=10, sticky='N')
en_per1_end.grid(row=1, column=1, padx=10, pady=10, sticky='N')
bt_show_segm.grid(row=1, column=2, padx=10, pady=10, sticky='N')

en_v_viento.grid(row=2, column=0, columnspan=1, padx=10, pady=10, sticky='N')
bt_calc.grid(row=2, column=1, columnspan=1, padx=10, pady=10, sticky='N')
bt_save.grid(row=2, column=2, columnspan=1, padx=10, pady=10, sticky='N')

root.after(100,plot_new)

root.mainloop()


