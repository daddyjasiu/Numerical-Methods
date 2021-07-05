//Jan Skwarczek

#include <cmath>

double sgn(double x, double eps){
    if(x > eps) return 1;
    if(x < -eps) return -1;
    return eps;
}

double findZero(
        double (*f)(double),  // funkcja ktĂłrej zera szukamy w [a, b]
        double a,             // lewy koniec przedziaĹu
        double b,             // prawy koniec przedziaĹu
        int M,                // maksymalna dozwolona liczba wywoĹaĹ funkcji f
        double eps,           // spodziewana dokĹadnoĹÄ zera
        double delta          // wystarczajÄcy bĹÄd bezwzglÄdny wyniku
){

    double e = b-a;    //Inicjalizacja zmiennych potrzebnych do przebiegu algorytmu
    double c;
    double w;
    double s;

        double fa = f(a);  //Obliczenie wartosci funkcji
        if(fa == 0) return a;

        double fb = f(b);
        if(fb == 0) return b;

        if (f(a) * f(b) <= 0) {

            while (M-- && (b - a) > 0.4) {  //Petla glowna algorytmu bisekcji

                e = e / 2.0;
                c = a + e;
                w = f(c);

                if (fabs(e) < delta || fabs(w) < eps)
                    break;

                if (sgn(w, eps) != sgn(fa, eps)) {
                    b = c;
                    fb = w;
                } else {
                    a = c;
                    fa = w;
                }

            }

            while (M--) {  //Petla glowna algorytmu siecznych

                s = (b - a) / (fb - fa);
                b = a;
                fb = fa;
                a = a - fa * s;
                fa = f(a);

                if (fabs(fa) < eps || fabs(b - a) < delta)
                    break;
            }

            return a;

        } else if (f(a) * f(b) > 0) {

            while (M--) {  //Petla glowna algorytmu siecznych

                s = (b - a) / (fb - fa);
                b = a;
                fb = fa;
                a = a - fa * s;
                fa = f(a);

                if (fabs(fa) < eps || fabs(b - a) < delta)
                    break;
            }

            while (M-- && (b - a) > 0.4) {  //Petla glowna algorytmu bisekcji

                e = e / 2.0;
                c = a + e;
                w = f(c);

                if (fabs(e) < delta || fabs(w) < eps)
                    break;

                if (sgn(w, eps) != sgn(fa, eps)) {
                    b = c;
                    fb = w;
                } else {
                    a = c;
                    fa = w;
                }

            }

            while (M--) {  //Petla glowna algorytmu siecznych

                s = (b - a) / (fb - fa);
                b = a;
                fb = fa;
                a = a - fa * s;
                fa = f(a);

                if (fabs(fa) < eps || fabs(b - a) < delta)
                    break;
            }

            return a;

        } else {
            return a;
        }

}
