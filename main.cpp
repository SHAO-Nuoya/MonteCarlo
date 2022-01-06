#include"Malliavin.h"

int main(void) {
	Malliavin malliavin;
	vector<float> delta1, delta2, gamma1, gamma2, vega1, vega2, rho1, rho2;
	string option_type1 = "EUR_CALL";
	string option_type2 = "ASIA_CALL";

	delta1 = malliavin.delta(option_type1, malliavin.N);
	delta2 = malliavin.delta(option_type2, malliavin.N);
	
	gamma1 = malliavin.gamma(option_type1, malliavin.N);
	gamma2 = malliavin.gamma(option_type2, malliavin.N);
	
	vega1 = malliavin.vega(option_type1, malliavin.N);
	vega2 = malliavin.vega(option_type2, malliavin.N);
	
	rho1 = malliavin.rho(option_type1, malliavin.N);
	rho2 = malliavin.rho(option_type2, malliavin.N);

	to_txt(delta1, "Delta_" + option_type1);
	to_txt(delta2, "Delta_" + option_type2);

	to_txt(gamma1, "Gamma_" + option_type1);
	to_txt(gamma2, "Gamma_" + option_type2);

	to_txt(vega1, "Vega_" + option_type1);
	to_txt(vega2, "Vega_" + option_type2);

	to_txt(rho1, "Rho_" + option_type1);
	to_txt(rho2, "Rho_" + option_type2);

	return 0;
}