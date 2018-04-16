#include "csv.hpp"
#include "icone.hpp"
#include <unistd.h>
//g++ app.cpp icone.cpp -o app -I/download/eigen
template <class KeyType,class ValueType>
void mapPrint(map<KeyType,ValueType> MAP)
{
	for (typename std::map<KeyType,ValueType>::iterator iter= MAP.begin(); iter!= MAP.end(); ++iter)
	{
	    cout<<"The predicted nuclide ID: "<<iter->first<<"  the probability:"<<iter->second<<endl;	
	}
}



int main(int argc, char const *argv[])
{
	vector<VectorXd*> X1,X2,X3,X,X_test;
	vector<int> y1,y2,y3,y,y_test;
	X1=csv::get_X("d1.csv");X2=csv::get_X("d2.csv");X3=csv::get_X("d3.csv");X=csv::get_X("d.csv");X_test=csv::get_X("d_test.csv");
	y1=csv::get_y("d1.csv");y2=csv::get_y("d2.csv");y3=csv::get_y("d3.csv");y=csv::get_y("d.csv");y_test=csv::get_y("d_test.csv");
	Kmeans km1;km1.train(X1,y1,8);
	Kmeans km2;km2.train(X2,y2,8);
	Kmeans km3;km3.train(X3,y3,8);
	Kmeans km4;km4.train(X3,y3,8);
	Kmeans km5;km5.train(X3,y3,8);
	//km2->train(X2,y2,8);km3->train(X3,y3,8);
	Experts ex;
	ex.appendEx(&km1);ex.appendEx(&km2);ex.appendEx(&km3);ex.appendEx(&km4);ex.appendEx(&km5);
	ex.train(X,y);
	//mapPrint<int,double>(ex.predict(X1[47]));
	/*for (std::vector<double>::iterator iter= ex.Loss.begin(); iter!= ex.Loss.end(); ++iter)
	{
		cout<<*iter<<endl;
	}*/
	/*for (std::map<int,VectorXd*>::iterator map_iter= km1.C_u.begin(); map_iter!= km1.C_u.end(); ++map_iter)
	{
		cout<<map_iter->first<<endl;
		cout<<(*(map_iter->second))[0]<<" "<<(*(map_iter->second))[1]<<" "<<(*(map_iter->second))[2]<<" ... ..."<<endl;
	}*/
	for (int i = 0; i < 20; ++i)
	{
		mapPrint<int,double>(ex.predict(X_test[i]));
		//cout<<"The predicted nuclide ID: "<<km1.predict(X3[i])<<endl;
		cout<<"The real nuclide ID: "<<y_test[i]<<endl;
		cout<<" "<<endl;
		sleep(1);
	}
	return 0;
}	
