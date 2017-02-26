#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "LinFitRoutine.h"
using namespace std;

int main(){
    ifstream is;
    is.open("samp.dat");
    if(is.bad()){
        return -1;
    }
    double X,Y;
    int N = 0;
    
    is.ignore(256,'\n');
    while(!(is.fail())){
        is>>X>>Y;
        N++;
    }
    is.close();
    is.clear();
    int n = N-1;
    double* x = new double[n];
    double* y = new double[n];
    
    is.open("samp.dat");
    is.ignore(256,'\n');
    for(int i=0; i<n; i++){
        is>>x[i]>>y[i];
    }
    cout<<"LinFit is designed to fit the given data into linear function\n";
    cout<<"y=a+b*x\n";
    double a, b, c;
    cout<<"Enter the initial estimation of a,b\n"; cin>>a>>b;
    
    double aold = a + 1;
    double bold = b + 1;
    
    double h;
    cout<<"Enter the spacial step for calculating derivatives\n"; cin>>h;
    
    double incr;
    cout<<"Enter the parameter for speeding up\n"; cin>>incr;
    
    double decr;
    cout<<"Enter the parameter for preventing overflowing\n"; cin>>decr;
    
    double dFda, dFdb;
    double d2Fda2, d2Fdb2;
    double da, db;
    double res = 1;
    
    double tol;
    cout<<"Enter the tolerance error\n"; cin>>tol;
    
    int itrMax;
    cout<<"Enter the maximum iteration number\n"; cin>>itrMax;
    
    double pa = 1;
    
    for(int i=1; i<=itrMax; i++){
        aold = a; bold = b;
        dFda = LinFitDev(a+h,b,x,y,n) - LinFitDev(a-h,b,x,y,n);
        dFdb = LinFitDev(a,b+h,x,y,n) - LinFitDev(a,b-h,x,y,n);
        
        dFda /= (2.*h); dFdb /= (2.*h);
        
        d2Fda2 = LinFitDev(a+h,b,x,y,n) -2.*LinFitDev(a,b,x,y,n) + LinFitDev(a-h,b,x,y,n);
        d2Fdb2 = LinFitDev(a,b+h,x,y,n) -2.*LinFitDev(a,b,x,y,n) + LinFitDev(a,b-h,x,y,n);
        
        d2Fda2 /= (h*h); d2Fdb2 /= (h*h);
        
        da = -dFda/d2Fda2; db = -dFdb/d2Fdb2;
        
        a = aold + pa*da; b = bold + pa*db;
        if(LinFitDev(a,b,x,y,n)>=LinFitDev(aold,bold,x,y,n)){
            pa *= decr;
            a = aold + pa*da; b = bold + pa*db;
        }
        else
            pa *= incr;
        
        res = (aold-a)*(aold-a) + (bold-b)*(bold-b);
        res = sqrt(res);
        if(res<=tol){
            cout<<"itr: "<<i<<endl;
            cout<<"Convergence succeeded!\n";
            break;
        }
    }
    cout<<"y=a+b*x\n";
    cout<<"a="<<a<<", b="<<b<<endl;
    
    double yMean = 0;
    for(int i=0; i<n; i++){
        yMean += y[i];
    }
    yMean /= n;
    
    double SSTot = 0;
    for(int i=0; i<n; i++){
        SSTot += (y[i]-yMean)*(y[i]-yMean);
    }
    double SSRes = LinFitDev(a,b,x,y,n);
    double R2 = 1 - (SSRes/SSTot);
    cout<<"R2="<<R2<<endl;
    
    return 0;
}
