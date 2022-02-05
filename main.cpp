//#include"Malliavin.h"
//#include"Malliavin.cpp"
#include"PDE_FiniteDiff.h"
#include"PDE_FiniteDiff.cpp"
//#include"utility.h"
//#include"utility.cpp"
#include <iostream>
#include <stdio.h>
using namespace std;

int main(void) {

	/*
	vector<float> delta1, delta2, gamma1, gamma2, vega1, vega2, rho1, rho2;
	string option_type1 = "EUR_CALL";
	string option_type2 = "ASIA_CALL";
	*/

	/*
	// Maliavin method
	Malliavin malliavin;

	delta1 = malliavin.delta(option_type1, malliavin.N);
	delta2 = malliavin.delta(option_type2, malliavin.N);
	
	gamma1 = malliavin.gamma(option_type1, malliavin.N);
	gamma2 = malliavin.gamma(option_type2, malliavin.N);
	
	vega1 = malliavin.vega(option_type1, malliavin.N);
	vega2 = malliavin.vega(option_type2, malliavin.N);
	
	rho1 = malliavin.rho(option_type1, malliavin.N);
	rho2 = malliavin.rho(option_type2, malliavin.N);

	to_txt(delta1, "M_Delta_" + option_type1);
	to_txt(delta2, "M_Delta_" + option_type2);

	to_txt(gamma1, "M_Gamma_" + option_type1);
	to_txt(gamma2, "M_Gamma_" + option_type2);

	to_txt(vega1, "M_Vega_" + option_type1);
	to_txt(vega2, "M_Vega_" + option_type2);

	to_txt(rho1, "M_Rho_" + option_type1);
	to_txt(rho2, "M_Rho_" + option_type2);
	*/

	// Finite difference method in PDE

	PDE_FiniteDiff PDE_finite_diff;
	cout << "N = " << PDE_finite_diff.N << endl;
	cout << "M = " << PDE_finite_diff.M << endl;
	cout << "price = " << PDE_finite_diff.getPrice(0.,100.) << endl;
	cout << "delta = "<< PDE_finite_diff.delta(0.,100.) << endl;
	cout << "gamma = " << PDE_finite_diff.gamma(0.,100.) << endl;


	/*
	to_txt(delta1, "FD_Delta_" + option_type1);
	to_txt(delta2, "FD_Delta_" + option_type2);

	to_txt(gamma1, "FD_Gamma_" + option_type1);
	to_txt(gamma2, "FD_Gamma_" + option_type2);

	to_txt(vega1, "FD_Vega_" + option_type1);
	to_txt(vega2, "FD_Vega_" + option_type2);

	to_txt(rho1, "FD_Rho_" + option_type1);
	to_txt(rho2, "FD_Rho_" + option_type2);
	*/
	return 0;
}