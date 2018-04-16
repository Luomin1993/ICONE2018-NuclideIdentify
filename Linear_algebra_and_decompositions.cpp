#include <iostream>
#include <Eigen/Dense>

//g++ Linear_algebra_and_decompositions.cpp -o la -I/download/eigen

using namespace std;
using namespace Eigen;


//QR方法解线性方程组
int main()
{
   Matrix3f A;
   Vector3f b;
   A << 1,2,3,  4,5,6,  7,8,10;
   b << 3, 3, 4;
   cout << "Here is the matrix A:\n" << A << endl;
   cout << "Here is the vector b:\n" << b << endl;
   Vector3f x = A.colPivHouseholderQr().solve(b);
   cout << "The solution is:\n" << x << endl;
}


//矩阵求逆
int main()
{
   Matrix2f A, b;
   A << 2, -1, -1, 3;
   b << 1, 2, 3, 1;
   cout << "Here is the matrix A:\n" << A << endl;
   cout << "Here is the right hand side b:\n" << b << endl;
   Matrix2f x = A.ldlt().solve(b);
   cout << "The solution is:\n" << x << endl;
}


//计算数值法求解和真实值的残差
int main()
{
   MatrixXd A = MatrixXd::Random(100,100);
   MatrixXd b = MatrixXd::Random(100,50);
   MatrixXd x = A.fullPivLu().solve(b);
   double relative_error = (A*x - b).norm() / b.norm(); // norm() is L2 norm
   cout << "The relative error is:\n" << relative_error << endl;
}


//计算特征值和特征向量
int main()
{
   Matrix2f A;
   A << 1, 2, 2, 3;
   cout << "Here is the matrix A:\n" << A << endl;
   SelfAdjointEigenSolver<Matrix2f> eigensolver(A);
   if (eigensolver.info() != Success) abort();
   cout << "The eigenvalues of A are:\n" << eigensolver.eigenvalues() << endl;
   cout << "Here's a matrix whose columns are eigenvectors of A \n"
        << "corresponding to these eigenvalues:\n"
        << eigensolver.eigenvectors() << endl;
}


//计算逆行列式
int main()
{
   Matrix3f A;
   A << 1, 2, 1,
        2, 1, 0,
        -1, 1, 2;
   cout << "Here is the matrix A:\n" << A << endl;
   cout << "The determinant of A is " << A.determinant() << endl;
   cout << "The inverse of A is:\n" << A.inverse() << endl;
}


//最小二乘解
int main()
{
   MatrixXf A = MatrixXf::Random(3, 2);
   cout << "Here is the matrix A:\n" << A << endl;
   VectorXf b = VectorXf::Random(3);
   cout << "Here is the right hand side b:\n" << b << endl;
   cout << "The least-squares solution is:\n"
        << A.jacobiSvd(ComputeThinU | ComputeThinV).solve(b) << endl;
}


//分离矩阵计算与构造(解耦合)
int main()
{
   Matrix2f A, b;
   LLT<Matrix2f> llt;
   A << 2, -1, -1, 3;
   b << 1, 2, 3, 1;
   cout << "Here is the matrix A:\n" << A << endl;
   cout << "Here is the right hand side b:\n" << b << endl;
   cout << "Computing LLT decomposition..." << endl;
   llt.compute(A);
   cout << "The solution is:\n" << llt.solve(b) << endl;
   A(1,1)++;
   cout << "The matrix A is now:\n" << A << endl;
   cout << "Computing LLT decomposition..." << endl;
   llt.compute(A);
   cout << "The solution is now:\n" << llt.solve(b) << endl;
}


// Rank-revealing分解
int main()
{
   Matrix3f A;
   A << 1, 2, 5,
        2, 1, 4,
        3, 0, 3;
   cout << "Here is the matrix A:\n" << A << endl;
   FullPivLU<Matrix3f> lu_decomp(A);
   cout << "The rank of A is " << lu_decomp.rank() << endl;
   cout << "Here is a matrix whose columns form a basis of the null-space of A:\n"
        << lu_decomp.kernel() << endl;
   cout << "Here is a matrix whose columns form a basis of the column-space of A:\n"
        << lu_decomp.image(A) << endl; // yes, have to pass the original A
}


//LU分解，设定阈值求秩
int main()
{
   Matrix2d A;
   A << 2, 1,
        2, 0.9999999999;
   FullPivLU<Matrix2d> lu(A);
   cout << "By default, the rank of A is found to be " << lu.rank() << endl;
   lu.setThreshold(1e-5);
   cout << "With threshold 1e-5, the rank of A is found to be " << lu.rank() << endl;
}
