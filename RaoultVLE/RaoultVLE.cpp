#include <iostream>
#include <cmath>
#include "antoine.h"
#include "DEWP.h"
#include "DEWT.h"
#include "BUBLP.h"
#include "BUBLT.h"
using namespace std;

int main(){
	int ch;
	back:
	cout<<"Choose what you want\n";
	cout<<"DEWP(1), DEWT(2)\n";
	cout<<"BUBLP(3), BUBLT(4)\n";
	cin>>ch;
	system("cls");
	if(ch==1)
		DEWP();
	else if(ch==2)
		DEWT();
	else if(ch==3)
		BUBLP();
	else if(ch==4)
		BUBLT();
	else{
		cout<<"Invalid input\n";
		goto back;
	}
	return 0;
}
