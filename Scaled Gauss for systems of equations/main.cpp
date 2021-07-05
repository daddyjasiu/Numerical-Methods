//Jan Skwarczek

#include <iomanip>
#include <cmath>
#include <algorithm>
#include "vectalg.h"

using namespace std;

void find_scale(Vector &s, Matrix& A){

    int max;

    for (int i = 0; i < A.size(); ++i) {
        max = fabs(A(i,0));
        for (int j = 0; j < A.size(); ++j) {
            if(max < fabs(A(i,j)))
                max = fabs(A(i,j));
        }
        s[i] = max;
    }
}

inline int row_scale(const Matrix& mA, const Vector& s, const std::vector<int>& p, const int& j) {

    int N = mA.size();
    int row = j;
    double val = 0;
    double temp;

    for (int i = j; i < N; ++i) {
        temp = fabs(mA(p[i], j) / s[p[i]]);
        if (temp > val) {
            row = i;
            val = temp;
        }
    }

    return row;
}

Vector solveEquations(
    const Matrix &A, // Macierz
    const Vector &b, // Wektor
    double eps       // dopuszczalny bĹÄd
)
{
    int n = A.size();
    Matrix mA(A);
    Vector vB(b);
    Vector x(n);

    vector<int> p(n);
    Vector s(n);

    find_scale(s, mA);
    for (int i = 0; i < p.size(); ++i) {                       //obliczanie skali wierszy
        p[i] = i;
    }

    int j;
    double z;

    for (int k = 0; k < n-1; ++k) {                    //skalowany wybor wierszy glownych
        j = row_scale(mA, s, p, k);
        swap(p[k], p[j]);

        for (int i = k+1; i < n; ++i) {                //algorytm inspirowany Kincaidem
            if(mA(p[k], k) == 0)
                swap(p[k], p[j]);
            z = mA(p[i], k) / mA(p[k], k);
            for (int val = k; val < n; ++val) {
                mA(p[i], val) -= mA(p[k], val) * z;
            }

            vB[p[i]] -= vB[p[k]] * z;
        }
    }

    double temp;
    for (int i = n - 1; i >= 0; --i) {
        temp = 0;
        for (int j = i + 1; j < n; ++j) {
            temp += mA(p[i], j) * x[j];
        }

        x[i] = (vB[p[i]] - temp) / mA(p[i], i);

    }

    Vector res = residual_vector(A, b, x);
    if (res.max_norm() >= eps) {                        //iteracyjne poprawianie wyniku
        Vector itr_popr = solveEquations(A, res, eps);

        for (int i = 0; i < x.size(); ++i) {
            x[i] = x[i] + itr_popr[i];
        }
    }

    return x;

}
