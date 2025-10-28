#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

vector<vector<string>> leerCSV(const string& archivo) {
    vector<vector<string>> datos; // crear matriz
    ifstream archivoCSV(archivo);
    string linea; // cadena de caracteres

    while (getline(archivoCSV, linea)) {
        vector<string> fila; // crear vector de cadenas de caracteres
        stringstream ss(linea);
        string dato;

        while (getline(ss, dato, ',')) {
            fila.push_back(dato); // guardar una cadena de caracteres en el vector
        }

        datos.push_back(fila); // guardar el vector en la matriz
    }

    archivoCSV.close();
    return datos;
}

int main() {
    vector<vector<string>> datos = leerCSV("D:/Descargas/prueba.csv");

    // Imprimir los datos del vector
    for (const auto& fila : datos) {
        for (const auto& dato : fila) {
            cout << dato << " ";
        }
        cout << endl;
    }
    return 0;
}



// vector<vector<float>> datos; // crear matriz -> esta forma tendrían las características de la turbina
// vector<float> fila; // crear vector de cadenas de caracteres -> esta forma tendría la curva para un cierto valor de viento



// variables: torque_actual, omega_actual, velocidad_viento (tipo float)
// salida: float torque_consigna
// carga: omega = torque_consigna * K

