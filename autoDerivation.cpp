#include <iostream>
#include <math.h>

#define h 0.001
//g++ autoDerivation.cpp -o exe

using namespace std;

template <class NumType>
NumType autoDerivation(NumType (*func)(NumType x),NumType x0)
{
	return (4*func(x0+h)-3*func(x0)-func(x0+2*h))/(2*h);
}

float SIN(float x)
{
	return sin(x);
}

int main(int argc, char const *argv[])
{
	/* TEST */
    cout<<"answer: "<<autoDerivation<float>(SIN,3.141592)<<endl;
	return 0;
}