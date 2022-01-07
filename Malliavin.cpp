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

Malliavin::Malliavin():S0(100), r(0), sigma(0.2), T(1), K(100), I(100), N(10000) {};

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
	float t, s, s_pre, dw;
	float b = r - pow(sigma, 2) / 2;
	for (int i = 1; i < I; i++) {
		t = i * h;
		s_pre = S.back();
		dw = sqrt(h) * generate_N01();
		s = s_pre + r * s_pre * h + sigma * s_pre * dw + pow(sigma, 2) * s_pre * (pow(dw, 2) - h) / 2;
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
vector<float> Malliavin::rho(string option_type, int N) {
	vector<float> rhos, S;
	float WT, r_sum = 0;
	float sigma2 = pow(sigma, 2);
	float b = r - sigma2 / 2;

	for (int i = 0; i < N; i++) {
		S = generate_St();
		float ST = S.back();

		if (option_type == "EUR_CALL") {
			float actualised_payoff = exp(-r * T) * payoff(option_type, S);
			WT = (log(ST / S0) - b) / sigma;
			r_sum += actualised_payoff * (WT / sigma - T);
		}
		else if (option_type == "ASIA_CALL") {
			r_sum += 0;
		}
		rhos.push_back(r_sum / (i + 1));
	}
	return rhos;
}


vector<float> Malliavin::delta(string option_type, int N) {
	vector<float> Deltas, S;
	float WT, d_sum = 0;
	float sigma2 = pow(sigma, 2);
	float b = r - sigma2 / 2;

	for (int i = 0; i < N; i++) {
		S = generate_St();
		float ST = S.back();

		if (option_type == "EUR_CALL") {
			float actualised_payoff = exp(-r * T) * payoff(option_type, S);
			WT = (log(ST / S0) - b) / sigma;
			d_sum += actualised_payoff * WT / (S0 * sigma * T);
		}
		else if (option_type == "ASIA_CALL") {
			float Integral_S = Sum(S) * h; //integration of S from 0 to T
			float actualised_payoff = exp(-r * T) * payoff(option_type, S);
			d_sum += actualised_payoff * (2 * (ST - S0) / (S0 * sigma2 * Integral_S) + (1 - 2 * r / sigma2) / S0);
		}
		Deltas.push_back(d_sum/(i+1));
	}
	return Deltas;
}

vector<float> Malliavin::gamma(string option_type, int N) {
	vector<float> Gammas, S;
	float WT, g_sum = 0;
	float sigma2 = pow(sigma, 2);
	float b = r - sigma2 / 2;

	for (int i = 0; i < N; i++) {
		S = generate_St();
		float ST = S.back();

		if (option_type == "EUR_CALL") {
			float actualised_payoff = exp(-r * T) * payoff(option_type, S);
			WT = (log(ST / S0) - b) / sigma;
			g_sum += actualised_payoff * (pow(WT, 2) / (sigma * T) - WT - 1 / sigma) / (pow(S0, 2) * sigma * T);
		}
		else if (option_type == "ASIA_CALL") {
			float Integral_S = Sum(S) * h; //integration of S from 0 to T
			float Upper_ST = Integral_S / T; //integration over time
			float actualised_payoff = exp(-r * T) * payoff(option_type, S);
			g_sum += 4 * actualised_payoff * (pow(ST - S0, 2) + b * r * pow(T * Upper_ST, 2) - 2 * r * T * ST * Upper_ST + 2 * b * T * S0 * Upper_ST) / pow(sigma2 * S0 * T * Upper_ST, 2);
		}
		Gammas.push_back(g_sum / (i + 1));
	}
	return Gammas;
}

vector<float> Malliavin::vega(string option_type, int N) {
	vector<float> Vegas, Gammas;
	float factor = pow(S0, 2) * sigma * T;
	if (option_type == "EUR_CALL") {
		Gammas = gamma(option_type, N);
	}
	else if (option_type == "ASIA_CALL") {
		Gammas = gamma(option_type, N);
	}
	Vegas = multiply(Gammas, factor);

	return Vegas;
}

//analytical Greeks
//no analytical solution for arithmetic asian option
float Malliavin::greeks(string greek_name, string option_type = "EUR_CALL") {
	float greek;
	if (option_type == "EUR_CALL") {
		if (greek_name == "delta") {
			greek = 0;
		}
		else if (greek_name == "gamma") {
			greek = 0;
		}
		else if (greek_name == "vega") {
			greek = 0;
		}
		else if (greek_name == "rho") {
			greek = 0;
		}
	}
	else if (option_type == "") {
		if (greek_name == "delta") {
			greek = 0;
		}
		else if (greek_name == "gamma") {
			greek = 0;
		}
		else if (greek_name == "vega") {
			greek = 0;
		}
		else if (greek_name == "rho") {
			greek = 0;
		}
	}
	return greek;
};