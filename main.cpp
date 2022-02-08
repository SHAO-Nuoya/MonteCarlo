#include"Malliavin.h"
#include"PDE_FiniteDiff.h"
#include"MC_FiniteDiff.h"
#include"utility.h"
#include "Malliavin_localized.h"

#include <iostream>
using namespace std;


int main(void) {
	string option_type1 = "EUR_CALL";
	string option_type2 = "ASIA_CALL";


	// Parameters: S0, K, r, sigma, T
	float par[5] = { 100, 100, 0, 0.2, 1};

	// Theoretial Greeks value for EUR_CALL
	float eur_delta = greeks("delta", par, option_type1);
	float eur_gamma = greeks("gamma", par, option_type1);
	float eur_vega = greeks("vega", par, option_type1);
	vector<float> theo_eur_call_greeks = { eur_delta, eur_gamma, eur_vega};

	to_txt(theo_eur_call_greeks, "theo_eur_call_greeks");

	
	// Maliavin method
	cout << "Begin Malliavin method" << endl;
	Malliavin malliavin;

	vector<float> m_delta1 = malliavin.delta(option_type1);
	vector<float> m_delta2 = malliavin.delta(option_type2);
	
	vector<float> m_gamma1 = malliavin.gamma(option_type1);
	vector<float> m_gamma2 = malliavin.gamma(option_type2);
	
	vector<float> m_vega1 = malliavin.vega(option_type1);
	vector<float> m_vega2 = malliavin.vega(option_type2);

	to_txt(m_delta1, "M_Delta_" + option_type1);
	to_txt(m_delta2, "M_Delta_" + option_type2);

	to_txt(m_gamma1, "M_Gamma_" + option_type1);
	to_txt(m_gamma2, "M_Gamma_" + option_type2);

	to_txt(m_vega1, "M_Vega_" + option_type1);
	to_txt(m_vega2, "M_Vega_" + option_type2);

	// Localized Malliavin method
	cout << "Begin Localized Malliavin method" << endl;
	Malliavin_localized ML;

	vector<float> ml_delta1 = ML.delta(option_type1);
	vector<float> ml_delta2 = ML.delta(option_type2);

	vector<float> ml_gamma1 = ML.gamma(option_type1);
	vector<float> ml_gamma2 = ML.gamma(option_type2);

	vector<float> ml_vega1 = ML.vega(option_type1);
	vector<float> ml_vega2 = ML.vega(option_type2);

	to_txt(ml_delta1, "ML_Delta_" + option_type1);
	to_txt(ml_delta2, "ML_Delta_" + option_type2);

	to_txt(ml_gamma1, "ML_Gamma_" + option_type1);
	to_txt(ml_gamma2, "ML_Gamma_" + option_type2);

	to_txt(ml_vega1, "ML_Vega_" + option_type1);
	to_txt(ml_vega2, "ML_Vega_" + option_type2);


	// Finite difference method with PDE
	cout << "Begin PDE FD method:" << endl;
	PDE_FiniteDiff PDE_finite_diff;
	float pde_delta = PDE_finite_diff.delta(0., 100.);
	float pde_gamma = PDE_finite_diff.gamma(0., 100.);
	float pde_vega = PDE_vega(0., 100.);

	vector<float> PDE_eur_call_greeks = { pde_delta, pde_gamma, pde_vega};
	to_txt(PDE_eur_call_greeks, "PDE_eur_call_greeks");


	// Monte Carlo finite difference method
	cout << "Begin Monte Carlo FD method" << endl;
	MC_FiniteDiff MC_finite_diff;

	vector<float> FD_EURO_delta = MC_finite_diff.delta(option_type1);
	to_txt(FD_EURO_delta, "FD_Delta_" + option_type1);
	vector<float> FD_EURO_gamma = MC_finite_diff.gamma(option_type1);
	to_txt(FD_EURO_gamma, "FD_Gamma_" + option_type1);
	vector<float> FD_EURO_vega = MC_finite_diff.vega(option_type1);
	to_txt(FD_EURO_vega, "FD_Vega_" + option_type1);
	
	vector<float> FD_ASIA_delta = MC_finite_diff.delta(option_type2);
	to_txt(FD_ASIA_delta, "FD_Delta_" + option_type2);
	vector<float> FD_ASIA_gamma = MC_finite_diff.gamma(option_type2);
	to_txt(FD_ASIA_gamma, "FD_Gamma_" + option_type2);
	vector<float> FD_ASIA_vega = MC_finite_diff.vega(option_type2);
	to_txt(FD_ASIA_vega, "FD_Vega_" + option_type2);

	return 0;
}