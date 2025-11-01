

#include <vector>
#include <string>

#include "data_handler.h"




using namespace std;


// private functions prototypes

/* Function: verifies the turbine data
 * Parameters: matrix with torque data, two vectors with omega and wind data
 * Returned values: flag indicating if data has the correct format
 */
bool verify_turb_data(vector<vector<float>> turb_data, vector<float> omega, vector<float> wind);

/* Function: verifies the simulation data
 * Parameters: vector with wind values to simulate, vector with delta time for each wind value
 * Returned values: flag indicating if proccess was sucessfull
 */
bool verify_sim_data(vector<float> wind_sim, vector<float> time_sim);

// ESTOS TAL VEZ TENDRÍAN QUE IR EN OTRO ARCHIVO PARA QUE QUEDE MÁS ORDENADO
bool matrix_string_to_float(vector<vector<string>> matrix_string, vector<vector<float>>& matrix_float);
// ESTOS TAL VEZ TENDRÍAN QUE IR EN OTRO ARCHIVO PARA QUE QUEDE MÁS ORDENADO
bool vector_string_to_float(vector<string> vector_string, vector<float>& vector_float);



// //////////////////// PARA PRUEBAS //////////////////////
static vector<string> wind_sim_data_str_static;
static vector<string> time_sim_data_str_static;

void set_wind_time(vector<string> wind_str_p, vector<string>time_str_p)
{
    wind_sim_data_str_static = wind_str_p;
    time_sim_data_str_static = time_str_p;
}
// //////////////////// PARA PRUEBAS //////////////////////



// public functions implementations

bool rx_turb_data()
{
    bool flag_ok_1 = false;
    bool flag_ok_2 = false;
    bool flag_ok_3 = false;

    // recibir datos de turbina

    // solo para probar // 5 , 6 , 7  [m/s]
//    vector<vector<string>> torque_data_str={{"2.64E+00", "3.80E+00", "5.17E+00"},
//                                            {"3.25E+00", "4.54E+00", "6.08E+00"},
//                                            {"5.70E+00", "6.37E+00", "1.31E+01"},
//                                            {"9.93E+00", "1.22E+01", "7.47E+00"},
//                                            {"8.55E+00", "1.42E+01", "1.88E+01"},
//                                            {"6.76E+00", "1.19E+01", "1.84E+01"},
//                                            {"5.13E+00", "9.73E+00", "1.57E+01"},
//                                            {"3.73E+00", "7.78E+00", "1.32E+01"},
//                                            {"2.44E+00", "5.96E+00", "1.10E+01"},
//                                            {"1.15E+00", "4.43E+00", "8.84E+00"},
//                                            {"-1.31E-01", "2.88E+00", "6.93E+00"},
//                                            {"-1.40E+00", "1.36E+00", "5.12E+00"},
//                                            {"-2.82E+00", "-1.88E-01", "3.32E+00"},
//                                            {"-4.29E+00", "-1.76E+00", "1.58E+00"}};

//    vector<string> omega_data_str = {"1.00E-02", "5.00E+01", "1.00E+02", "1.50E+02", "2.00E+02", "2.50E+02", "3.00E+02", "3.50E+02", "4.00E+02", "4.50E+02", "5.00E+02", "5.50E+02", "6.00E+02", "6.50E+02"};
//    vector<string> wind_data_str = {"5E+00", "6E+00", "7E+00"};


//    // --------------------------------------- 1m/s ----- 2m/s ----- 3m/s ----- 4m/s ----- 5m/s ----- 6m/s ---- 7m/s ----- 8m/s ----- 9m/s ----- 10m/s ---- 11m/s ---- 12m/s -
//    vector<vector<string>> torque_data_str = {{"0.042"}, {"0.168"}, {"0.38"},  {"0.67"},  {"1.05"},  {"1.52"}, {"2.06"},  {"2.70"},  {"3.42"},  {"4.22"},  {"5.11"},  {"6.08"},
//                                              {"0.195"}, {"0.695"}, {"0.832"}, {"1.05"},  {"1.41"},  {"1.88"}, {"2.47"},  {"3.17"},  {"3.96"},  {"4.84"},  {"5.80"},  {"6.85"},
//                                              {"0.058"}, {"0.783"}, {"2.07"},  {"2.79"},  {"3.06"},  {"3.34"}, {"3.71"},  {"4.22"},  {"4.87"},  {"5.64"},  {"6.52"},  {"7.53"},
//                                              {"0.0"},   {"0.477"}, {"1.76"},  {"3.68"},  {"5.43"},  {"6.27"}, {"6.68"},  {"7.10"},  {"7.51"},  {"8.01"},  {"8.72"},  {"9.50"},
//                                              {"0.0"},   {"0.280"}, {"1.40"},  {"3.27"},  {"5.75"},  {"8.17"}, {"9.50"},  {"10.29"}, {"10.76"}, {"11.31"}, {"11.86"}, {"12.41"},
//                                              {"0.0"},   {"0.079"}, {"1.04"},  {"2.79"},  {"5.23"},  {"8.24"}, {"11.23"}, {"13.27"}, {"14.53"}, {"15.31"}, {"15.86"}, {"16.49"},
//                                              {"0.0"},   {"0.0"},   {"0.75"},  {"2.27"},  {"4.60"},  {"7.62"}, {"11.23"}, {"14.84"}, {"17.59"}, {"19.32"}, {"20.49"}, {"21.20"},
//                                              {"0.0"},   {"0.0"},   {"0.441"}, {"1.81"},  {"3.99"},  {"6.89"}, {"10.44"}, {"14.60"}, {"18.77"}, {"22.30"}, {"24.58"}, {"26.31"},
//                                              {"0.0"},   {"0.0"},   {"0.145"}, {"1.44"},  {"3.34"},  {"6.18"}, {"9.58"},  {"13.74"}, {"18.45"}, {"23.24"}, {"27.40"}, {"30.39"},
//                                              {"0.0"},   {"0.0"},   {"0.0"},   {"1.01"},  {"2.80"},  {"5.40"}, {"8.79"},  {"12.80"}, {"17.51"}, {"22.77"}, {"28.11"}, {"32.98"},
//                                              {"0.0"},   {"0.0"},   {"0.0"},   {"0.516"}, {"2.21"},  {"4.46"}, {"7.68"},  {"11.62"}, {"16.18"}, {"21.44"}, {"27.33"}, {"33.29"},
//                                              {"0.0"},   {"0.0"},   {"0.0"},   {"0.019"}, {"1.55"},  {"3.74"}, {"6.55"},  {"10.44"}, {"14.76"}, {"19.94"}, {"25.75"}, {"32.19"},
//                                              {"0.0"},   {"0.0"},   {"0.0"},   {"0.0"},   {"0.934"}, {"2.99"}, {"5.59"},  {"9.03"},  {"13.74"}, {"18.45"}, {"24.02"}, {"30.46"},
//                                              {"0.0"},   {"0.0"},   {"0.0"},   {"0.0"},   {"0.312"}, {"2.21"}, {"4.79"},  {"7.85"},  {"12.01"}, {"17.12"}, {"22.46"}, {"28.58"}};

    // --------------------------------------- 1m/s ---- 2m/s --- 3m/s --- 4m/s --- 5m/s --- 6m/s -- 7m/s --- 8m/s --- 9m/s --- 10m/s -- 11m/s -- 12m/s -
//    vector<vector<string>> torque_data_str = {{"0.042", "0.168", "0.38",  "0.67",  "1.05",  "1.52", "2.06",  "2.70",  "3.42",  "4.22",  "5.11",  "6.08"},
//                                              {"0.195", "0.695", "0.832", "1.05",  "1.41",  "1.88", "2.47",  "3.17",  "3.96",  "4.84",  "5.80",  "6.85"},
//                                              {"0.058", "0.783", "2.07",  "2.79",  "3.06",  "3.34", "3.71",  "4.22",  "4.87",  "5.64",  "6.52",  "7.53"},
//                                              {"0.0",   "0.477", "1.76",  "3.68",  "5.43",  "6.27", "6.68",  "7.10",  "7.51",  "8.01",  "8.72",  "9.50"},
//                                              {"0.0",   "0.280", "1.40",  "3.27",  "5.75",  "8.17", "9.50",  "10.29", "10.76", "11.31", "11.86", "12.41"},
//                                              {"0.0",   "0.079", "1.04",  "2.79",  "5.23",  "8.24", "11.23", "13.27", "14.53", "15.31", "15.86", "16.49"},
//                                              {"0.0",   "0.0",   "0.75",  "2.27",  "4.60",  "7.62", "11.23", "14.84", "17.59", "19.32", "20.49", "21.20"},
//                                              {"0.0",   "0.0",   "0.441", "1.81",  "3.99",  "6.89", "10.44", "14.60", "18.77", "22.30", "24.58", "26.31"},
//                                              {"0.0",   "0.0",   "0.145", "1.44",  "3.34",  "6.18", "9.58",  "13.74", "18.45", "23.24", "27.40", "30.39"},
//                                              {"0.0",   "0.0",   "0.0",   "1.01",  "2.80",  "5.40", "8.79",  "12.80", "17.51", "22.77", "28.11", "32.98"},
//                                              {"0.0",   "0.0",   "0.0",   "0.516", "2.21",  "4.46", "7.68",  "11.62", "16.18", "21.44", "27.33", "33.29"},
//                                              {"0.0",   "0.0",   "0.0",   "0.019", "1.55",  "3.74", "6.55",  "10.44", "14.76", "19.94", "25.75", "32.19"},
//                                              {"0.0",   "0.0",   "0.0",   "0.0",   "0.934", "2.99", "5.59",  "9.03",  "13.74", "18.45", "24.02", "30.46"},
//                                              {"0.0",   "0.0",   "0.0",   "0.0",   "0.312", "2.21", "4.79",  "7.85",  "12.01", "17.12", "22.46", "28.58"}};

//    vector<string> omega_data_str = {"0.002", "1.00E+01", "2.00E+01", "3.00E+01", "3.80E+01", "4.60E+01", "5.40E+01", "6.20E+01", "7.00E+01", "7.80E+01", "8.80E+01", "9.80E+01", "1.00E+02", "1.00E+02"};
    // p/Delta 10 Ohm:  T=5% -> W=16%  ;  T=7% -> W=25%
    // p/Delta 20 Ohm:  T=5% -> W=36%  ;  T=7% -> W=54%

    // - set 2 -------------------------------- 1m/s ---- 2m/s ---- 3m/s ---- 4m/s ---- 5m/s ---- 6m/s ---- 7m/s ----- 8m/s ---- 9m/s ---- 10m/s --- 11m/s --- 12m/s -
    vector<vector<string>> torque_data_str = {{"0.0326", "0.1303", "0.2933", "0.5212", "0.8121", "1.1758", "1.5939", "2.0848", "2.6424", "3.2606", "3.9455", "4.6909"},
                                              {"0.1509", "0.5370", "0.6424", "0.8121", "1.0909", "1.4545", "1.9091", "2.4485", "3.0545", "3.7333", "4.4788", "5.2909"},
                                              {"0.0447", "0.6042", "1.6000", "2.1515", "2.3636", "2.5758", "2.8606", "3.2545", "3.7576", "4.3515", "5.0364", "5.8121"},
                                              {"0.0000", "0.3685", "1.3576", "2.8424", "4.1879", "4.8364", "5.1576", "5.4788", "5.8000", "6.1818", "6.7273", "7.3333"},
                                              {"0.0000", "0.2164", "1.0788", "2.5212", "4.4364", "6.3030", "7.3333", "7.9394", "8.3030", "8.7273", "9.1515", "9.5758"},
                                              {"0.0000", "0.0612", "0.8061", "2.1515", "4.0364", "6.3636", "8.6667", "10.2424", "11.2121", "11.8182", "12.2424", "12.7273"},
                                              {"0.0000", "0.0000", "0.5782", "1.7515", "3.5515", "5.8788", "8.6667", "11.4545", "13.5758", "14.9091", "15.8182", "16.3636"},
                                              {"0.0000", "0.0000", "0.3400", "1.4000", "3.0788", "5.3212", "8.0606", "11.2727", "14.4848", "17.2121", "18.9697", "20.3030"},
                                              {"0.0000", "0.0000", "0.1121", "1.1091", "2.5818", "4.7697", "7.3939", "10.6061", "14.2424", "17.9394", "21.1515", "23.4545"},
                                              {"0.0000", "0.0000", "0.0000", "0.7818", "2.1636", "4.1697", "6.7879", "9.8788", "13.5152", "17.5758", "21.6970", "25.4545"},
                                              {"0.0000", "0.0000", "0.0000", "0.3982", "1.7030", "3.4424", "5.9273", "8.9697", "12.4848", "16.5455", "21.0909", "25.6970"},
                                              {"0.0000", "0.0000", "0.0000", "0.0151", "1.2000", "2.8848", "5.0545", "8.0606", "11.3939", "15.3939", "19.8788", "24.8485"},
                                              {"0.0000", "0.0000", "0.0000", "0.0000", "0.7212", "2.3152", "4.3212", "6.9697", "10.6061", "14.2424", "18.5455", "23.5152"},
                                              {"0.0000", "0.0000", "0.0000", "0.0000", "0.2412", "1.7030", "3.6970", "6.0606", "9.2727", "13.2121", "17.3333", "22.0606"}};

    vector<string> omega_data_str = {"2.09E-03", " 1.05E+01", " 2.09E+01", " 3.14E+01", " 3.97E+01", " 4.81E+01", " 5.64E+01", " 6.48E+01", " 7.32E+01", " 8.15E+01", " 9.20E+01", " 1.00E+02", " 1.00E+02", " 1.00E+02"};


    vector<string> wind_data_str = {"1E+00", "2E+00", "3E+00", "4E+00", "5E+00", "6E+00", "7E+00", "8E+00", "9E+00", "1E+01", "1.1E+01", "1.2E+01"};


    // convertir a formato final
    uint8_t dim_omega = torque_data_str.size();
    uint8_t dim_wind = torque_data_str[0].size();
    vector<float> omega_data_float(dim_omega);
    vector<float> wind_data_float(dim_wind);
    vector<vector<float>> torque_data_float(dim_omega,wind_data_float);
    flag_ok_1 = matrix_string_to_float(torque_data_str, torque_data_float);
    flag_ok_2 = vector_string_to_float(omega_data_str, omega_data_float);
    flag_ok_3 = vector_string_to_float(wind_data_str, wind_data_float);

    // verificar datos recibidos
    if( flag_ok_1 && flag_ok_2 && flag_ok_3 )
    {
        // verificar dimensiones y otros parámetros
        if( ( torque_data_str.size() == dim_omega ) || ( torque_data_str[0].size() == dim_wind ) )
        {
            // guardar los datos en las variables correspondientes
            init_turb_data(dim_omega, dim_wind);

            // llamar a función para guardar los datos
            write_turb_data(omega_data_float, wind_data_float, torque_data_float);

        }
        else
        {
            flag_ok_1 = false;
        }
    }

    return flag_ok_1;
}

bool rx_sim_data()
{
    bool flag_ok_1 = false;
    bool flag_ok_2 = false;

    // recibir datos de simulación

    // solo para probar // 5 , 7  [m/s]
//    vector<string> wind_sim_data_str = {"11.00E+00", "9.00E+00", "8.00E+00", "7.00E+00", "7.00E+00", "6.00E+00"};
//    vector<string> wind_sim_data_str = {"11.00E+00", "8.00E+00", "7.00E+00", "7.00E+00", "7.00E+00", "6.00E+00", "6.00E+00"};
//    vector<string> wind_sim_data_str = {"11.00E+00", "9.00E+00", "10.00E+00", "9.00E+00", "8.00E+00", "7.00E+00", "6.00E+00"}; // arranque (9-8-...) para evitar la parte baja de la curva
    //vector<string> wind_sim_data_str = {"5.00E+00", "7.00E+00", "7.00E+00", "7.00E+00", "7.00E+00", "7.00E+00", "7.00E+00"};
    //vector<string> wind_sim_data_str = wind_sim_data_str_static; // valores obtenidos con otra función
    //vector<string> wind_sim_data_str = {"9.00E+00"};

//    vector<string> time_sim_data_str = {"2.00E+01", "2.00E+01", "2.00E+01", "2.00E+01", "2.00E+01", "2.00E+01"};
//    vector<string> time_sim_data_str = {"2.00E+01", "2.00E+01", "2.00E+01", "2.00E+01", "2.00E+01", "2.00E+01", "2.00E+01"};
//    vector<string> time_sim_data_str = {"2.00E+01", "2.00E+01", "0.50E+01", "2.00E+01", "2.00E+01", "2.00E+01", "2.00E+01"};
    //vector<string> time_sim_data_str = time_sim_data_str_static; // valores obtenidos con otra función
    //vector<string> time_sim_data_str = {"3.0E+01"};


    // Pruebas Convertidor:
    // Arranque gradual para verificar funcionamiento
//    vector<string> wind_sim_data_str = {"1.00E+00", "2.00E+00", "3.00E+00", "4.00E+00", "5.00E+00", "6.00E+00"};
//    vector<string> time_sim_data_str = {"4.00E+01", "4.00E+01", "4.00E+01", "4.00E+01", "4.00E+01", "4.00E+01"};
//        vector<string> wind_sim_data_str = {"4.00E+00", "5.00E+00", "6.00E+00"};
//        vector<string> time_sim_data_str = {"4.00E+01", "4.00E+01", "4.00E+01"};
    // Valores de viento de interés + paso inicial + paso final
//    vector<string> wind_sim_data_str = {"6.00E+00", "7.00E+00", "8.00E+00", "9.00E+00", "10.00E+00", "6.00E+00"};
//    vector<string> time_sim_data_str = {"6.00E+01", "6.00E+01", "6.00E+01", "6.00E+01", "6.00E+01", "6.00E+01"};
//    vector<string> time_sim_data_str = {"2.00E+01", "2.00E+01", "2.00E+01", "2.00E+01", "2.00E+01", "2.00E+01"};
    // Valores de viento de interés !!!
//    vector<string> wind_sim_data_str = {"6.00E+00", "7.00E+00", "8.00E+00", "9.00E+00", "10.00E+00"};
//    vector<string> time_sim_data_str = {"4.00E+01", "4.00E+01", "4.00E+01", "4.00E+01", "4.00E+01"};
//    vector<string> time_sim_data_str = {"6.00E+01", "6.00E+01", "6.00E+01", "6.00E+01", "6.00E+01"};
    // Valores de viento FIJO (mucho tiempo)
//        vector<string> wind_sim_data_str = {"10.00E+00"};
//        vector<string> time_sim_data_str = {"6.00E+02"};
    // gradual inverso
        vector<string> wind_sim_data_str = {"7.00E+00", "6.00E+00", "5.00E+00", "4.00E+00", "3.00E+00", "2.00E+00", "1.00E+00"};
        vector<string> time_sim_data_str = {"4.00E+01", "4.00E+01", "4.00E+01", "4.00E+01", "4.00E+01", "4.00E+01", "4.00E+01"};


    // convertir a formato final
    uint8_t dim_wind = wind_sim_data_str.size();
    uint8_t dim_time = time_sim_data_str.size();
    vector<float> wind_sim_data(dim_wind);
    vector<float> time_sim_data(dim_time);
    flag_ok_1 = vector_string_to_float(wind_sim_data_str, wind_sim_data);
    flag_ok_2 = vector_string_to_float(time_sim_data_str, time_sim_data);

    // verificar datos recibidos
    if(flag_ok_1 && flag_ok_2 )
    {
        // verificar dimensiones y otros parámetros
        if(dim_time==dim_wind)
        {
            // guardar los datos en las variables correspondientes
            init_sim_data(dim_wind);
            // llamar a función para guardar los datos
            write_sim_data(wind_sim_data, time_sim_data);
        }
        else
        {
            flag_ok_1 = false;
        }
    }

    return flag_ok_1;
}


// private functions implementations

bool verify_turb_data(vector<vector<float>> turb_data, vector<float> omega, vector<float> wind)
{
    bool flag_ok = false;

    // verificar datos
    flag_ok = true;

    return flag_ok;
}

bool verify_sim_data(vector<float> wind_sim, vector<float> time_sim)
{
    bool flag_ok = false;

    // verificar datos
    flag_ok = true;

    return flag_ok;
}


bool matrix_string_to_float(vector<vector<string>> matrix_string, vector<vector<float>>& matrix_float)
{
    bool flag_ok = true;
    uint8_t dim_omega = matrix_string.size();
    uint8_t dim_wind = matrix_string[0].size();
    for(uint8_t i_omega = 0; i_omega<dim_omega; i_omega++)
    {
        for(uint8_t i_wind = 0; i_wind<dim_wind; i_wind++)
        {
            try
            {
                matrix_float[i_omega][i_wind] = stof(matrix_string[i_omega][i_wind]);
            }
            catch(...)
            {
                flag_ok = false;
            }
        }
    }
    return flag_ok;
}

bool vector_string_to_float(vector<string> vector_string, vector<float>& vector_float)
{
    bool flag_ok = true;
    uint8_t dim = vector_string.size();
    for(uint8_t i = 0; i<dim; i++)
    {
        try
        {
            vector_float[i] = stof(vector_string[i]);
        }
        catch(...)
        {
            flag_ok = false;
        }
    }
    return flag_ok;
}



