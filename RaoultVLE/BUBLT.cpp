#include <iostream>
#include <cmath>
#include "antoine.h"
using namespace std;

void BUBLT(){
	cout<<"BUBLT is designed to calculate y_i, T, given x_i, P\n";
	cout<<"It's based on Raoult's Law\n";
	int n;
	cout<<"Enter number of compounds\n"; cin>>n;
	
	//given parameter
	double* X; X = new double[n];
	double T;
	
	//variables to calculate
	double* Y; Y = new double[n];
	double P;
	
	double* A; A = new double[n];
	double* B; B = new double[n];
	double* C; C = new double[n];
	
	cout<<"Enter the pressure\n"; cin>>P;
	string pUnit;  
	cout<<"Enter the pressure unit\n"; cin>>pUnit;
	string tUnit;
	cout<<"Enter the temperature unit\n"; cin>>tUnit;	
	for(int i=0; i<n; i++){
		cout<<"Enter the molar fraction of compound (liquid phase) "<<(i+1)<<endl;
		cin>>X[i];
	}
	cout<<"Antoine Equation is given below\n";
	cout<<"log10(Psat)=A-B/(T+C)\n";
	for(int i=0; i<n; i++){
		cout<<"Enter the Antoine coefficients(A,B,C) of compound "<<(i+1)<<endl;
		cin>>A[i]>>B[i]>>C[i];
	}
	
	cout<<"Estimate the temperature\n";
	cin>>T;
	double Told = T+1;
	int itr = 0; int itrMax = 1000000;
	double eq = 0; double eqDot = 0;
	while(fabs(T-Told)>1e-013){
		Told = T;
		for(int i=0; i<n; i++){
			eq += X[i]*Psat(Told,A[i],B[i],C[i])/P;
			eqDot += log(10)*B[i]*pow((Told+C[i]),-2)*X[i]*Psat(Told,A[i],B[i],C[i])/P;
		}
		T = Told - (eq-1)/eqDot;
		itr++;
		eq = 0; eqDot = 0;
		if(itr==itrMax){
			cout<<"Convergence failed\n";
			break;
		}
	}
	
	for(int i=0; i<n; i++){
		Y[i] = X[i]*Psat(T,A[i],B[i],C[i])/P;
	}
	cout<<"T["<<tUnit<<"]="<<T<<endl;
	cout<<"Vapor Phase:\n";
	for(int i=0; i<n; i++){
		cout<<"Y["<<(i+1)<<"]="<<Y[i]<<endl;
	}		
}
