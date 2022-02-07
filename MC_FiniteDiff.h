#pragma once
#include<string>
#include<vector>

using namespace std;
class MC_FiniteDiff {
private:
	float S0; //current price of underlying
	float r; //risk free rate
	float sigma; //volatility
	float T; //maturity
	float K; //strike

public:
	int I; //time step number
	int N; //simulation time
	float h = T / I; //time step

	MC_FiniteDiff(float S0, float r, float sigma, float T, float K, int I, int N);
	MC_FiniteDiff();
	
	//simulation
    vector<float> price(string option_type);
	vector<float> delta(string option_type);
	vector<float> gamma(string option_type);
	vector<float> vega(string option_type);
};

