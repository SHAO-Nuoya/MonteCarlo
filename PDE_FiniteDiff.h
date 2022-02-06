#pragma once
#include<string>
#include<vector>

using namespace std;
class PDE_FiniteDiff {
private:
	float S0; //current price of underlying
	float r; //risk free rate
	float sigma; //volatility
	float T; //maturity
	float K; //strike


public:
	int N; //time step number
	float dt = T / N; //time step
	int M;    //number of discret points in space
	float ubound;   //space upper bound; lower bound = -ubound
	float dx = 2 * ubound / M; //space interval

	PDE_FiniteDiff(float S0, float r, float sigma, float T, float K, int N, int M, float ubound);
	PDE_FiniteDiff();


	float payoff(float xm);	
	float getPrice(float t, float x);

	//vector<float> rho(float t, float x, float r, float dr);
	float delta(float t, float S);
	float gamma(float t, float S);
	//vector<float> vega(float t, float x, float sigma);
};


float PDE_vega(float t, float S);