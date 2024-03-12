#include <cmath>
#include <iostream>

using namespace std;

double f(double x) {
	return sin(5*x);
}

int main() {

	double ll = 0, ul = 3;
	int n = 25;
	double h = (ul - ll) / (n - 1);

	double a[n], b[n], c[n], y[n], l[n], u[n], x[n];
	for(int i = 0; i < n; i++) {
		a[i] = 1;
		b[i] = 4;
		c[i] = 1;
		y[i] = 3/h * (f(h*(i+1)) - f(h*(i-1)));
	}
	a[0] = 0; a[n-1] = 2;
	b[0] = 1; b[n-1] = 1;
	c[0] = 2; c[n-1] = 0;
	y[0]  = 1/h * (-5.0/2*f(ll) + 2*f(ll + h) + 1.0/2*f(ll + 2*h));
	y[n-1] = 1/h * (5.0/2*f(ul) - 2*f(ul - h) - 1.0/2*f(ul - 2*h));


	u[0] = b[0];
	for(int i = 1; i < n; i++) {
		l[i] = a[i] / u[i-1];
		u[i] = b[i] - l[i] * c[i-1];
		y[i] = y[i] - l[i] * y[i-1];
	}

	x[n-1] = y[n-1] / u[n-1];
	for(int i = n-2; i >= 0; i--) {
		x[i] = (y[i] - c[i]*x[i+1]) / u[i];
	}

	cout << "[";
	for(int i = 0; i < n-1; i++) {
		cout << x[i] << ",";
	}
	cout << x[n-1] << "]" << endl;
}
