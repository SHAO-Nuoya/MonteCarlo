#include"Malliavin.h"
#include"PDE_FiniteDiff.h"
#include"MC_FiniteDiff.h"
#include"utility.h"

#include <iostream>
using namespace std;


int main(void) {

	vector<float> delta1, delta2, gamma1, gamma2, vega1, vega2, rho1, rho2;
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


	/*

	// Maliavin method
	Malliavin malliavin;

	delta1 = malliavin.delta(option_type1, malliavin.N);
	delta2 = malliavin.delta(option_type2, malliavin.N);
	
	gamma1 = malliavin.gamma(option_type1, malliavin.N);
	gamma2 = malliavin.gamma(option_type2, malliavin.N);
	
	vega1 = malliavin.vega(option_type1, malliavin.N);
	vega2 = malliavin.vega(option_type2, malliavin.N);

	to_txt(delta1, "M_Delta_" + option_type1);
	to_txt(delta2, "M_Delta_" + option_type2);

	to_txt(gamma1, "M_Gamma_" + option_type1);
	to_txt(gamma2, "M_Gamma_" + option_type2);

	to_txt(vega1, "M_Vega_" + option_type1);
	to_txt(vega2, "M_Vega_" + option_type2);
	
	

	// Finite difference method with PDE

	PDE_FiniteDiff PDE_finite_diff;
	float pde_delta = PDE_finite_diff.delta(0., 100.);
	float pde_gamma = PDE_finite_diff.gamma(0., 100.);
	float pde_vega = PDE_vega(0., 100.);

	vector<float> PDE_eur_call_greeks = { pde_delta, pde_gamma, pde_vega};
	to_txt(PDE_eur_call_greeks, "PDE_eur_call_greeks");

	// Finite difference method with Monte Carlo


	
	to_txt(delta1, "FD_Delta_" + option_type1);
	to_txt(delta2, "FD_Delta_" + option_type2);

	to_txt(gamma1, "FD_Gamma_" + option_type1);
	to_txt(gamma2, "FD_Gamma_" + option_type2);

	to_txt(vega1, "FD_Vega_" + option_type1);
	to_txt(vega2, "FD_Vega_" + option_type2);
	*/


	// Monte Carlo finite difference method
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

	/*
	// Finite difference method in PDE: European option; Explicit scheme

	PDE_FiniteDiff PDE_finite_diff;
	cout << "N = " << PDE_finite_diff.N << endl;
	cout << "M = " << PDE_finite_diff.M << endl;
	cout << "price = " << PDE_finite_diff.getPrice(0.,100.) << endl;
	cout << "delta = "<< PDE_finite_diff.delta(0.,100.) << endl;
	cout << "gamma = " << PDE_finite_diff.gamma(0.,100.) << endl;
	*/

	

	return 0;
}