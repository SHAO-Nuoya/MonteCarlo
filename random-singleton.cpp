//
//  random-singleton.cpp
//  Practical_Class_M2MO
//
//  Created by Noufel frikha on 17/11/2020.
//  Copyright © 2020 Noufel frikha. All rights reserved.
//

#include "random-singleton.hpp"

// random-singleton.cpp (Singleton)
// Implementation de la classe Random / Implementation of the class Random

#include <cfloat> //DBL_EPSILON
#define M_PI 3.14159265358979323846
using namespace std;

inline static double sqr(double x) {return x*x;}

//Ces constantes sont requises par l'algorithme du generateur aleatoire
//These consts are required by the algorithm
const int Random::NTAB = 32;

const long Random::IM1 = 2147483563;
const long Random::IM2 = 2147483399;
const long Random::IMM1 = Random::IM1 - 1;
const double Random::AM = 1.0/Random::IM1;
const int Random::IA1 = 40014;
const int Random::IA2 = 40692;
const int Random::IQ1 = 53668;
const int Random::IQ2 = 52774;
const int Random::IR1 = 12211;
const int Random::IR2 = 3791;
const int Random::NDIV = 1 + Random::IMM1/Random::NTAB;
const double Random::EPS = DBL_EPSILON;
const double Random::RNMX = 1.0-Random::EPS;

long  Random::idum   = 0;
long  Random::idum2  = 123456789L;
long  Random::iy     = 0;
long* Random::iv     = 0;

//definition du singleton
Random Random::Singleton(0);

void Random::Randomize(long seed)
{
    idum = (seed <= 0) ? (seed == 0 ? 1 : -seed) : seed; //be sure to prevent idum=0
    
    idum2 = idum;
    if (idum2 < 0) idum2 = -idum2;
    
    long k = 0;
    for(int j = NTAB+7 ; j >= 0 ; j--)
    {
        k = idum/IQ1;
        idum = IA1*(idum - k*IQ1) - k*IR1;
        if (idum < 0)
            idum += IM1;
        
        if (j < NTAB)
            iv[j] = idum;
    }
    
    iy = iv[0];
}
//fin Randomize()

//Cette fonction renvoie un double pseudo-aleatoire uniformement dans ]0;1[
//Il s'agit de l'algorithme de L'Ecuyer avec melange de Bays-Durham
//This function returns a double, taken uniformly in ]0;1[
//It is the algorithm of L'Ecuyer with a Bays-Durham shuffle
double Random::theRandom(void)
{
    long k = idum/IQ1;
    idum = IA1*(idum - k*IQ1) - k*IR1;
    if (idum < 0)
        idum +=IM1;
    
    k = idum2/IQ2;
    idum2 = IA2*(idum2 -k*IQ2) - k*IR2;
    if (idum2 < 0)
        idum2 +=IM2;
    
    long j = iy/NDIV;
    iy = iv[j] - idum2;
    iv[j] = idum;
    if (iy < 1)
        iy += IMM1;
    
    double temp = AM*iy;
    if (temp >= RNMX)
        return RNMX;  //empeche de renvoyer 1 / prevents from returning 1
    else
        return temp;
}
//fin theRandom()

//Renvoie un double de la Gaussienne de moyenne et d'ecartype specifies
//Returns a double taken on a Gaussian with specified mean and standard deviation
double Random::Gaussian(double mean, double standardDeviation)
{
    const int NbTirages = 12; //augmenter pour une meilleure precision. 12 est bien.
    //increase for better precision. 12 works fine.
    double valeur = 0;
    for(int i=0 ; i < NbTirages ; ++i)
        valeur += Random::Uniform();
    
    //on recentre la somme / centering the sum
    valeur -= NbTirages/2;
    
    //on etale suivant l'ecartype / spread with standard deviation
    //le 12 n'a rien a voir avec NbTirages, mais explique pourquoi justement, on prend souvent
    //NbTirages = 12
    //the 12 is not related to NbTirages, but it explains why it is often chosen that NbTirages=12
    valeur *= (NbTirages == 12) ? standardDeviation
    : sqrt(12/static_cast<double>(NbTirages))*standardDeviation;
    
    //on centre sur la moyenne / debias
    valeur += mean;
    
    return valeur;
}

//fin Gaussian()

double Random::normalCDF(double x) // Phi(-∞, x) aka N(x)
{
    return std::erfc(-x/sqrt(2))/2;
}
double Random::Payoff_Call(double S, double K)
{
        return (S >= K) ? S - K : 0.0;
}
double Random::Call_price_BS(double S, double r, double T, double K, double sigma)
{
    double d_1 = 1 / (sigma * sqrt(T)) * ((log(S) - log(K) + (r + pow(sigma, 2)/2) * T));
    return S * normalCDF(d_1) - K * exp(- r * T) * normalCDF(d_1 - sigma * sqrt(T));
}
int Random::Binomial(double prob)
{
    int result = 0;
    double unif = Random::Uniform();
    if( unif < prob)
    {
        result = 1;
    }
    return result;
}

int Random::Bernoulli(int N, double prob)
{
    int result = 0;
    for(int n=0; n<N; n++)
    {
        result += Random::Binomial(prob);
    }
    return result;
}

double Random::Exponentielle(double lambda)
{
    double result;
    double unif = Random::Uniform();
    result = (-1/lambda) * log(unif);
    return result;
}

double Random::Cauchy(double x0, double lambda)
{
    double result;
    double unif = Random::Uniform();
    result = lambda * tan(M_PI*(unif-0.5)) + x0;
    return result;
}

double * Random::BoxMuller(double m, double sigma)
{
    double * result = new double [2];
    double u = Random::Uniform();
    double expo = Random::Exponentielle(0.5);
    
    result[0] = m + sigma * sqrt(expo) * cos(2 * M_PI * u);
    
    result[1] = m + sigma * sqrt(expo) * sin(2 * M_PI * u);
    
    return result;
}
double Random::Gamma(double a)
{
    // Méthode d'acceptation - rejet
    double result;
    double unif1;
    double unif2;
    double Y;
    double q_Y;
    double seuil  = exp(1)/(a + exp(1));
    
    int arret = 0;
    
    while(arret == 0)
    {
        unif1 = Random::Uniform();
        unif2 = Random::Uniform();
        
        if(unif2 < seuil)
            Y = pow(unif2/seuil,1/a);
        else
            Y = -log((1-unif2)*(1/(seuil*exp(1))));
        if(Y< 1)
            q_Y = exp(-Y);
        else
            q_Y = pow(Y, a-1);
        
        if(unif1 < q_Y)
            arret = 1;
    }
    result = Y;
    return result;
}
double * Random::Inverse_Gaussian(double lambda, double * mu, int length_mu)
{
    double z= Random::Gaussian(0,1);
    double u=  Random::Uniform(0,1);
    double y = z*z;
    double * x = new double [length_mu];
    for(int i=0; i<length_mu; ++i){
        x[i]=mu[i] + (0.5*mu[i]/lambda)*(y*mu[i] +sqrt(4*lambda*mu[i]*y+mu[i]*mu[i]*y*y));
        if (u > mu[i]/(mu[i]+x[i])) x[i]=mu[i]*mu[i]/x[i];
    }
    return x;
}

//fin Inverse_Gaussian()
double * Random::Normal_Inverse_Gaussian(double alpha, double beta, double delta, double mu, double * shift, int length_shift)
{
    double z = Random::Gaussian(0,1);
    double * gamma= new double[length_shift];
    double * mu_IG= new double[length_shift];
    double * res= new double[length_shift];
    //Convention: le shift se fait en soustrayant!
    for(int i=0; i< length_shift; ++i){
        gamma[i]=sqrt(alpha*alpha-(beta-shift[i])*(beta-shift[i]));
        mu_IG[i]=delta/gamma[i];
    }
    double * y =Random::Inverse_Gaussian(delta*delta,mu_IG, length_shift);
    for(int i=0; i< length_shift; ++i) res[i]=mu + (beta-shift[i])*y[i] + sqrt(y[i])*z;
    
    delete gamma, mu_IG;
    return res;
}

//fin Normal_Inverse_Gaussian()

//fin random-singleton.cpp
