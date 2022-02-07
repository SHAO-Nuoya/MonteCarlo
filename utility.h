#pragma once
#include <math.h>
#include <fstream>
#include <numeric>
#include <vector>
#include <iomanip>
using namespace std;

#define PI acos(-1)

//statistics
float Sum(vector<float> vec);
float Mean(vector<float> vec);
float Var(vector<float> vec);
double normalCDF(double value);
double normalPDF(double value);

//operations for vector
vector<float> multiply(vector<float> v, float d);
float Integral(vector<float> v, float step);

//simulation of spot
float generate_N01();
vector<float> generate_St(float S0, float r, float sigma, float I, float h);

//option type : European, Asian, Barrier
float payoff(string option_type, vector<float> S, float K);

//analytical values of greeks
float greeks(string greek_name, float* par, string option_type);

//output
void to_txt(vector<float> array, string filename);