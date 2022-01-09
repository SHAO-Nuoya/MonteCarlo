#include"FiniteDiff.h"
#include<iostream>
#include<math.h>
using namespace std;

FiniteDiff::FiniteDiff(float S0_, float r_, float sigma_, float T_, float K_, int N_, int M_, float ubound_):
	S0(S0_), r(r_), sigma(sigma_), T(T_), K(K_), N(N_), M(M_), ubound(ubound_) {};

FiniteDiff::FiniteDiff(): S0(100), r(0), sigma(0.2), T(1), K(100), N(1600), M(400), ubound(2) {};
	
float FiniteDiff::payoff(float xm){	
	return (S0*exp(xm) - K) * (S0*exp(xm) > K);
}	
	
float FiniteDiff::getPrice(float t, float S){
	
	
	float** uMat = new float*[M+1];
	
    for (int i = 0; i < M+1; i++)
        uMat[i] = new float[N+1];

	float p = pow(sigma,2)*dt/2./pow(dx,2)*(1-dx/2.);
	float q = pow(sigma,2)*dt/2./pow(dx,2)*(1+dx/2.);
	
	for (int i = 0; i < M+1; i++){
		cout << "payoff((-ubound+i*dx))=" << payoff((-ubound+i*dx)) << endl;
		float u = -ubound+i*dx;
		uMat[N][i] = payoff(u);
		
	}
	cout << "uMat[N][0]=" << uMat[N][0] << S0 << endl;
	for (int i = N-1; i>=0; i--){        //backward iteration
		uMat[i][0] = payoff(-ubound);    //Dirichlet left boundary condition
		uMat[i][M] = payoff(ubound);	//Dirichlet right boundary condition

		for (int j = 1; j < M; j++){
		//u[i-1,1:-1] = p*u[i,2:]+q*u[i,:-2] + (1.-p-q)*u[i,1:-1]
		uMat[i][j] = p * uMat[i-1][j+1] + q*uMat[i-1][j-1] + (1-p-q)*uMat[i-1][j];
		}
	}

	int m = floor(log(S/S0)/dx);
	int n = floor(t/dt);
	float u = uMat[n][m];
	
	for (int j = 0; j < M+1; j++)
        delete[] uMat[j];
    delete[] uMat;


	return u;
}



float FiniteDiff::delta(float t, float x, float dx) {
	
	
	return 0;
}

float FiniteDiff::gamma(float t, float x, float dx) {
	
	
	return 0;
}



