#include"utility.h"

float Sum(vector<float> vec) { return accumulate(begin(vec), end(vec), 0.0); };

float Mean(vector<float> vec) { return Sum(vec) / vec.size(); };

float Var(vector<float> vec) {
    float mean = Mean(vec);
    float var = 0;
    int N = vec.size();
    for (int i = 0; i < N; ++i) {
        var += pow(vec[i] - mean, 2);
    }
    return var / N;
}

//output
void to_txt(vector<float> array, string filename) {
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