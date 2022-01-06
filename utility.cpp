#include"utility.h"

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

//operations for vector
vector<float> multiply(const vector<float> v, float d) {
    vector<float> res;
    for (int i = 0; i < v.size(); i++) {
        res.push_back(v[i] * d);
    }
    return res;
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