/*
 * @Description: 
 * @Version: 1.0
 * @Author: SHAO Nuoya
 * @Date: 2021-12-27 23:42:12
 * @LastEditors: SHAO Nuoya
 * @LastEditTime: 2021-12-28 18:24:12
 */
#include<iostream>
#include<math.h>
#include <random>
#include <chrono>
#include"Malliavin.h"
using namespace std;

Malliavin::Malliavin(float S0_, float r_, float sigma_, float T_, float K_, int I_, int N_) :
	S0(S0_), r(r_), sigma(sigma_), T(T_), K(K_), I(I_), N(N_) {};

Malliavin::Malliavin():S0(100), r(0), sigma(0.2), T(1), K(100), I(1000), N(10000) {};

float Malliavin::generate_N01() {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine e(seed);
	normal_distribution<float> dis(0, 1);
	float N01 = dis(e);
	return N01;
}

vector<float> Malliavin::generate_St() {
	vector<float> S;
	S.push_back(S0);
	float b, t, s;
	for (int i = 1; i < I; i++) {
		t = i * h;
		b = r - pow(sigma, 2) / 2;
		s = S.back() * exp(b * h + sigma * sqrt(h) * generate_N01());
		S.push_back(s);
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
vector<float> Malliavin::delta(string option_type, int N) {
	vector<float> Deltas, S;
	float WT, d_sum = 0;
	for (int i = 0; i < N; i++) {
		S = generate_St();

		if (option_type == "EUR_CALL") {
			WT = (log(S.back() / S0) - (r - pow(sigma, 2) / 2)) / sigma;
			d_sum += exp(-r * T) * payoff(option_type, S) * WT / (S0 * sigma * T);
		}
		else if (option_type == "ASIA_CALL") {
			d_sum += exp(-r * T) * payoff(option_type, S) * (2 * (S.back() - S0) / (S0 * pow(sigma, 2) * Sum(S)*h) + (1 - 2 * r / pow(sigma, 2)) / S0);
		}
		Deltas.push_back(d_sum/(i+1));
	}
	return Deltas;
}
