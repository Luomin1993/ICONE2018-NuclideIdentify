#include <iostream>
#include <stdlib.h>
#include <vector>
#include <random>
#include <sstream>

using namespace std;
std::default_random_engine e;  
std::uniform_int_distribution<> u(0,10);  

//int u = int(((double)rand()/(RAND_MAX + 1))+0.6);
//g++ betMethod.cpp -o bet -std=c++11

struct match
{
	int id;
	int correct;
	match(int ID,int CORRECT) :
	     id(ID), correct(CORRECT){}
};

template <class Type>  
Type stringToNum(const string& str)
{  
    istringstream iss(str);  
    Type num;  
    iss >> num;  
    return num;      
}  


/*float giveBack(int numOfMatches,float odd2b1,float correct)
{
	for(int i=0;i<numOfMatches;i++)
	{

	}
}
*/

void planA(vector<match*> matches,float money,float odd2b1,float onemoney)
{
	float backmoney=0;
	int match_1;
	int match_2;
	while(money>0)
	{
		match_1    = u(e);
		match_2    = u(e);
		cout<<"plan: "<<match_1<<"+"<<match_2<<endl;
		backmoney += matches[match_2]->correct*(matches[match_1]->correct)*odd2b1*onemoney;
		money     -= onemoney;
	}
	cout<<"+++++ $ +++++"<<endl;
	cout<<"back money: "<<backmoney<<endl;
}

void planB(vector<match*> matches,float money,float odd2b1,float onemoney)
{
	float backmoney=0;
	int match_1;
	int match_2;
	int id = 0;
	while(money>0)
	{
		match_1    = id++;
		match_2    = id++;
		cout<<"plan: "<<match_1<<"+"<<match_2<<endl;
		cout<<"back: "<<matches[match_2]->correct*(matches[match_1]->correct)*odd2b1*onemoney<<endl;
		backmoney += matches[match_2]->correct*(matches[match_1]->correct)*odd2b1*onemoney;
		money     -= onemoney;
		if(id>=10){id=0;}
	}
	cout<<"+++++ $ +++++"<<endl;
	cout<<"back money: "<<backmoney<<endl;
}

void test(float money,float odd2b1,float onemoney)
{
	vector<match*> matches;
	for(int i=0;i<11;i++)
	{
		//matches.push_back(new match(i,int(((double)rand()/RAND_MAX)+0.63)) );
		matches.push_back(new match(i,int(double(u(e))/10+0.9) ) );
		//cout<<"rand:  "<<u(e)<<endl;
	}
	for (std::vector<match*>::iterator i = matches.begin(); i != matches.end(); ++i)
	{
		cout<<(*i)->correct<<endl;
	}
	planA(matches,money,odd2b1,onemoney);
}

int main(int argc, char const *argv[])
{
	/* code */
	float money     = stringToNum<float>(argv[1]);
	float odd2b1    = stringToNum<float>(argv[2]);
	float onemoney  = stringToNum<float>(argv[3]);
	test(money,odd2b1,onemoney);
	return 0;
}