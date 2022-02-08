#pragma once
#include<string>
#include<vector>

using namespace std;
class Malliavin_localized {
private:
    float S0; //current price of underlying
    float r; //risk free rate
    float sigma; //volatility
    float T; //maturity
    float K; //strike

public:
    int I; //time step number
    int N; //simulation time
    float h = T / I; //time step
    float lp;
    
    Malliavin_localized(float S0, float r, float sigma, float T, float K, int I, int N, float lp);
    Malliavin_localized();
    
    //simulation
    vector<float> rho(string option_type);
    vector<float> delta(string option_type);
    vector<float> gamma(string option_type);
    vector<float> vega(string option_type);
    float F_delta(float t);
    float G(float t);
    float H(float s);
    float I_fct(float t);
    float F_gamma_integ(float t);
    float F_gamma(float t);
};

