#pragma once
#include<string>
#include<vector>

using namespace std;
class FiniteDiff {
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

	FiniteDiff(float S0, float r, float sigma, float T, float K, int I, int N);
	FiniteDiff();

	//simulation
	vector<float> rho(string option_type, int n);
	vector<float> delta(string option_type, int n);
	vector<float> gamma(string option_type, int n);
	vector<float> vega(string option_type, int n);
};

