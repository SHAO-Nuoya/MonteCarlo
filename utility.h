#pragma once
#include <math.h>
#include <fstream>
#include <numeric>
#include <vector>
#include <iomanip>
using namespace std;

//statistics
float Sum(vector<float> vec);
float Mean(vector<float> vec);
float Var(vector<float> vec);

//operations for vector
vector<float> multiply(vector<float> v, float d);

//output
void to_txt(vector<float> array, string filename);