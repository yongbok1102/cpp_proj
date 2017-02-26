#include <cmath>

double LinFitFunc(double a, double b, double x){
    return a + b*x;
}

double LinFitDev(double a, double b, double x[], double y[], int n){
    double r;
    double sum = 0;
    
    for(int i=0; i<n; i++){
        r = y[i] - LinFitFunc(a,b,x[i]);
        sum += r*r;
    }
    return sum;
}
