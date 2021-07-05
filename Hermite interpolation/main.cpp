//Jan Skwarczek

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

long long factorial(long long n)
{
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

void polynomialEvaluation(vector<long double>& T, vector<long double>& W, vector<pair<long double,long double>> table){

    vector<long double> result;

    for (int i = 0; i < W.size(); ++i) {
        cout << W[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < T.size(); ++i) {
        long double sum = W[table.size()-1];
        for (int j = table.size() - 2; j >= 0; --j) {
            sum = W[j] + (sum * (T[i] - table[j].first));
        }
        result.emplace_back(sum);
    }
    cout << endl;
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << " ";
    }

}

vector<long double> hermite(vector<long double>& X, vector<long double>& Y, vector<long double>& T, vector<pair<long double,long double>>& fX, vector<pair<long double,long double>>& fX_deriv, vector<pair<long double,long double>>& table){

    vector<long double> W;
    int derivCounter = 0;
    W.emplace_back(fX[0].second);

    for (int i = 1; i < X.size(); i++) {
        for (int j = 0; j < Y.size()-i; j++) {
            if(table[j].first != table[j+i].first){
                table[j].second = (table[j+1].second - table[j].second) / (table[j+i].first - table[j].first);
            }
            else{
                int id = 0;
                for (int k = 0; k < fX_deriv.size() && id != i; ++k) {
                    if(fX_deriv[k].first == table[j].first){
                        derivCounter = k;
                        id++;
                    }
                }
                table[j].second = fX_deriv[derivCounter].second / factorial(i);
            }

        }
        derivCounter = i-1;
        W.emplace_back(table[0].second);
    }

    return W;
}

int main() {

    int M;
    int N;
    vector<long double> X;
    vector<long double> Y;
    vector<pair<long double,long double>> fX;
    vector<pair<long double,long double>> fX_deriv;
    vector<pair<long double,long double>> table;
    vector<long double> T;

    vector<long double> result;

    cin >> M >> N;

    for (int i = 0; i < M; ++i) {
        long double input;
        cin >> input;

        X.emplace_back(input);
    }
    for (int i = 0; i < M; ++i) {
        long double input;
        cin >> input;

        Y.emplace_back(input);
    }
    for (int i = 0; i < N; ++i) {
        long double input;
        cin >> input;
        T.emplace_back(input);
    }

    for (int i = 0; i < M; ++i) {
        if(X[i] != X[i-1])
            fX.emplace_back(X[i], Y[i]);
    }

    for (int i = 1; i < M; ++i) {
        if(X[i] == X[i-1])
        fX_deriv.emplace_back(X[i], Y[i]);
    }

    for (int i = 0; i < M; ++i) {
        table.emplace_back(X[i], Y[i]);
    }
    for (int i = 1; i < table.size(); ++i) {
        if(table[i].first == table[i-1].first)
            table[i].second = table[i-1].second;
    }

    cout << setprecision(17) << fixed;

    result = hermite(X, Y, T, fX, fX_deriv, table);
    polynomialEvaluation(T, result, table);
}
