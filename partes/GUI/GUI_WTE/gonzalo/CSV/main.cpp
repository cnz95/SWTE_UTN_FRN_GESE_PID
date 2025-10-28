#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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
