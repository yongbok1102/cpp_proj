#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "idft.h"

#define pi 3.1415926535898;

using namespace std;


int main(){
	ifstream is;
    is.open("DFT.dat");
    if (is.bad()) {
        return -1;
    }
	double F,xre,xim,XMag;
	int N=0;
    is.ignore(256, '\n'); // ignoring first line
    while(!(is.fail())){
        is >> F >> xre>>xim>>XMag;
        N++;
    }
	is.close();
	is.clear();

	double* f = new double[N-1];
	double* XRe = new double[N-1];
	double* XIm = new double[N-1];
	double* X = new double[N-1];	
	double* t = new double[N-1];	
	is.open("DFT.dat");
	is.ignore(256, '\n');	
	for(int i=0; i<N-1; i++){
        is >> f[i] >> XRe[i]>>XIm[i]>>X[i];		
	}
	is.close();	
	double df = f[1]-f[0];
	double dt = 1/(df*(N-1));
	for(int i=0; i<N-1; i++){
		t[i]=i*dt;
	}
	IDFT(XRe, XIm, X,f, t, N-1);
    return 0;
}
