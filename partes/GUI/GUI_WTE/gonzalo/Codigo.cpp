#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctype.h>

using namespace std;

vector<vector<string>> leerCSV(const string& archivo) {
    vector<vector<string>> datos;
    ifstream archivoCSV(archivo);
    string linea;

    while (getline(archivoCSV, linea)) {
        vector<string> fila;
        stringstream ss(linea);
        string dato;

        while (getline(ss, dato, ',')) {
            fila.push_back(dato);
        }

        datos.push_back(fila);
    }

    archivoCSV.close();
    return datos;
}

//Crear CSV desde una matriz de dos columnas
void Crear_csv(int** matriz,int rows, int cols, string* cabecera){
    int fila = rows+1;
    int columna = cols;
    ofstream archivo("D:/Descargas/Datos_variador.csv");
    int i;
    if(!archivo){
        cout<<"No se pudo crear el archivo"<<endl;
    }
    else{
        for (int i = 0; i < fila; i++) {
            if(i==0){
                for (int j = 0; j < columna; j++) {

                    archivo<< cabecera[j] << ";";

                }
            }
            else
            {

            for (int j = 0; j < columna; j++) {
                archivo<< matriz[i-1][j] << ";";
            }
            }
            archivo<<endl;
        }
        archivo.close();
    }
}

// Función para convertir dos vectores en una matriz
int** vectoresAMatriz2(int* vector1, int* vector2, int size1, int size2) {
    // Determinar el tamaño de la matriz
    int fila = (size1 > size2) ? size1 : size2;
    int columnas = 2;  // Cantidad de vectores

    // Crear la matriz con memoria dinámica
    int** matriz = new int*[fila];
    for (int i = 0; i < fila; i++) {
        matriz[i] = new int[columnas];
    }

    // Copiar los elementos de los vectores a la matriz
    for (int i = 0; i < size1; i++) {
        matriz[i][0] = vector1[i];
    }

    for (int i = 0; i < size2; i++) {
        matriz[i][1] = vector2[i];
    }

    return matriz;
}
// Función para convertir 5 vectores en una matriz
int** vectoresAMatriz(int* vector1, int* vector2, int* vector3, int* vector4, int* vector5,int rows, int cols) {

    // Crear la matriz con memoria dinámica
    int** matriz = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matriz[i] = new int[cols];
    }

    // Copiar los elementos de los vectores a la matriz
    for (int i = 0; i < rows; i++) {
        matriz[i][0] = vector1[i];
    }

    for (int i = 0; i < rows; i++) {
        matriz[i][1] = vector2[i];
    }

    for (int i = 0; i < rows; i++) {
        matriz[i][2] = vector3[i];
    }

    for (int i = 0; i < rows; i++) {
        matriz[i][3] = vector4[i];
    }

    for (int i = 0; i < rows; i++) {
        matriz[i][4] = vector5[i];
    }

    return matriz;
}


int main() {
    int vector1[]={0,1,2,3,4,5,6,7,8,9};
    int vector2[]={0,1,2,3,4,5,6,7,8,9};
    int vector3[]={0,1,2,3,4,1,6,7,8,9};
    int vector4[]={0,1,2,3,4,5,6,7,8,9};
    int vector5[]={0,1,2,3,4,5,6,7,8,9};
    string cabecera[]={"Tiempo","Velocidad de viento","Torque","Velocidad de giro","Tension","Corriente"};


    int size1 = sizeof(vector1) / sizeof(vector1[0]);
    int size2 = sizeof(vector2) / sizeof(vector2[0]);
    int size3 = sizeof(vector3) / sizeof(vector3[0]);
    int size4 = sizeof(vector4) / sizeof(vector4[0]);
    int size5 = sizeof(vector5) / sizeof(vector5[0]);


    // Determinar el tamaño de la matriz
    int rows = size1;
    rows = (rows > size2) ? rows : size2;
    rows = (rows > size3) ? rows : size3;
    rows = (rows > size4) ? rows : size4;
    rows = (rows > size5) ? rows : size5;
    int cols = 5;  // Cantidad de vectores

    // Convertir los vectores en una matriz
    int** matriz= vectoresAMatriz(vector1,vector2,vector3,vector4,vector5,rows,cols);


    //Se crea un archivo csv a partir de una matriz y un vector de cabecera
    Crear_csv(matriz,rows,cols,cabecera);

    return 0;
}
