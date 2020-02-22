#include<iostream>
using namespace std;
#include"stringBuilder.h"

int main()
{
	stringBuilder ank = stringInitialize("qwerty ");
	stringBuilder ush = stringInitialize("uiop ");
	cout<<ank.word<<endl;
	cout<<ush.word<<endl;

	stringBuilder o = stringAppend(ank, ush);
	
	
	stringBuilder qw = stringInitialize("asdfg");

	stringBuilder o2 = stringAppend(qw, o);

	stringBuilder last = stringAppend(o2, o);
	findSubstring(last, "sdvds");
}