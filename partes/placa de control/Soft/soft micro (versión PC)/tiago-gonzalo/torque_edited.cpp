#include <iostream>
#include <vector>

usini_omega namespace std;

int main()
{
    int dim_omega = 14;
    int dim_wind = 11;
    int i_wind = 0;
    int i_omega = 0;
    float current_wind = 2;
    float current_omega = 175;
    float current_torque = 2.0;
    float set_torque = 1.0;
    float inc_torque=0.1;
    float m,cte,torque_interp;
    float x1,x2,y1,y2;
                                    // omega, torque(wind=1m/s), torque(wind=2m/s), torque(wind=3m/s)
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
    vector <float> v_wind = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    vector <float> v_omega;
    for(int i=0;i<14;i++)
    {
        v_omega.push_back(m_torque[i][0]);
        cout<<v_omega[i]<<'\t'<<endl;
    }



    while (i_wind < dim_wind)
    {
        if( (v_wind[i_wind] <= current_wind) && (current_wind <= v_wind[i_wind]) )
        {
            while(i_omega < dim_omega)
            {
                if( (v_omega[i_omega] <= current_omega) && (current_omega <= v_omega[i_omega+1]) )
                {
                    x1=v_omega[i_omega];
                    x2=v_omega[i_omega+1];
                    y2=m_torque[i_omega+1][v_wind[i_wind]];
                    y1=m_torque[i_omega][v_wind[i_wind]];
                    m=(y2-y1)/(x2-x1);
                    cte=(-m*x1)+y1;
                    torque_interp=(m*current_omega)+cte;
                    //torque_interp=y2+(((y2-y1)/(x2-x1))*(current_wind-x1));
                    if(current_torque - torque_interp < 0)
                    {

                        set_torque+= inc_torque;
                    }
                    else
                    {

                        set_torque-= inc_torque;
                    }
                    i_omega = dim_omega;
                }
                i_omega++;
            }
            i_wind = dim_wind;
        }
        i_wind++;
    }
    cout << "Hello World!" << endl;
    return 0;
}
