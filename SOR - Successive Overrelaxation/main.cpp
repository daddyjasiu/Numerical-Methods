//Jan Skwarczek

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<double> SOR(vector<vector<double>> wstegi, int N, int M, const vector<double> &y, vector<double> &x, int L, double omega ) {// Jacobi
    
    double s;
    int M_length = M/2;

    for(int i=0; i < L; i++) {
        for (int j = 0; j < N; j++) {

            s = y[j];

            for (int k = 0; k < M_length; k++) {
                if(j + M_length - k < N) {
                    s -= wstegi[k][j] * x[j + M_length - k];
                }
            }

            for (int k = M_length+1; k < M; k++) {
                if(j + M_length - k >= 0) {
                    s -= wstegi[k][j + M_length - k] * x[j + M_length - k];
                }
            }

            x[j] = (1-omega) * x[j] + omega * s / wstegi[M_length][j];

        }
    }
    return x;
}

int main() {

    int N;
    int M;
    double omega;
    int L;

    cin >> N >> M;

    int M_length = M / 2;

    vector<vector<double>> wstegi;

    vector<double> inputV;

    double input;
    
    vector<double> v_Y;
    vector<double> v_X;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N-M_length; ++j) {
            cin >> input;
            inputV.push_back(input);
        }
        wstegi.push_back(inputV);
        inputV.clear();

        if (i < (M/2)){
            M_length--;
        }

        else if (i >= (M/2)){
            M_length++;
        }

    }

    for (int i = 0; i < N; ++i) {
        cin >> input;
        v_Y.emplace_back(input);
        
    }
    for (int i = 0; i < N; ++i) {
        cin >> input;
        v_X.emplace_back(input);
    }

    cin >> omega >> L;

    vector<double> result;

    cout << scientific << setprecision(16);
    result = SOR(wstegi, N, M, v_Y, v_X, L, omega);

    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << " ";
    }

    return 0;
}

/*

7
5
1 2 1 2 1
2 -1 3 1 3 -1
5 6 7 8 9 10 11
2 -1 3 1 3 -1
1 2 1 2 1
8 9 11 16 15 14 11
2 3 2 3 2 3 2
1.5
1

 -1.0000000000000000e+000 2.5000000000000000e-001 -7.3214285714285721e-001 3.1808035714285765e-001 -2.6432291666666696e-001 9.2352120535714288e-001 6.6197874391233791e-001

 */
