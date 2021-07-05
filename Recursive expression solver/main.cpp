//Jan Skwarczek

#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

double nth_element(double x0, double x1, double k){
	
	double c1 = 7.0/48.0*(7.0*x0-x1);
	double c2 = x0 - c1;
	
	return c1*pow(7.0, -k) + c2*pow(7.0, k);
}

int main(){
	
	int z;
	
	cin >> z;
	
	while(z--){
		
		double x0, x1;
		int n;
		
		cin >> x0 >> x1 >> n;
		
		double k[n];
		
		for(int i = 0; i<n; i++){
			
			cin >> k[i];
			
		}
		
		for(int i = 0; i<n; i++){
			
			cout << setprecision(16) << scientific << nth_element(x0, x1, k[i]) << endl;
			
		}
	}
	
	return 0;
}
