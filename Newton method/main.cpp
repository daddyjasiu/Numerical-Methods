//Jan Skwarczek

#include <stdio.h>
#include <cmath>
#include <iostream>

#define eps 1e-14

void printVector(const double* x, unsigned N){
    for(unsigned i=0;i<N;++i)
        printf("%17.17f ",x[i]);
    printf("\n");
}

typedef void (*FuncPointer)(const double* x, double* y, double* Df);

double determinant(double d1, double d2, double d3, double d4){
    return d1*d2 - d3*d4;
}

double matrixMult(double d1, double d2, double d3, double d4){
    return d1*d2 - d3*d4;
}

int findCurve (FuncPointer f, double* x, unsigned k, double h){

    int Z = 1000;
    double y[2];
    double Df[6];

    for(int i=1; i <= k; i++){

        double X[3] = {x[0],x[1],x[2] + i*h};

        f(X,y,Df);

        bool rootFound = false;

        while(Z--){

            if(determinant(Df[0],Df[4], Df[1],Df[3]) != 0) {

                X[0] -= (matrixMult(Df[4], y[0], Df[1], y[1])) / determinant(Df[0], Df[4], Df[1], Df[3]);
                X[1] -= (matrixMult(Df[0], y[1], Df[3], y[0])) / determinant(Df[0], Df[4], Df[1], Df[3]);

                f(X, y, Df);

                if (std::max(fabs(y[0]), fabs(y[1])) <= eps) {
                    rootFound = true;
                    printVector(X, (unsigned) 3);
                    break;
                }
            }
            else{
                return i;
            }
        }

        if(!rootFound){
            return i;
        }
        
        Z = 1000;
    }
    return 0;
}

int findSurface(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2){

    int Z = 1000;
    double y[1];
    double Df[3];

    for (int i1 = 1; i1 <= k1; i1++) {

        for(int i2 = 1; i2 <= k2; i2++){

            double X[3] = {x[0], x[1] + i1*h1, x[2] + i2*h2};

            f(X,y,Df);

            bool rootFound = false;

            while(Z--){

                if(determinant(Df[0],1, 0,0) != 0) {

                    X[0] -= (y[0] / determinant(Df[0], 1, 0, 0));

                    f(X, y, Df);

                    if (fabs(y[0]) <= eps) {
                        rootFound = true;
                        printVector(X, (unsigned) 3);
                        break;
                    }
                }
                else{
                    return i1*k1+i2;
                }
            }

            if(!rootFound){
                return i1*k1+i2;
            }

            Z = 1000;
        }
        std::cout << std::endl;
    }
    return 0;
}

int findFixedPoints(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2){

    int Z = 1000;
    double Y[2];
    double Df[8];

    for(int i=1; i <= k1; i++){
        for(int j=1; j <= k2; j++){

            double X[4] = {x[0], x[1], x[2]+i*h1, x[3]+j*h2};

            f(X, Y, Df);

            bool rootFound = false;

            while(Z--){

                Df[0] = Df[0] - 1;
                Df[5] = Df[5] - 1;

                if(determinant(Df[0], Df[5], Df[1], Df[4]) != 0) {

                    X[0] -= (matrixMult(Df[5], Y[0] - X[0], Df[1], Y[1] - X[1])) /
                            determinant(Df[0], Df[5], Df[1], Df[4]);;
                    X[1] -= (matrixMult(Df[0], Y[1] - X[1], Df[4], Y[0] - X[0])) /
                            determinant(Df[0], Df[5], Df[1], Df[4]);;

                    f(X, Y, Df);

                    if (std::max(fabs(Y[0] - X[0]), fabs(Y[1] - X[1])) <= eps) {
                        rootFound = true;
                        printVector(X, (unsigned) 4);
                        break;
                    }
                }
                else{
                    return i*k1 + j;
                }
            }

            if(!rootFound){
                return i*k1 + j;
            }
            Z = 1000;
        }
        std::cout << std::endl;
    }
    return 0;
}
