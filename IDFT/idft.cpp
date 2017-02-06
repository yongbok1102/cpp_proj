#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
#define pi 3.1415926535898;

void IDFT(double XRe[], double XIm[], double X[], double f[], double t[], int N){
    double* InvX = new double[N];    
    for(int i=0; i<N; i++){
        InvX[i] = 0;
    }
    double w = 2*pi;
	
	int num_peak=0;
	double min_spect;
	cout<<"Enter the minimal spectrum for filtering the signal\n";
	cin>>min_spect;
	for(int i=0; i<N; i++){
		if(X[i]>min_spect)
			num_peak++;
	}
	double* peak_f = new double[num_peak];
	int index = 0;
	cout<<"Peak Frequency[Hz]: \n";
	for(int i=0; i<N; i++){
		if(X[i]>=min_spect){
			peak_f[index]=f[i];
			cout<<peak_f[index]<<endl;
			index++;

		}
		else{
			XRe[i]=0;
			XIm[i]=0;
		}
	}
		
   for(int i=0; i<N; i++){
        for(int k=0; k<N; k++){
        	InvX[i] += XRe[k]*cos(w*(double)k*(double)i/(double)N) + XIm[k]*sin(w*(double)k*(double)i/(double)N);
	    }
	    InvX[i] /= N;
	}
	ofstream out;
	out.open("IDFT.dat");
	for(int i=0; i<N; i++){
		out<<t[i]<<'\t'<<InvX[i]<<endl;
	}
	out.close();		
	
}
