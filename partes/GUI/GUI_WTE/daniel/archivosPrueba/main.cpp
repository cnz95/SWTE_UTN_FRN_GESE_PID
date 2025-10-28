#include <iostream>
//#include <cstring>
#include <vector>
//#include <cstdint>
#include <string>


using namespace std;

int main()
{
    FILE *Manipulador;
    Manipulador= fopen("D:\\Proyecto emulador aerogenerador\\rotor.csv", "rb");

    char var;
    int cont=0;
    int cont1=0;
    if (Manipulador== NULL)
    {
        printf("Error al abrir");
        return -1;
    }
    //tamaño del archivo y cantidad de renglones

    fseek(Manipulador,0,SEEK_END);
    int Peso= ftell(Manipulador);
    fseek(Manipulador,0,SEEK_SET);

    int num;
    for (int i=0; i<Peso; i++)
    {
        fread(&var, sizeof(char),1,Manipulador);
        if(var=='\n')
        cont++;
    }
   //  int *Lineas= new int[cont];
     vector<int> Lineas(cont);
     //printf("cantidad de lineas totales%d",cont);

     fseek(Manipulador,0,SEEK_SET);
     for (int i=0; i<Peso; i++)
     {
         fread(&var, sizeof(char),1,Manipulador);
         if(var=='\n')
         {
             num=ftell(Manipulador);
             Lineas[cont1]=num;
             cont1++;
         }
     }

    fseek(Manipulador,Lineas[2],SEEK_SET);

    //////////////////////////////////////////////////////////////////////

//   //leo el archivo y separo datos y lo imprimo en pantalla
     int cantdatos= (Lineas[cont-3]-Lineas[2]);

  //  string cadena="";
   int c=0;
   int c1=0;


        for (int i=0; i<(cantdatos); i++)
        {
            fread(&var, sizeof(char),1,Manipulador);
            if(var==';')
                c++;
            if(var=='\n')
                c1++;

        }

 fseek(Manipulador,Lineas[2],SEEK_SET);




//      printf("cantidada del vel vector de datos %d\n", c+c1);
//         printf("cantidad datos %d", cantdatos);


    vector<string> datos(c1+c);
    int c3=0;
    string aux;


    for (int i=0; i<(cantdatos); i++)
    {
        fread(&var, sizeof(char),1,Manipulador);
        //if(var!=';'|| var!='\n'){
        if(var!=';'&& var!='\n'){
          aux.push_back(var);
        //}
        }else{
            datos[c3]=aux;

            c3++;
            aux.clear();

        }

    }

    fseek(Manipulador,Lineas[2],SEEK_SET);

//    for(int i=0;i<datos.size();i++)
//        std::cout << datos[i] << std::endl;
   // vector< uint8_t> Vecent();
//std::vector<uint8_t> vector_enteros;





//    delete []Lineas;
//   delete []datos;


    fclose(Manipulador);
    return 0;

}
