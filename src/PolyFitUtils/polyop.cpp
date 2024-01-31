#include <vector>
#include <iostream>
#include "cmath"
// ����ʽ������ֵ
double fx(double x, double coeffs[], int degree) {
    double result = 0;
    int i;
    for ( i = 0; i <= degree; ++i) {
        result += coeffs[i] * pow(x, degree - i);
    }
    return result;
}


