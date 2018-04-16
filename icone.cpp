#include "Eigen/Dense"
#include <iostream>
#include "icone.hpp"
#include <math.h>
//g++ icone.cpp -o test -I/download/eigen
using namespace std;
using namespace Eigen;

Kmeans::Kmeans(){}
Kmeans::~Kmeans(){}

double Kmeans::norm(VectorXd* vec1, VectorXd* vec2)
{
	return sqrt((*vec2 - *vec1).squaredNorm());
}

void Kmeans::train(vector<VectorXd*> X,vector<int> y,int k)
{
	//Initialize
	//circle
	int len_y = y.size();
	for (int i = 0; i < len_y; ++i)
	{
		if( !in<int>(C_y,y[i]))
		{
			C_y.insert(y[i]);
		}
	}
	for (int i = 0; i < X.size(); ++i)
	{
		C_all[X[i]]=y[i];
	}
	for (std::set<int>::iterator iter= C_y.begin(); iter!= C_y.end(); ++iter)
	{
		//static  = getMeanU(*iter);
		C_u[*iter] = new VectorXd(getMeanU(*iter));
	}
}

VectorXd Kmeans::getMeanU(int y)
{
	VectorXd sum;
	int num=0;
	for (std::map<VectorXd*,int>::iterator iter = C_all.begin(); iter != C_all.end(); ++iter )
	{
		if (iter->second==y)
		{
			if (num==0)
			{
				sum = *(iter->first);
				num++;
				continue;
			}
			sum += *(iter->first);
			num++;
		}
	}
	//cout<<"NUM: "<<num<<endl;
	return sum/num;
}

int Kmeans::findMinNormIndex(VectorXd* x)
{
	int minIndex = C_u.begin()->first;
	double minNorm  = norm(C_u.begin()->second,x);
	//int move     = 0;
	for (std::map<int,VectorXd*>::iterator iterC_u = C_u.begin(); iterC_u != C_u.end(); ++iterC_u)
	{
		if (norm(iterC_u->second,x)<minNorm)
		{
			minIndex = iterC_u->first;
			minNorm  = norm(iterC_u->second,x);
		}
	}
	//cout<<minNorm<<endl;
	return minIndex;
}

int Kmeans::predict(VectorXd* x)
{
	return findMinNormIndex(x);
}


void Kmeans::update(VectorXd* x,int y)
{
	if (!in<int>(C_y,y))
	{
		/* add y into C_y and ... */
		C_y.insert(y);
		C_all[x] = y;
		C_u[y]   = x;
		K+=1;
	}
	else
	{
		/* add x into C_all and update C_u[y] */
		C_all[x] = y;
		VectorXd sum;int num = 0;
		for (std::map<VectorXd*,int>::iterator iter = C_all.begin(); iter != C_all.end(); ++iter )
	    {
	    	if (iter->second==y)
	    	{
	    		if (num==0)
	    		{
	    			sum = *(iter->first);
	    			num++;
	    			continue;
	    		}
	    		sum += *(iter->first);
	    		num++;
	    	}
	    }
	    ////cout<<"NUM: "<<num<<endl;
	    *(C_u[y]) = sum/num;
	}
}

template<class DType>
bool Kmeans::in(set<DType> C_i,DType element)
{
	if (C_i.find(element)!= C_i.end())
	{
		return true;
	}
	return false;
}

Experts::Experts(){}
Experts::~Experts(){}

void Experts::train(vector<VectorXd*> X,vector<int> y)
{
	int T       = X.size();
	int d       = C_experts.size();
	double nita = sqrt(2*log(double(d))/T);
	VectorXd Wh_temp(d);Wh_temp.setConstant(1);Wh.array() = Wh_temp.array();
	VectorXd V_temp(d);V_temp.setConstant(1);V.array() = V_temp.array();
	for (int t = 0; t < T; ++t)
	{
		W = Wh/(Wh.sum());
		int iter_d = 0;
		float maxW = W.maxCoeff();
		for (std::vector<Kmeans*>::iterator iterKmeans= C_experts.begin(); iterKmeans!= C_experts.end(); ++iterKmeans)
		{
			if((*iterKmeans)->predict(X[t]) == y[t]) //predict right;
			{
				V[iter_d] = 0;
			}
			else  //predict wrongly;
			{
				V[iter_d] = 1;
				if (iter_d==1)
				{			
					(*iterKmeans)->update(X[t],y[t]); //real-time update;
				}
			}
			iter_d++;
		}
	    Loss.push_back(W.dot(V));  //need Trans??? no
	    Wh.array() = (Wh.array())*((-nita*V).array().exp());   //vectorly calculate;
	}
}

map<int,double> Experts::predict(VectorXd* x)
{
	map<int,double> res;
	for (int i = 0; i < C_experts.size(); ++i)
	{
		int this_y = C_experts[i]->predict(x);
		if (res.find(this_y)==res.end())
		{
			res[this_y]=W[i];
		}
		else
		{
			res[this_y]+=W[i];
		}
	}
	return res;
}

void Experts::appendEx(Kmeans* model)
{
	C_experts.push_back(model);
}


//-------------- TEST ----------------
/*int main(int argc, char const *argv[])
{
	VectorXd v1(4),v2(4),v3(4),v4(4),v5(4);
	v1<<5.0, 6.0, 7.0, 5.0;v2<<4.0, 6.0, 3.0, 5.0;v3<<1.0, 16.0, 17.0, 9.0;v4<<2.0, 13.0, 7.0, 11.0;v5<<5.0, 0.0, 4.0, 12.0;
	vector<VectorXd*> X1;X1.push_back(&v1);X1.push_back(&v2);X1.push_back(&v3);
	vector<VectorXd*> X2;X2.push_back(&v4);X2.push_back(&v5);X2.push_back(&v3);
	vector<VectorXd*> X3;X3.push_back(&v1);X3.push_back(&v4);X3.push_back(&v3);
	vector<int> y1,y2,y3;
	y1.push_back(1),y1.push_back(1),y1.push_back(2);
	y1.push_back(2),y1.push_back(1),y1.push_back(3);
	y1.push_back(3),y1.push_back(2),y1.push_back(2);
	Kmeans km1,km2,km3;
	km.train(X,y,2);
	cout<<km.predict(&v3)<<endl;
	//cout<<*(km.C_u[2])<<endl;
	return 0;
}*/

template <class KeyType,class ValueType>
void mapPrint(map<KeyType,ValueType> MAP)
{
	for (typename std::map<KeyType,ValueType>::iterator iter= MAP.begin(); iter!= MAP.end(); ++iter)
	{
	    cout<<"是 "<<iter->first<<" 号核素的概率: "<<iter->second<<endl;	
	}
}

/*
int main(int argc, char const *argv[])
{
	VectorXd v1(4),v2(4),v3(4),v4(4),v5(4);
	v1<<5.0, 6.0, 7.0, 5.0;v2<<4.0, 6.0, 3.0, 5.0;v3<<1.0, 16.0, 17.0, 9.0;v4<<2.0, 13.0, 7.0, 11.0;v5<<5.0, 0.0, 4.0, 12.0;
	vector<VectorXd*> X1;X1.push_back(&v1);X1.push_back(&v2);X1.push_back(&v3);
	vector<VectorXd*> X2;X2.push_back(&v4);X2.push_back(&v5);X2.push_back(&v3);
	vector<VectorXd*> X3;X3.push_back(&v1);X3.push_back(&v4);X3.push_back(&v3);
	vector<int> y1,y2,y3;
	y1.push_back(1);y1.push_back(1);y1.push_back(2);
	y2.push_back(2);y2.push_back(1);y2.push_back(3);
	y3.push_back(3);y3.push_back(2);y3.push_back(2);
	Kmeans km1,km2,km3;
	km1.train(X1,y1,2);km2.train(X2,y2,3);km3.train(X3,y3,2);
	Experts ex;
	ex.appendEx(&km1);ex.appendEx(&km2);ex.appendEx(&km3);
	vector<VectorXd*> X;X.push_back(&v1);X.push_back(&v2);X.push_back(&v3);X.push_back(&v4);X.push_back(&v5);
	vector<int> y;y.push_back(1);y.push_back(1);y.push_back(2);y.push_back(3);y.push_back(3);
	ex.train(X,y);
	//cout<<"predict: "<<ex.predict(&v1)<<endl;
	ex.mapPrint<int,double>(ex.predict(&v1));
	return 0;
}*/


