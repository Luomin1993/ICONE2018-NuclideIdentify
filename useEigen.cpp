#include <iostream>
#include <vector>
#include <Eigen/Dense>

//g++ useEigen.cpp -o test -I/download/eigen

using namespace Eigen;
using namespace std;

//typedef Matrix<float, 3, 1> Vector3f
int main(int argc, char const *argv[])
{
	/* code */
	Matrix<float, 5, 1> vec1;
	Matrix<float, 5, 1> vec2;
	Matrix<float, 5, 1> vec3;
	vec1<<5.0, 6.0, 7.0, 5.0, 6.0;
    vec2<<6.0, 7.0, 5.0, 6.0, 7.0;
    vec3<<1.0, 1.0, 1.0, 1.0, 1.0;
	//cout<<"norm: "<<(vec2 - vec1).squaredNorm()<<endl;
	//cout<<(vec1+vec2+vec3)/3<<endl;
	//cout<<vec2.array()*((0*vec1).array().exp())<<endl;
	//cout<<VectorXd(vec1.array())<<endl;
	//cout<<vec1.setConstant(1)<<endl;
	//vec1.array()=vec1.array().exp();
	//cout<<vec1.dot(vec2)<<endl;
	//vec1.array() = vec2.array();
	//cout<<vec1.setConstant(2)<<endl;
	cout<<vec1.minCoeff()<<endl;
	return 0;
}