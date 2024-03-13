#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

void transposeMatrix(double** mat, int n) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < i; j++) {
			double temp = mat[i][j];
			mat[i][j] = mat[j][i];
			mat[j][i] = temp;
		}
	}
	return;
}

void getMatrix(double** mat, int n) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			cin >> mat[i][j];
		}
	}
	return;
}

double** multiplyTwoMatrices(double** A, double** B, int n) {
	double** C = new double*[n];
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			for(int k = 0; k < n; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return C;
}

void checkTransposeMultiplicity(double** A, double** B, int n) {
	cout << "Calculating (AB)^T ...";
	double** AB_T = multiplyTwoMatrices(A, B, n);
	transposeMatrix(AB_T, n); 
}

int main() {
	int n;
	cout << "Enter the number of rows in square matrix: ";
	cin >> n;

	double** A = new double*[n];
	double** B = new double*[n];

	cout << "Enter the values of Matrix A:" << endl;
	getMatrix(A, n);

	cout << "Enter the values of Matrix B:" << endl;
	getMatrix(B, n);

	cout << "Check if (AB)^T = (B^T)(A^T) ..." << endl;

}
