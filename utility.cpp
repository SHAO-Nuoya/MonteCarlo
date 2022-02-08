#include"utility.h"
#include <chrono>
#include <random>
using namespace std;

//statistics
float Sum(const vector<float> vec) { return accumulate(begin(vec), end(vec), 0.0); };

float Mean(const vector<float> vec) { return Sum(vec) / vec.size(); };

float Var(const vector<float> vec) {
    float mean = Mean(vec);
    float var = 0;
    int N = vec.size();
    for (int i = 0; i < N; ++i) {
        var += pow(vec[i] - mean, 2);
    }
    return var / N;
}

double normalCDF(double value) { return 0.5 * erfc(-value * sqrt(0.5)); };
double normalPDF(double value) { return exp(-pow(value, 2) / 2) / sqrt(2 * PI); };

//operations for vector
vector<float> multiply(const vector<float> v, float d) {
    vector<float> res;
    for (int i = 0; i < v.size(); i++) {
        res.push_back(v[i] * d);
    }
    return res;
};

vector<float> vector_multiply(vector<float> v1, vector<float> v2) {
	vector<float> res;
	for (int i = 0; i < v1.size(); i++) {
		res.push_back(v1[i] * v2[i]);
	}
	return res;
};

float Integral(vector<float> v, float step) {
	return Sum(v) * step;
};


float generate_N01() {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine e(seed);
	normal_distribution<float> dis(0, 1);
	float N01 = dis(e);
	return N01;
}

vector<float> generate_St(float S0, float r, float sigma, float I, float h) {
	vector<float> S;
	S.push_back(S0);
	float t, s, s_pre, dw;

	for (int i = 1; i < I; i++) {
		t = i * h;
		s_pre = S.back();
		dw = sqrt(h) * generate_N01();
		s = s_pre + r * s_pre * h + sigma * s_pre * dw + pow(sigma, 2) * s_pre * (pow(dw, 2) - h) / 2;
		S.push_back(s);
	}
	return S;
}

//payoff function
float payoff(string option_type, vector<float> S, float K) {
	float pay_off = 0;
	if (option_type == "EUR_CALL") {
		pay_off = max(S.back() - K, float(0));
	}
	else if (option_type == "ASIA_CALL") {
		pay_off = max(Mean(S) - K, float(0));
	}
	return pay_off;
};

//analytical Greeks
//no analytical solution for arithmetic asian option
float greeks(string greek_name,float* par, string option_type = "EUR_CALL") {
	float greek = 0;
	float S0 = par[0];
	float K = par[1];
	float r = par[2];
	float sigma = par[3];
	float T = par[4];
	float d1;

	if (option_type == "EUR_CALL") {
		d1 = (log(S0 / K) + (r + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));
		if (greek_name == "delta") {
			greek = normalCDF(d1);
		}
		else if (greek_name == "gamma") {
			greek = normalPDF(d1)/(S0*sigma*sqrt(T));
		}
		else if (greek_name == "vega") {
			greek = S0 * sqrt(T) * normalPDF(d1);
		}
	}
	else if (option_type == "") {
		if (greek_name == "delta") {
			greek = 0;
		}
		else if (greek_name == "gamma") {
			greek = 0;
		}
		else if (greek_name == "vega") {
			greek = 0;
		}
	}
	return greek;
};

//output
void to_txt(const vector<float> array, string filename) {
    ofstream outfile;
    outfile.open("Result/" + filename + ".txt");
    for (int i = 0; i < array.size(); i++) {
        outfile << array[i] << " ";
        if (i % 20 == 0 && i > 0) {
            outfile << "\n";
        }
    }
    outfile.close();
}