#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
using namespace std;
#define pi 3.1415926535898;
double magn(double x, double y){
    return sqrt(x*x + y*y);
}

void FFT(double x[], double dt, int N){
    double* X = new double[N];
    double* XRe = new double[N];
    double* XIm = new double[N];
 	double* GRe = new double[N];
 	double* GIm = new double[N];
 	double* HRe = new double[N];
 	double* HIm = new double[N];
    for(int i=0; i<N; i++){
        XIm[i]=0;
        XRe[i] = 0;
        X[i] = 0;
        GRe[i] = 0;
 		GIm[i] = 0;
 		HRe[i] = 0;
 		HIm[i] = 0;
    }
    double w = 2*pi;
    double start = clock();
    for(int i=0; i<N/2; i++){
        for(int k=0; k<N/2; k++){
            GRe[i] += x[2*k]*cos(2.*w*(double)k*(double)i/(double)N);
            GIm[i] += x[2*k]*sin(2.*w*(double)k*(double)i/(double)N);
            HRe[i] += x[2*k+1]*cos(2.*w*k*i/(double)N);
            HIm[i] += x[2*k+1]*sin(2.*w*k*i/(double)N);
        }
    }
    for(int i=0; i<N/2; i++){
    	XRe[i] = GRe[i] + HRe[i]*cos(w*(double)i/(double)N) - HIm[i]*sin(w*(double)i/(double)N);
    	XIm[i] = GIm[i] + HRe[i]*sin(w*(double)i/(double)N) + HIm[i]*cos(w*(double)i/(double)N);
		XRe[i+(N/2)] = GRe[i] - HRe[i]*cos(w*i/(double)N) + HIm[i]*sin(w*i/(double)N);
    	XIm[i+(N/2)] = GIm[i] - HRe[i]*sin(w*i/(double)N) - HIm[i]*cos(w*i/(double)N);
    	X[i] = magn(XRe[i],XIm[i]);
    	X[i+(N/2)] = magn(XRe[i+(N/2)],XIm[i+(N/2)]);    	
    }
	double end = clock();
	double elap = (end-start)/CLOCKS_PER_SEC;
	cout<<"elapsed time[s]: "<<elap<<endl;    
    double* f = new double[N];
    for(int i=0; i<N; i++){
        f[i]=(double)i/(N*dt);
    }

    ofstream out;
    out.open("FFT.dat");
    out<<"#Freq[Hz]"<<'\t'<<"Real"<<'\t'<<"Im"<<'\t'<<"Spectrum"<<endl;
    for(int i=0; i<N; i++){
        out<<f[i]<<'\t'<<XRe[i]<<'\t'<<XIm[i]<<'\t'<<X[i]<<endl;
    }
    out.close();
}
