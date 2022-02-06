#include"PDE_FiniteDiff.h"
#include<iostream>
#include<math.h>
#include<vector>
using namespace std;

PDE_FiniteDiff::PDE_FiniteDiff(float S0_, float r_, float sigma_, float T_, float K_, int N_, int M_, float ubound_):
	S0(S0_), r(r_), sigma(sigma_), T(T_), K(K_), N(N_), M(M_), ubound(ubound_) {};

PDE_FiniteDiff::PDE_FiniteDiff(): S0(100), r(0), sigma(0.2), T(1), K(100), N(10000), M(100), ubound(2) {};
	
float PDE_FiniteDiff::payoff(float xm){	
	return (S0*exp(xm) - K) * (S0*exp(xm) > K);
}	


// only for European option
float PDE_FiniteDiff::getPrice(float t, float S){
	
	std::vector<std::vector<float> > uMat(N + 1, std::vector<float>(M + 1));

	float p = pow(sigma,2)*dt/2./pow(dx,2)*(1-dx/2.);
	float q = pow(sigma,2)*dt/2./pow(dx,2)*(1+dx/2.);
	
	for (int i =0; i < M+1; i++){
		float x = -ubound+i*dx;
		uMat[N][i] = payoff(x);
	}

	for (int i = N-1; i>=0; i--){        //backward iteration
		uMat[i][0] = payoff(-ubound);    //Dirichlet left boundary condition
		uMat[i][M] = payoff(ubound);	//Dirichlet right boundary condition
	
		for (int j = 1; j < M; j++){
			uMat[i][j] = p * uMat[i+1][j+1] + q*uMat[i+1][j-1] + (1-p-q)*uMat[i+1][j];
		}
	}

	int m = floor((log(S/S0)+ubound)/dx);
	int n = floor(t/dt);
	float u = uMat[n][m];
	return u*exp(-r*T);
}



float PDE_FiniteDiff::delta(float t, float S) {	
	float x = log(S/S0);
	float S_1 = S0*exp(x-dx);
	float S_2 = S0*exp(x+dx);

	float delta=(getPrice(t,S_2) - getPrice(t,S_1))/(S_2 - S_1);
	
	return delta;
}

float PDE_FiniteDiff::gamma(float t, float S) {
	float x = log(S/S0);
	float S_1 = S0*exp(x-2*dx);
	float S_1_=S0*exp(x-dx);
	float S_2 = S0*exp(x+2*dx);
	float S_2_=S0*exp(x+dx);
	float delta_2=(getPrice(t,S_2) - getPrice(t,S))/(S_2 - S);
	float delta_1=(getPrice(t,S) - getPrice(t,S_1))/(S - S_1);

	float gamma = (delta_2 - delta_1)/(S_2_ - S_1_);
	
	return gamma;
}



