#include "mainwindow.h"
#include <QApplication>

//Delaracion librerias
#include <iostream>
#include <vector>
#include <string>
#include <QVector>
#include <QString>

//nota: un template una vez parametrizado con el tipo de dato no se puede reescribir
// investigar como se puede cambiar esto para utilizar menos

template<typename T> // plantilla para escribir datos con un tipo de dato a definir
//Muestreo de matriz del tipo vector sin nesecidad de expresar el tipo de dato.
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

template<typename H>// plantilla para escribir datos con un tipo de dato a definir
//Muestreo de matriz del tipo Qvector sin nesecidad de expresar el tipo de dato.
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

// Realiza el pasaje de datos de una matriz del tipo vector a una Qvector
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

template<typename RF>// plantilla para escribir datos con un tipo de dato a definir
// Realiza el proceso de modificar una matriz Qvector que cumpla con parametros de Torque indicados
//y la llena otra matriz que trabaja en porcentajes respecto a los mismos parametros.
void Escalamiento( float T_ref, QVector<QVector<RF>>&matrizQt,QVector<QVector<QString>>&matrizEscalada ){
        bool ok = false; // Variable para verificar si la conversión fue exitosa
          float aux;
          QString Aux2;
        int d= matrizQt.size();// cantidad de filas
        int c=matrizQt[0].size();// tamaño del vector de cada fila
        for(int i = 0; i<d; i++){
            //En la columna cero de la matriz cargo el valor directamente ya que el parametro omega no varia.
            Aux2= matrizQt[i][0];
             matrizEscalada[i][0] = Aux2;
                for (int j = 1;  j<(c); j++) {
                    //como el valor de referencia es flotante realizo la conversion de
                    //cada elemento de la matriz para comparar con el mismo
                      aux=matrizQt[i][j].toFloat(&ok);

                      if (ok) {
                          if ( aux>= T_ref)
                              matrizEscalada[i][j]= "100.0"; // Si es mayor o igual a T_ref es el 100%
                          else{
                          if (aux <= 0.0)
                              matrizEscalada[i][j]= "0.0"; // Si es menor  o igual a 0  es el 0%
                          else{
                              matrizEscalada[i][j]= QString::number((aux*100)/(T_ref));
                              // Para cualquier valor que este entre 0 % y 100% realizo la conversion de escalamiento
                          }}

                      }

               }


    }}

using namespace std;

int main(int argc, char *argv[])
{

    float T_ref = 51.2; // 51.2 Nm son la referencia (máximo) (equivale a 100%)// Valor de prueba para implementar el escalamiento
    // creacion de matriz de prueba con los siguientes parametros omega, torque(Vv=6m/s), torque(Vv=7m/s)
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


	vector<vector<string>> turb_data_str={{"1.00E+00", "5.0"},
                                          {"3.00E+00", "5.0"},
										  {"5.00E+00", "5.0"},
										  {"6.00E+00", "10.0"},
										  {"7.00E+00", "10.0"},
										  {"8.00E+00", "10.0"},
										  {"9.00E+00", "10.0"},
										  {"1.00E+01", "10.0"},
										  {"1.10E+01", "20.0"},
										  {"1.20E+01", "20.0"}};


    mostrarMatriz(turb_data_str);
    int s= turb_data_str.size();// cantidad de filas
    int b=turb_data_str[0].size();// tamaño del vector de cada fila

    QVector<QString> fila(b);

   // float aux_float;

    //QVector<QVector<QString>> turb_data_qt(turb_data_str.size()); // formato de la salida (valores entre 0 y 100)
     QVector<QVector<QString>>turb_data_qt(s,fila);
     QVector<QVector<QString>>MatrizEscalada(s,fila);
   pasaje(turb_data_qt,turb_data_str);

   mostrarMatrizQt(turb_data_qt);

  Escalamiento(T_ref,turb_data_qt, MatrizEscalada);

  mostrarMatrizQt(MatrizEscalada);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

