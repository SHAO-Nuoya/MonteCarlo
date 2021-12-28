#include"Malliavin.h"

int main(void) {
	Malliavin malliavin;
	vector<float> delta1, delta2;
	string option_type1 = "EUR_CALL";
	string option_type2 = "ASIA_CALL";

	delta1 = malliavin.delta(option_type1, malliavin.N);
	delta2 = malliavin.delta(option_type2, malliavin.N);
	
	to_txt(delta1, "Delta" + option_type1);
	to_txt(delta2, "Delta" + option_type2);
	return 0;
}