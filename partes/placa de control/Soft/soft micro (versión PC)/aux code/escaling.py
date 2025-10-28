
# módulos
import pandas
import copy

# constantes
CHAR_SEPARATOR = ';'
N_ROW_HEADER = 2
OMEGA_COLUMN = 'Omega [rpm]'
TORQUE_COLUM = 'T [Nm]'


#### load_table() ####

# función: obtiene la tabla con los valores a simular, desde un archivo

# Parámetros:
# directory: directorio en el que se encuentra el archivo a leer
#            (formatos aceptados por pandas.read_csv)

# Valores de retorno:
# table: tabla leída desde el archivo
# flag_table: indicador de que la tabla se leyó correctamente

# módulos
def load_table(directory):
	
	# borrar filas no válidas
	flag_table = True # flag para indicar que la tabla se leyó correctamente
	try:
		# leer archivo
		csv_file = pandas.read_csv(directory, sep=CHAR_SEPARATOR, header=N_ROW_HEADER)
		
		for index, value in enumerate(csv_file[OMEGA_COLUMN]):
			if(pandas.isna(value)):
				csv_file.drop(index, inplace=True, axis=0)
		# borrar columnas no útiles
		for i in range(1,int(csv_file.shape[1]/2)):
			cad = OMEGA_COLUMN + '.' + str(i)
			csv_file.drop([cad], inplace=True, axis=1)
	except:
		csv_file = pandas.DataFrame()
		flag_table = False
	table = csv_file
	return table, flag_table



#### table_float2int() ####

# función: convertir la tabla con datos en punto flotante a otra con datos de tipo
#          entero sin signo de 8 bits,

# Parámetros:
# table: tabla con elementos en formato float
# omega_max: valor máximo de omega (equivalente a 100 !!! )
# torque_max: valor máximo de torque (equivalente a 100 !!! )

# Valores de retorno:
# table_int: tabla con elementos en formato entero sin signo de 8 bits


def table_process(table, omega_max, torque_max, vel_red):
	
	table_int = copy.copy(table)
	
	# escalar a 8 bits, anular valores negativos y redondear (en c/columna)
	table_int[OMEGA_COLUMN] = table[OMEGA_COLUMN]*(vel_red/1)*100.0/omega_max
	for i, element in enumerate(table_int[OMEGA_COLUMN]):
		if(element>100.0):
			table_int[OMEGA_COLUMN][i] = 100.0
	
	table_int[TORQUE_COLUM] = table[TORQUE_COLUM]*(1/vel_red)*100.0/torque_max
	for i, element in enumerate(table_int[TORQUE_COLUM]):
		if(element<0):
			table_int[TORQUE_COLUM][i] = 0
		if(element>100.0):
			table_int[TORQUE_COLUM][i] = 100.0
	
	for i in range(1,table.shape[1]-1):
		cad = TORQUE_COLUM + '.' + str(i)
		table_int[cad] = table[cad]*(1/vel_red)*100.0/torque_max
		for i, element in enumerate(table_int[cad]):
			if(element<0):
				table_int[cad][i] = 0
			if(element>100.0):
				table_int[cad][i] = 100.0
	
	# convertir a entero sin signo de 8 bits
	# table_int = table_int.astype('uint8')
	# se redondea antes para evitar el truncamiento acá
	
	return table_int


table, flag_ok = load_table("rotor_eolocal.csv")

print(table)

# omega max 1500
# torque max 42.45
table_2 = table_process(table, 1500, 42.45, 3)

print(table_2)

print(flag_ok)

FILE = 'rotor_eolocal_esc.csv'
SEPARATOR_CHAR = ','
DECIMAL_CHAR = '.'

table_2.to_csv(FILE, sep=SEPARATOR_CHAR, decimal=DECIMAL_CHAR)

