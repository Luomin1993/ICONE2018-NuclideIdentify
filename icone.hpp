#include <iostream>
#include "Eigen/Dense"
#include <map>
#include <set>
#include <vector>
//typedef map<VectorXd*,int> C_ALL;

using namespace std;
using namespace Eigen;

class Kmeans
{
public:
	Kmeans();
	~Kmeans();
	double norm(VectorXd* vec1, VectorXd* vec2);
	void train(vector<VectorXd*> X,vector<int> y,int k);
	int predict(VectorXd* x);
public:	
	void update(VectorXd* x,int y);
	int  findMinNormIndex(VectorXd* x);
	double getTotalDistance();
	vector<int> getInitIndexes();
	VectorXd getMeanU(int y);

    template <class DType>  
	bool in(set<DType> C_i,DType element);
public:
	double J_0;
    map<VectorXd*,int> C_all;
    vector<VectorXd*> C_r;
    map<int,VectorXd*> C_u;
    set<int> C_y;
    int K;
};

class Experts
{
public:
	Experts();
	~Experts();
	void train(vector<VectorXd*> X,vector<int> y);
	map<int,double> predict(VectorXd* x);
	void appendEx(Kmeans*);
	
	//template <class KeyType,class ValueType>
    //void mapPrint(map<KeyType,ValueType> MAP);
public:
    vector<Kmeans*>	C_experts;
    VectorXd W;                  //W = (w1,...,wd);
    VectorXd V;                  //V = (v1,...,vd);
    VectorXd Wh;
    vector<double> Loss;          //Loss_t = <Vt,Wt>;    
};
