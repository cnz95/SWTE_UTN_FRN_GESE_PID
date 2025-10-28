
#include "mainwindow.h"

#include <QApplication>


#include <iostream>

#include <vector>
#include <string>

#include <QVector>
#include <QString>

template<typename T>
    void mostrarMatriz(const std::vector<std::vector<T>>& matriz) {

        int s= matriz.size();// cantidad de filas
        int b=matriz[0].size();// tamaño del vector de cada fila
        for ( int i = 0;  i<s;i++) {
                for (int j = 0; j<b; j++) {
                    std::cout << matriz[i][j]<<" ";
                }
                std::cout << "\n";
        }
        std::cout << "...........................................................\n";

    }

template<typename H>
    void mostrarMatrizQt( const QVector<QVector<H>>&matriz){

        int d= matriz.size();// cantidad de filas
        int c=matriz[0].size();// tamaño del vector de cada fila
        for(int i = 0; i<d; i++){
                for (int j = 0;  j<(c); j++) {
                    std::cout << matriz[i][j].toStdString()<<" ";
                }
                std::cout << "\n";}
        std::cout << "...........................................................\n";

    }

    void pasaje(QVector<QVector<QString>>&matrizQt,const std::vector<std::vector<std::string>>&matriz){
        QString aux;
        int c=matrizQt[0].size();
        int d= matrizQt.size();
       for(int j=0;j<(d);j++){
       for(int i=0; i<c;i++)
       {

             aux = QString::fromStdString(matriz[j][i]);// el primer corchete devuelve el vector de la fila y con el segundo corchete se accede al mismo

         matrizQt[j][i]= aux;
       }}

    }
    template<typename RF>

    void Escalamiento( float T_ref, QVector<QVector<RF>>&matrizQt ){
        bool ok = false; // Variable para verificar si la conversión fue exitosa
          float aux;
        int d= matrizQt.size();// cantidad de filas
        int c=matrizQt[0].size();// tamaño del vector de cada fila
        for(int i = 0; i<d; i++){
                for (int j = 1;  j<(c); j++) {
                      aux=matrizQt[i][j].toFloat(&ok);

                      if (ok) {
                          if ( aux> T_ref)
                              matrizQt[i][j]=QString::number(T_ref);

                          if (aux < 0.0)
                              matrizQt[i][j]= "0.0";

                      }

               }
                                              }
    }

using namespace std;

int main(int argc, char *argv[])
{

    float T_ref = 51.2; // 51.2 Nm son la referencia (máximo) (equivale a 100%)

    // omega, torque(Vv=6m/s), torque(Vv=7m/s)

    std::vector<std::vector<std::string>> turb_data_str={{"1.00E-02", "3.80E+00", "5.17E+00"},
                  {"5.00E+01", "4.54E+00", "6.08E+00"},
                  {"1.50E+02", "1.22E+01", "1.31E+01"},
                  {"2.00E+02", "1.42E+01", "1.88E+01"},
                  {"2.50E+02", "1.19E+01", "1.84E+01"},
                  {"3.00E+02", "9.73E+00", "1.57E+01"},
                  {"3.50E+02", "7.78E+00", "1.32E+01"},
                  {"4.00E+02", "5.96E+00", "1.10E+01"},
                  {"4.50E+02", "4.43E+00", "8.84E+00"},
                  {"5.00E+02", "2.88E+00", "6.93E+00"},
                  {"5.50E+02", "1.36E+00", "5.12E+00"},
                  {"5.50E+02", "1.36E+00", "57.43E+00"},// fila agregada para probar el valor de referencia
                  {"6.00E+02", "-1.88E-01", "3.32E+00"},
                  {"6.50E+02", "-1.76E+00", "1.58E+00"}};

    mostrarMatriz(turb_data_str);
    int s= turb_data_str.size();// cantidad de filas
    int b=turb_data_str[0].size();// tamaño del vector de cada fila

    QVector<QString> fila(b);
   // float aux_float;

    //QVector<QVector<QString>> turb_data_qt(turb_data_str.size()); // formato de la salida (valores entre 0 y 100)
     QVector<QVector<QString>>turb_data_qt(s,fila);
       pasaje(turb_data_qt,turb_data_str);


   mostrarMatrizQt(turb_data_qt);
   Escalamiento(T_ref,turb_data_qt);
   mostrarMatrizQt(turb_data_qt);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

