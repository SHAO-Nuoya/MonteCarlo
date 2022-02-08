#include <iostream>
#include <math.h>
#include "utility.h"
#include "Malliavin_localized.h"
#include "random-singleton.hpp"

using namespace std;

Malliavin_localized::Malliavin_localized(float S0_, float r_, float sigma_, float T_, float K_, int I_, int N_, float lp_) :
    S0(S0_), r(r_), sigma(sigma_), T(T_), K(K_), I(I_), N(N_), lp(lp_) {};

Malliavin_localized::Malliavin_localized():S0(100), r(0), sigma(0.2), T(1), K(100), I(100), N(10000),lp(10) {};

// N is the number of simulations

vector<float> Malliavin_localized::delta(string option_type) {
    vector<float> Deltas, S;
    float WT;
    float YT;
    float d_sum = 0;
    float sigma2 = pow(sigma, 2);
    float b = r - sigma2 / 2;
    float term1 = 0;
    float term2 = 0;
    for (int i = 0; i < N; i++) {
        
        S = generate_St(S0, r, sigma, I, h);
        float ST = S.back();
        WT = (log(ST / S0) - b) / sigma;
        YT = ST/S0;
        
        if (option_type == "EUR_CALL") {
            term1 = exp(-r * T) * H(ST) * YT;
            term2 = exp(-r * T) * F_delta(ST) * WT/(S0 * sigma * T);
            
            d_sum += term1+term2 ;
        }
        Deltas.push_back(d_sum/(i+1));
    }
    return Deltas;
}

vector<float> Malliavin_localized::gamma(string option_type) {
    vector<float> Gammas, S;
    float WT, g_sum = 0;
    float sigma2 = pow(sigma, 2);
    float b = r - sigma2 / 2;
    float term1 =0;
    float term2 =0;
    
    for (int i = 0; i < N; i++) {
        S = generate_St(S0, r, sigma, I, h);
        float ST = S.back();
        WT = (log(ST / S0) - b);
        float YT = ST/S0;
        
        if (option_type == "EUR_CALL") {
            term1 = exp(-r * T)*I_fct(ST)*pow(YT,2);
            term2 = exp(-r * T)*F_gamma(ST)/(pow(S0,2)*sigma*T) * (pow(WT,2)/(sigma*T) - 1/sigma - WT);
            
            g_sum += (term1 + term2);
        }
        
        else if (option_type == "ASIA_CALL") {
            float Integral_S = Integral(S, h); //integration of S from 0 to T
            float Upper_ST = Integral_S / T; //integration over time
            float actualised_payoff = exp(-r * T) * payoff(option_type, S, K);
            g_sum += term1 + term2;
        }
        Gammas.push_back(g_sum / (i + 1));
    }
    return Gammas;
}

vector<float> Malliavin_localized::vega(string option_type) {
    vector<float> Vegas, S;
    float WT, v_sum = 0;
    float sigma2 = pow(sigma, 2);
    float b = r - sigma2 / 2;
    float term1 =0;
    float term2 =0;
    
    for (int i = 0; i < N; i++) {
        S = generate_St(S0, r, sigma, I, h);
        float ST = S.back();
        WT = (log(ST / S0) - b);
        
        
        if (option_type == "EUR_CALL") {
            term1 = exp(-r * T) * H(ST) * ST * (WT - sigma*T);
            term2 = exp(-r * T) * F_delta(ST) * (  pow(WT,2)/(sigma*T) - 1/sigma - WT  );
            // F_delta(ST)
            v_sum += (term1 + term2 );
        }
        Vegas.push_back(v_sum / (i + 1));
    }

    return Vegas;
}
    
float Malliavin_localized::H(float s){
        if (s < K - lp)
            return 0;
        else if( s >= K - lp && s <= K + lp)
            return (s-(K-lp))/(2*lp);
        else
            return 1;     
    }


float Malliavin_localized::G(float t){
        if (t < K - lp)
            return 0;
        else if( t >= K - lp && t <= K + lp)
            return pow((t-K+lp),2)/(4*lp);
        else
            return t-(K+lp)+lp;
    }


float Malliavin_localized::F_delta(float t){
    if(t>K)
        return t - K - G(t);
    else
        return 0-G(t);
    
    }

float Malliavin_localized::I_fct(float t){
    if (t-K<lp && t-K>-lp)
        return 1/(2*lp);
    else
        return 0;
    }


float Malliavin_localized::F_gamma_integ(float t){
    if (t < K-lp)
        return 0;
    else if (t<= K+lp && t>= K-lp)
        return lp * pow((t-(K-lp))/(2*lp),2);
    else
        return t-(K+lp)+lp;
}


float Malliavin_localized::F_gamma(float t){
    if(t>K)
        return t - K - F_gamma_integ(t);
    else
        return -F_gamma_integ(t);

    }
