#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "dft.h"

#define pi 3.1415926535898;

using namespace std;


int main(){
	ifstream is;
    is.open("samp.dat");
    if (is.bad()) {
        return -1;
    }
	double T,X;
	int N=0;
    is.ignore(256, '\n'); // ignoring first line
    while(!(is.fail())){
        is >> T >> X;
        N++;
    }
	is.close();
	is.clear();

	double* t = new double[N-1];
	double* x = new double[N-1];
	is.open("samp.dat");
	is.ignore(256, '\n');	
	for(int i=0; i<N-1; i++){
        is >> t[i] >> x[i];		
	}
	is.close();	
	double dt = t[1]-t[0];
    DFT(x,dt,N-1);

    return 0;
}
