#include"FiniteDiff.h"
#include<iostream>
#include<math.h>
#include"utility.h"
using namespace std;

FiniteDiff::FiniteDiff(float S0_, float r_, float sigma_, float T_, float K_, int I_, int N_) :
	S0(S0_), r(r_), sigma(sigma_), T(T_), K(K_), I(I_), N(N_) {};

FiniteDiff::FiniteDiff() :S0(100), r(0), sigma(0.2), T(1), K(100), I(100), N(10000) {};

// n is the time of simulation
vector<float> FiniteDiff::rho(string option_type, int N) {
	vector<float> rhos, S;
	float WT, r_sum = 0;
	float sigma2 = pow(sigma, 2);
	float b = r - sigma2 / 2;

	for (int i = 0; i < N; i++) {
		S = generate_St(S0, r, sigma, I, h);
		float ST = S.back();

		if (option_type == "EUR_CALL") {
			float actualised_payoff = exp(-r * T) * payoff(option_type, S, K);
			WT = (log(ST / S0) - b) / sigma;
			r_sum += 0;
		}
		else if (option_type == "ASIA_CALL") {
			r_sum += 0;
		}
		rhos.push_back(r_sum / (i + 1));
	}
	return rhos;
}


vector<float> FiniteDiff::delta(string option_type, int N) {
	vector<float> Deltas, S;
	float sigma2 = pow(sigma, 2);
	float b = r - sigma2 / 2;
	float d_sum = 0;

	for (int i = 0; i < N; i++) {
		S = generate_St(S0, r, sigma, I, h);

		if (option_type == "EUR_CALL") {
			float ST = S.back();
			d_sum += exp(-r * T) * ST / S0 * (ST > S0);
		}
		else if (option_type == "ASIA_CALL") {
			float ST_bar = Mean(S);
			d_sum += exp(-r * T) * ST_bar / S0 * (ST_bar > S0);
		}
		Deltas.push_back(d_sum / (i + 1));
	}
	return Deltas;
}

vector<float> FiniteDiff::gamma(string option_type, int N) {
	vector<float> Gammas, S;
	float WT, g_sum = 0;
	float sigma2 = pow(sigma, 2);
	float b = r - sigma2 / 2;

	for (int i = 0; i < N; i++) {
		S = generate_St(S0, r, sigma, I, h);
		float ST = S.back();

		if (option_type == "EUR_CALL") {
			float actualised_payoff = exp(-r * T) * payoff(option_type, S, K);
			WT = (log(ST / S0) - b) / sigma;
			g_sum += 0;
		}
		else if (option_type == "ASIA_CALL") {
			float Integral_S = Sum(S) * h; //integration of S from 0 to T
			float Upper_ST = Integral_S / T; //integration over time
			float actualised_payoff = exp(-r * T) * payoff(option_type, S, K);
			g_sum += 0;
		}
		Gammas.push_back(g_sum / (i + 1));
	}
	return Gammas;
}

vector<float> FiniteDiff::vega(string option_type, int N) {
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

