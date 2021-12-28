#include"Malliavin.h"

int main(void) {
	Malliavin malliavin;
	vector<float> delta1, delta2;
	vector<float> ns;
	string option_type1 = "EUR_CALL";
	string option_type2 = "ASIA_CALL";
	for (int n = 100; n < malliavin.N; n += 100) {
		delta1.push_back(malliavin.delta(option_type1, n));
		delta2.push_back(malliavin.delta(option_type2, n));
		ns.push_back(n);
	}
	to_txt(ns, "ns");
	to_txt(delta1, "Delta" + option_type1);
	to_txt(delta2, "Delta" + option_type2);
	return 0;
}