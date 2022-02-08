#include<iostream>
#include<math.h>
#include"Malliavin.h"
#include"utility.h"
using namespace std;

Malliavin::Malliavin(float S0_, float r_, float sigma_, float T_, float K_, int I_, int N_) :
	S0(S0_), r(r_), sigma(sigma_), T(T_), K(K_), I(I_), N(N_) {};

Malliavin::Malliavin():S0(100), r(0), sigma(0.2), T(1), K(100), I(100), N(10000) {};

// n is the time of simulation
vector<float> Malliavin::rho(string option_type) {
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
			r_sum += actualised_payoff * (WT / sigma - T);
		}
		else if (option_type == "ASIA_CALL") {
			r_sum += 0;
		}
		rhos.push_back(r_sum / (i + 1));
	}
	return rhos;
}


vector<float> Malliavin::delta(string option_type) {
	vector<float> Deltas, S;
	float WT, d_sum = 0;
	float sigma2 = pow(sigma, 2);
	float b = r - sigma2 / 2;

	for (int i = 0; i < N; i++) {
		S = generate_St(S0, r, sigma, I, h);
		float ST = S.back();

		if (option_type == "EUR_CALL") {
			float actualised_payoff = exp(-r * T) * payoff(option_type, S, K);
			WT = (log(ST / S0) - b) / sigma;
			d_sum += actualised_payoff * WT / (S0 * sigma * T);
		}
		else if (option_type == "ASIA_CALL") {
			float Integral_S = Integral(S, h); //integration of S from 0 to T
			float actualised_payoff = exp(-r * T) * payoff(option_type, S, K);
			d_sum += actualised_payoff * (2 * (ST - S0) / (S0 * sigma2 * Integral_S) + (1 - 2 * r / sigma2) / S0);
		}
		Deltas.push_back(d_sum/(i+1));
	}
	return Deltas;
}

vector<float> Malliavin::gamma(string option_type) {
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
			g_sum += actualised_payoff * (pow(WT, 2) / (sigma * T) - WT - 1 / sigma) / (pow(S0, 2) * sigma * T);
		}
		else if (option_type == "ASIA_CALL") {
			float Integral_S = Integral(S, h); //integration of S from 0 to T
			float Upper_ST = Integral_S / T; //integration over time
			float actualised_payoff = exp(-r * T) * payoff(option_type, S, K);
			g_sum += 4 * actualised_payoff * (pow(ST - S0, 2) + b * r * pow(T * Upper_ST, 2) - 2 * r * T * ST * Upper_ST + 2 * b * T * S0 * Upper_ST) / pow(sigma2 * S0 * T * Upper_ST, 2);
		}
		Gammas.push_back(g_sum / (i + 1));
	}
	return Gammas;
}

vector<float> Malliavin::vega(string option_type) {
	vector<float> Vegas, Gammas, S;
	float factor = pow(S0, 2) * sigma * T;
	float b = r - pow(sigma, 2) / 2;

	if (option_type == "EUR_CALL") {
		Gammas = gamma(option_type);
		Vegas = multiply(Gammas, factor);
	}
	else if (option_type == "ASIA_CALL") {
		float ST, actualised_payoff, Integral_S, Upper_ST, vega_sum;
		float INT_St_Wt_dt, INT_t_St_dt, INT_t2_St_dt, INT_INT_St_Wt_dt_dWt = 0;
		for (int i = 0; i < N; i++) {
			vector<float> Wt, vec_t, vec_t2;

			S = generate_St(S0, r, sigma, I, h);

			for (int j = 0; j < S.size(); j++) {
				Wt.push_back((log(S[j] / S0) - b) / sigma);
				vec_t.push_back(j * h);
				vec_t2.push_back(pow(j * h, 2));
			}

			INT_St_Wt_dt = Integral(vector_multiply(S, Wt), h);
			INT_t_St_dt = Integral(vector_multiply(vec_t, S), h);
			INT_t2_St_dt = Integral(vector_multiply(vec_t2, S), h);

			for (int k = 1; k < Wt.size(); k++) {
				INT_INT_St_Wt_dt_dWt += INT_St_Wt_dt * (Wt[k] - Wt[k - 1]);
			}

			ST = S.back();
			actualised_payoff = exp(-r * T) * payoff(option_type, S, K);
			Integral_S = Integral(S, h); //integration of S from 0 to T
			Upper_ST = Integral_S / T; //integration over time
			vega_sum = actualised_payoff * (INT_INT_St_Wt_dt_dWt / sigma * INT_t_St_dt + INT_t2_St_dt * INT_St_Wt_dt / pow(INT_t_St_dt, 2) - Wt.back());
			Vegas.push_back(vega_sum / (i + 1));
		}
		/*
		Gammas = gamma(option_type);
		Vegas = multiply(Gammas, factor);
		*/
	}
	return Vegas;
}

