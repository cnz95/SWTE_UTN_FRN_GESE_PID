#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int g_fin = 14; //cant. de elementos de g
    int v_fin = 11; //cant. de elementos de v
    int v = 0; //puntero para recorrer vector de velocidad de viento
    int g = 0; //puntero para recorrer vector de velocidad de giro
    float viento = 2; //dato velocidad de viento
    float giro = 175; //dato velocidad de giro
    float torque = 2.0; //dato torque
    float set_torque = 1.0; //torque consigna
    float inc_torque=0.1; // incremento de consigna de torque
    float m,cte,t_obtenido;
    float x1,x2,y1,y2;
                                    // omega, torque(Vv=1m/s), torque(Vv=2m/s), torque(Vv=3m/s)
    vector<vector<float>> m_torque = { {1.00E-02,	1.06E-01,	4.22E-01,	9.49E-01},
                                        {5.00E+01,	2.70E-01,	1.36E+00,	1.59E+00},
                                        {1.00E+02,	-4.46E-03,	1.08E+00,	3.55E+00},
                                        {1.50E+02,	-3.40E-01,	4.92E-01,	2.43E+00},
                                        {2.00E+02,	-1.23E+00,	-1.77E-02,	1.49E+00},
                                        {2.50E+02,	-2.26E+00,	-5.65E-01,	7.20E-01},
                                        {3.00E+02,	-3.24E+00,	-1.36E+00,	-4.71E-02},
                                        {3.50E+02,	-4.66E+00,	-2.88E+00,	-8.49E-01},
                                        {4.00E+02,	-6.15E+00,	-5.00E+00,	-1.71E+00},
                                        {4.50E+02,	-7.80E+00,	-6.54E+00,	-3.06E+00},
                                        {5.00E+02,	-9.70E+00,	-9.03E+00,	-4.81E+00},
                                        {5.50E+02,	-1.18E+01,	-1.05E+01,	-9.14E+00},
                                        {6.00E+02,	-1.40E+01,	-1.29E+01,	-1.15E+01},
                                        {6.50E+02,	-1.64E+01,	-1.57E+01,	-1.45E+01}};
    vector <float> v_viento = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    vector <float> v_giro;
    for(int i=0;i<14;i++)
    {
        v_giro.push_back(m_torque[i][0]);
        cout<<v_giro[i]<<'\t'<<endl;
    }



    while (v < v_fin) //Me aseguro de no llegar al final del vector viento
    {

        if (viento == v_viento[v]) //Encuentro velocidad de viento
        {
            while(g < g_fin)//Me aseguro de no llegar al final del vector giro
            {
                if (v_giro[g] <= giro && giro <= v_giro[g+1]) //Encuentro
                {
                    x1=v_giro[g];
                    x2=v_giro[g+1];
                    y2=m_torque[g+1][v_viento[v]];
                    y1=m_torque[g][v_viento[v]];
                    m=(y2-y1)/(x2-x1);
                    cte=(-m*x1)+y1;
                    t_obtenido=(m*giro)+cte;
                    //t_obtenido=y2+(((y2-y1)/(x2-x1))*(viento-x1));
                    if(torque - t_obtenido < 0)
                    {

                        set_torque+= inc_torque;
                    }
                    else
                    {

                        set_torque-= inc_torque;
                    }
                    g = g_fin;
                }
                g++;
            }
            v = v_fin;
        }
        v++;
    }
    cout << "Hello World!" << endl;
    return 0;
}
