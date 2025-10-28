# funciones para procesamiento de los datos crudos de T-W y V-I

import pandas as pd
import numpy as np

SEPARATOR = '\t'

# nombres de archivos
file_name = [['T-W_60_Tri.csv', 'V-I-S-P-Q_60_Tri.csv'],
			['T-W_40_Tri.csv', 'V-I-S-P-Q_40_Tri.csv'],
			['T-W_20_Tri.csv', 'V-I-S-P-Q_20_Tri.csv'],
			['T-W_10_Tri.csv', 'V-I-S-P-Q_10_Tri.csv'],
			['T-W_6R6_Tri.csv', 'V-I-S-P-Q_6R6_Tri.csv']]

f_n_columns = ['TW', 'IV']
f_n_rows = ['60', '40', '20', '10', '6R6']

df_file_name = pd.DataFrame(file_name, columns=f_n_columns, index=f_n_rows)

# print(df_file_name)

# función para limpiar los archivos de datos crudos
# param: 'TW' o 'VI'
# res: '60', '40', '20', '10', '6R6'
def clean_file(param, res, modif='crudos'):

	# leer archivo
	if(modif != ''):
		file_name = df_file_name[param][res][:-4]+'_'+modif+'.csv'
	else:
		file_name = df_file_name[param][res]
		
	# print(pd.read_csv(df_file_name[param][res], sep=SEPARATOR, header=None))

	df_file = pd.read_csv(file_name, sep=SEPARATOR, header=None)
	
	if(param=='TW'):
		list_data = df_file.values

		# print(df_file.values)

		# convertir a formato 3 columnas
		n_rows = int(np.ceil(len(list_data) / 3))

		matrix_data = list_data[:n_rows*3].reshape(n_rows, 3)

		# print(pd.DataFrame(matrix_data))

		df_file = pd.DataFrame(matrix_data)
		
		# eliminar columna redundante
		df_file.drop(0, axis=1, inplace=True)

	if(param=='IV'):
		# eliminar columnas innecesarias (potencias)
		df_file.drop([6,7,8], axis=1, inplace=True)
		
		print(df_file)
		
	# guardar archivo
	file_name_new = df_file_name[param][res]
	df_file.to_csv(file_name_new, sep=SEPARATOR, header=None, index=None)


# función para promediar los datos de V y I de los archivos
# res: '60', '40', '20', '10', '6R6'
# axis: 0, 1 = filas, columnas
# modif: modificador del nombre del archivo ('crudos', 'ave_col', 'ave_row', '')
def average_iv_file(res, axis, modif=''):
	
	param = 'IV' # solo se promedian los Vs y Is
	
	# leer archivo
	if(modif != ''):
		file_name = df_file_name[param][res][:-4]+'_'+modif+'.csv'
	else:
		file_name = df_file_name[param][res]
	
	df_file = pd.read_csv(file_name, sep=SEPARATOR, header=None)
	
	if(axis==0): # promediar filas
		# agrupar y promediar
		df_file['group'] = [i//3 for i in range(len(df_file))] # columna auxiliar de referencia
		# print(df_file)
		
		df_file = df_file.groupby('group').mean()
		# print(df_file)
		
		df_file.reset_index(drop=True, inplace=True)
		# print(df_file)
		
		file_name_new = df_file_name[param][res][:-4]+'_'+'ave_row'+'.csv' # nombre archivo
		
	if(axis==1): # promediar columnas
		# agrupar y promediar
		groups = [[0,1,2], [3,4,5]]
		cols = df_file.columns
		groups2 = [cols[i:i+3] for i in range(0, len(cols), 3)]
		print(f'groups: {groups},   groups 2: {groups2}')
		
		print(df_file)
		df_file = pd.DataFrame( {
								0: df_file[groups[0]].mean(axis=1),
								1: df_file[groups[1]].mean(axis=1)
								} )
		print(df_file)
		
		file_name_new = df_file_name[param][res][:-4]+'_'+'ave_col'+'.csv' # nombre archivo
	
	# guardar archivo
	df_file.to_csv(file_name_new, sep=SEPARATOR, header=None, index=None)


# función para unir los archivos de TW y IV en uno solo
# res: '60', '40', '20', '10', '6R6'
# modif_tw: modificador del nombre del archivo de TW ('crudos', '')
# modif_iv: modificador del nombre del archivo de IV ('crudos', 'ave_col', 'ave_row', '')
def group_twiv_file(res, modif_tw='', modif_iv=''):
	# leer archivo
	if(modif_tw != ''):
		file_name_tw = df_file_name['TW'][res][:-4]+'_'+modif_tw+'.csv'
	else:
		file_name_tw = df_file_name['TW'][res]
	
	df_file_tw = pd.read_csv(file_name_tw, sep=SEPARATOR, header=None)
	
	if(modif_iv != ''):
		file_name_iv = df_file_name['IV'][res][:-4]+'_'+modif_iv+'.csv'
	else:
		file_name_iv = df_file_name['IV'][res]
	
	df_file_iv = pd.read_csv(file_name_iv, sep=SEPARATOR, header=None)
	
	# unir archivos
	df_file = pd.concat([df_file_tw, df_file_iv], axis=1)
	
	# guardar archivo
	file_name_new = 'T-W-I-V' + '_' + res + '_Tri.csv'
	df_file.to_csv(file_name_new, sep=SEPARATOR, header=None, index=None)


# clean_file('IV', '40')

# clean_file('TW', '40')

# average_iv_file('40')

# average_iv_file('40', 0)

# average_iv_file('40', 1, 'ave_row')

group_twiv_file('40', '', 'ave_col')

# print('working')

