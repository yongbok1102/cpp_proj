//antoine.cpp

#include <cmath>

double Psat(double T, double A, double B, double C){
	double param = A-B/(T+C);
	return pow(10,param);
}
