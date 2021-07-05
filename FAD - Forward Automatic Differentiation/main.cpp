//Jan Skwarczek

#include <iostream>
#include <cmath>
#include <iomanip>
#include "funkcja.h"

using namespace std;

struct Jet{ //glowna klasa jeta

    const static int size = 6; //stala wartosc naszej tablicy gdyz obliczamy f, fx, fy, fxx, fxy, fyy.
    double values[size]{};

    Jet(){ //zerowanie tablicy wartosci
        for(double & value : values){
            value = 0.0;
        }
    }

    friend Jet sin(Jet right) { //funkcja obliczajaca sinusa

        Jet jet(right);
        double cosine = cos(jet.values[0]);
        double sine = sin(jet.values[0]);

        right.values[0] = sine;
        right.values[1] = jet.values[1] * cosine;
        right.values[2] = jet.values[2] * cosine;
        right.values[3] = jet.values[3] * cosine - pow(jet.values[1], 2) * sine;
        right.values[4] = jet.values[4] * cosine - jet.values[2] * jet.values[1] * sine;
        right.values[5] = jet.values[5] * cosine - pow(jet.values[2], 2) * sine;

        return right;
    }

    friend Jet cos(Jet right) { //funkcja obliczajaca cosinusa

        Jet jet(right);
        double sine = sin(jet.values[0]);
        double cosine = cos(jet.values[0]);

        right.values[0] = cosine;
        right.values[1] = jet.values[1] * (-sine);
        right.values[2] = jet.values[2] * (-sine);
        right.values[3] = pow(jet.values[1], 2) * (-cosine) - jet.values[3] * sine;
        right.values[4] = jet.values[2] * jet.values[1] * (-cosine) - jet.values[4] * sine;
        right.values[5] = pow(jet.values[2], 2) * (-cosine) - jet.values[5] * sine;

        return right;
    }

    friend Jet exp(Jet right) { //funkcja obliczajaca exp

        Jet jet(right);
        double e = exp(jet.values[0]);

        right.values[0] = e;
        right.values[1] = e * jet.values[1];
        right.values[2] = e * jet.values[2];
        right.values[3] = e * (pow(jet.values[1], 2) + jet.values[3]);
        right.values[4] = e * (jet.values[2] * jet.values[1] + jet.values[4]);
        right.values[5] = e * (pow(jet.values[2], 2) + jet.values[5]);

        return right;
    }

    Jet operator +=(Jet right){ //przeladowanie znaku += w dzialaniu na jetach

        for(int i=0; i<size; i++){
            values[i] += right.values[i];
        }

        return *this;
    }

    Jet operator +=(double right){ //przeladowanie znaku += w dzialaniu na jet + stala

        values[0] += right;

        return *this;
    }

    Jet operator -=(Jet right){ //przeladowanie znaku -= w dzialaniu na jetach

        for(int i=0; i<size; i++){
            values[i] -= right.values[i];
        }

        return *this;
    }

    Jet operator -=(double right){ //przeladowanie znaku -= w dzialaniu jet - stala

        values[0] -= right;

        return *this;
    }

    Jet operator *=(Jet right){ //przeladowanie znaku *= w dzialaniu na jetach

        const Jet jet(*this);
        values[0] = jet.values[0] * right.values[0];
        values[1] = jet.values[1] * right.values[0] + jet.values[0] * right.values[1];
        values[2] = jet.values[2] * right.values[0] + jet.values[0] * right.values[2];
        values[3] = 2 * jet.values[1] * right.values[1] + jet.values[3] * right.values[0] + jet.values[0] * right.values[3];
        values[4] = jet.values[1] * right.values[2] + jet.values[2] * right.values[1] + jet.values[4] * right.values[0] + jet.values[0] * right.values[4];
        values[5] = 2 * jet.values[2] * right.values[2] + jet.values[5] * right.values[0] + jet.values[0] * right.values[5];
        return *this;
    }

    Jet operator *=(double right){ //przeladowanie znaku *= w dzialaniu jet * const

        for(double & value : values){
            value *= right;
        }

        return *this;
    }

    Jet operator /=(Jet right){ //przeladowanie znaku /= w dzialaniu na jetach

        const Jet jet(*this);
        const double powrf2 = pow(right.values[0], 2);
        const double powrf3 = pow(right.values[0], 3);

        values[0] = jet.values[0] / right.values[0];
        values[1] = (jet.values[1] * right.values[0] - jet.values[0] * right.values[1]) / powrf2;
        values[2] = (jet.values[2] * right.values[0] - jet.values[0] * right.values[2]) / powrf2;
        values[3] = (-right.values[0] * (2 * jet.values[1] * right.values[1] + jet.values[0] * right.values[3]) + jet.values[3] * powrf2 +
                     2 * jet.values[0] * pow(right.values[1], 2)) / powrf3;
        values[4] = (-right.values[0] * (jet.values[1] * right.values[2] + jet.values[2] * right.values[1] + jet.values[0] * right.values[4]) +
                     jet.values[4] * powrf2 + 2 * jet.values[0] * right.values[2] * right.values[1]) / powrf3;
        values[5] = (-right.values[0] * (2 * jet.values[2] * right.values[2] + jet.values[0] * right.values[5]) + jet.values[5] * powrf2 +
                     2 * jet.values[0] * pow(right.values[2], 2)) / powrf3;
        return *this;
    }

    Jet operator /=(double right){ //przeladowanie znaku /= w dzialaniu na jetach

        for(double & value : values){
            value /= right;
        }

        return *this;
    }

    Jet& operator=(const Jet& jet) = default; //przeladowanie znaku = w dzialaniu na jetach

    friend Jet operator+(Jet left, const Jet& right) { //przeladowanie znaku + w dzialaniu na jetach
        left += right;
        return left;
    }

    friend Jet operator+(Jet left, double stala) { //przeladowanie znaku + w dzialaniu jet + stala
        left += stala;
        return left;
    }

    friend Jet operator+(double stala, Jet right) { //przeladowanie znaku + w dzialaniu stala + jet
        right += stala;
        return right;
    }

    friend Jet operator-(double stala, Jet right) { //przeladowanie znaku - w dzialaniu stala - jet
        right -= stala;
        return -right;
    }

    friend Jet operator-(Jet left, const Jet& right) { //przeladowanie znaku + w dzialaniu na jetach
        left -= right;
        return left;
    }

    friend Jet operator-(Jet left, double stala) { //przeladowanie znaku - w dzialaniu jet - stala
        left -= stala;
        return left;
    }

    Jet operator-()const{

        Jet result;

        for(int i=0; i<size; i++){
            result.values[i] = values[i] * -1;
        }

        return result;
    }

    friend Jet operator*(Jet left, const Jet& right) { //przeladowanie znaku * w dzialaniu na jetach
        left *= right;
        return left;
    }

    friend Jet operator*(Jet left, double stala) { //przeladowanie znaku * w dzialaniu jet * stala
        left *= stala;
        return left;
    }

    friend Jet operator*(double stala, Jet right) { //przeladowanie znaku * w dzialaniu stala * jet
        right *= stala;
        return right;
    }

    friend Jet operator/(Jet left, const Jet& right) { //przeladowanie znaku / w dzialaniu na jetach
        left /= right;
        return left;
    }

    friend Jet operator/(double stala, const Jet& right) { //przeladowanie znaku / w dzialaniu stala / jet
        Jet jet;
        jet.values[0] = stala;
        jet.values[1] = 1.0;
        jet /= right;
        return jet;
    }

    friend Jet operator/(Jet left, double stala) { //przeladowanie znaku / w dzialaniu jet / stala
        left /= stala;
        return left;
    }

};

struct JetCoords{ //klasa dwoch jetow

    Jet X;
    Jet Y;

    static void partialDerivatives(Jet &X, double x, Jet &Y, double y){ //obliczanie pierwszych wspolrzednych z metody FAD
        X.values[0] = x;
        X.values[1] = 1.0;

        Y.values[0] = y;
        Y.values[2] = 1.0;
    }

    static void print(const Jet& jet) { //wyswietlanie wyniku
        for (double value : jet.values)
            cout << setprecision(15) << value << " ";
        cout << endl;
    }

};

int main() {

    int M;

    cin >> M;
    double x, y;

    while(M--){ //petla glowna

        cin >> x >> y;

        JetCoords XY; //dwa jety z koordynatami
        Jet jetX;
        Jet jetY;

        XY.X = jetX;
        XY.Y = jetY;

        JetCoords::partialDerivatives(jetX, x, jetY, y);

        JetCoords::print(funkcja(jetX, jetY));

    }

    return 0;
}
