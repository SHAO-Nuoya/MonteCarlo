#include<iostream>
#include<math.h>
#include <random>
#include <chrono>
#include"Malliavin.h"
using namespace std;

Malliavin::Malliavin(float S0_, float r_, float sigma_, float T_, float K_, int I_, int N_) :
	S0(S0_), r(r_), sigma(sigma_), T(T_), K(K_), I(I_), N(N_) {};

Malliavin::Malliavin():S0(100), r(0.1), sigma(0.2), T(1), K(100), I(100), N(10000) {};

float Malliavin::generate_Wt(float t) {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine e(seed);
	normal_distribution<float> dis(0, t);
	float Wt = dis(e);
	return Wt;
}

vector<float> Malliavin::generate_St() {
	vector<float> S(I);
	S[0] = S0;
	float b, t;
	for (int i = 1; i < I; i++) {
		t = i * h;
		b = r - pow(sigma, 2) / 2;
		S[i] = S0 * exp(b * t + sigma * generate_Wt(t));
	}
	return S;
}

float Malliavin::payoff(string option_type, vector<float> S) {
	float pay_off = 0;
	if (option_type == "EUR_CALL") {
		pay_off = max(S.back() - K, float(0));
	}
	else if (option_type == "ASIA_CALL") {
		pay_off = max(Mean(S) - K, float(0));
	}
	return pay_off;
};

// n is the time of simulation
float Malliavin::delta(string option_type, int n) {
	vector<float> Deltas, S;
	float d;
	for (int i = 0; i < n; i++) {
		S = generate_St();

		if (option_type == "EUR_CALL") {
			d = exp(-r * T) * payoff(option_type, S) * generate_Wt(T) / (S0 * sigma * T);
		}
		else if (option_type == "ASIA_CALL") {
			d = exp(-r * T) * payoff(option_type, S) * (2 * (S.back() - S0) / (S0 * pow(sigma, 2) * Sum(S)) + (1 - 2 * r / pow(sigma, 2)) / S0);
		}
		Deltas.push_back(d);
	}
	return Mean(Deltas);
}
