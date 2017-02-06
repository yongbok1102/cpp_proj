#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
#define pi 3.1415926535898;
double magn(double x, double y){
    return sqrt(x*x + y*y);
}

void DFT(double x[], double dt, int N){
    double* X = new double[N];
    double* XRe = new double[N];
    double* XIm = new double[N];
 
    for(int i=0; i<N; i++){
        XIm[i]=0;
        XRe[i] = 0;
        X[i] = 0;
    }
    double w = 2*pi;
    for(int i=0; i<N; i++){
        for(int k=0; k<N; k++){
            XRe[i] += x[k]*cos(w*(double)k*(double)i/(double)N);
            XIm[i] += x[k]*sin(w*(double)k*(double)i/(double)N);
        }
        X[i] = magn(XRe[i],XIm[i]);
    }
    double* f = new double[N];
    for(int i=0; i<N; i++){
        f[i]=(double)i/(N*dt);
    }

    ofstream out;
    out.open("DFT.dat");
    out<<"#Freq[Hz]"<<'\t'<<"Real"<<'\t'<<"Im"<<'\t'<<"Spectrum"<<endl;
    for(int i=0; i<N; i++){
        out<<f[i]<<'\t'<<XRe[i]<<'\t'<<XIm[i]<<'\t'<<X[i]<<endl;
    }
    out.close();
}
