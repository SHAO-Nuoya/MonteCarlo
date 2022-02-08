#include<iostream>
#include<math.h>
#include"MC_FiniteDiff.h"
#include"utility.h"
using namespace std;

MC_FiniteDiff::MC_FiniteDiff(float S0_, float r_, float sigma_, float T_, float K_, int I_, int N_) :
	S0(S0_), r(r_), sigma(sigma_), T(T_), K(K_), I(I_), N(N_) {};

MC_FiniteDiff::MC_FiniteDiff():S0(100), r(0), sigma(0.2), T(1), K(100), I(100), N(10000) {};


// n is the time of simulation
vector<float> MC_FiniteDiff::price(string option_type){
    vector<float> St,Prices;
    float d_sum = 0;
    for (int i = 0; i < N; i++) {
		St = generate_St(S0, r, sigma, I, h);
		float actualised_payoff = exp(-r * T) * payoff(option_type, St, K);
		d_sum += actualised_payoff;

		Prices.push_back(d_sum/(i+1));
	}
	return Prices;
}

vector<float> MC_FiniteDiff::delta(string option_type) {
	float dS0 = 1;
   
    vector<float> St1,St2;
    float d_sum1 = 0;
    float d_sum2 = 0;
    vector<float> Deltas;
    
    for (int i = 0; i < N; i++) {
		St1 = generate_St(S0-dS0, r, sigma, I, h);
        St2 = generate_St(S0+dS0, r, sigma, I, h);

		d_sum1 += exp(-r * T) * payoff(option_type, St1, K);
        d_sum2 += exp(-r * T) * payoff(option_type, St2, K);
        
        Deltas.push_back((d_sum2-d_sum1)/(i+1)/(2*dS0));
	}
	return Deltas;
}

vector<float> MC_FiniteDiff::gamma(string option_type) {
    float dS0 = 1;
   
    vector<float> St1,St,St2;
    float d_sum1 = 0;
    float d_sum = 0;
    float d_sum2 = 0;  
    vector<float> Gammas;

    for (int i = 0; i < N; i++) {
		St1 = generate_St(S0-dS0, r, sigma, I, h);
        St = generate_St(S0, r, sigma, I, h);
        St2 = generate_St(S0+dS0, r, sigma, I, h);
		float actualised_payoff1 = exp(-r * T) * payoff(option_type, St1, K);
        float actualised_payoff = exp(-r * T) * payoff(option_type, St, K);
        float actualised_payoff2 = exp(-r * T) * payoff(option_type, St2, K);
		d_sum1 += actualised_payoff1;
        d_sum += actualised_payoff;
        d_sum2 += actualised_payoff2;

        Gammas.push_back((d_sum2-2*d_sum+d_sum1)/(i+1)/pow(dS0,2));
	}
	return Gammas;
}

vector<float> MC_FiniteDiff::vega(string option_type) {
	float dsig = 0.1;
   
    vector<float> St1,St2;
    float d_sum1 = 0;
    float d_sum2 = 0;
    vector<float> Vegas;
      
    for (int i = 0; i < N; i++) {
		St1 = generate_St(S0, r, sigma-dsig, I, h);
        St2 = generate_St(S0, r, sigma+dsig, I, h);
		float actualised_payoff1 = exp(-r * T) * payoff(option_type, St1, K);
        float actualised_payoff2 = exp(-r * T) * payoff(option_type, St2, K);
		d_sum1 += actualised_payoff1;
        d_sum2 += actualised_payoff2;

        Vegas.push_back((d_sum2-d_sum1)/(i+1)/(2*dsig));
	}
	return Vegas;

}

