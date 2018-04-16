#include <iostream>
#include <Eigen/Dense>
//g++ mat.cpp -o mat -I/download/eigen
using namespace Eigen;
using namespace std;

//矩阵的按元素赋值
int main()
{
  //------------------------
  MatrixXd m(2,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);
  cout << "Here is the matrix m:\n" << m << endl;
  VectorXd v(2);
  v(0) = 4;
  v(1) = v(0) - 1;
  cout << "Here is the vector v:\n" << v << endl;
  
  //------------------------
  Matrix3f m;
  m << 1, 2, 3,
     4, 5, 6,
     7, 8, 9;
  cout << m << endl;

  
}

//矩阵的加减运算
int main()
{
  Matrix2d a;
  a << 1, 2,
       3, 4;
  MatrixXd b(2,2);
  b << 2, 3,
       1, 4;
  std::cout << "a + b =\n" << a + b << std::endl;
  std::cout << "a - b =\n" << a - b << std::endl;
  std::cout << "Doing a += b;" << std::endl;
  a += b;
  std::cout << "Now a =\n" << a << std::endl;
  Vector3d v(1,2,3);
  Vector3d w(1,0,0);
  std::cout << "-v + w - v =\n" << -v + w - v << std::endl;
}


//矩阵与实数相乘
int main()
{
  Matrix2d a;
  a << 1, 2,
       3, 4;
  Vector3d v(1,2,3);
  std::cout << "a * 2.5 =\n" << a * 2.5 << std::endl;
  std::cout << "0.1 * v =\n" << 0.1 * v << std::endl;
  std::cout << "Doing v *= 2;" << std::endl;
  v *= 2;
  std::cout << "Now v =\n" << v << std::endl;
}

//转置
int main()
{
  Matrix2d mat;
  mat << 1, 2,
         3, 4;
  Vector2d u(-1,1), v(2,0);
  std::cout << "Here is mat*mat:\n" << mat*mat << std::endl;
  std::cout << "Here is mat*u:\n" << mat*u << std::endl;
  std::cout << "Here is u^T*mat:\n" << u.transpose()*mat << std::endl;
  std::cout << "Here is u^T*v:\n" << u.transpose()*v << std::endl;
  std::cout << "Here is u*v^T:\n" << u*v.transpose() << std::endl;
  std::cout << "Let's multiply mat by itself" << std::endl;
  mat = mat*mat;
  std::cout << "Now mat is mat:\n" << mat << std::endl;
}


//向量内积、求共轭向量
int main()
{
  Vector3d v(1,2,3);
  Vector3d w(0,1,2);
  cout << "Dot product: " << v.dot(w) << endl;
  double dp = v.adjoint()*w; // automatic conversion of the inner product to a scalar
  cout << "Dot product via a matrix product: " << dp << endl;
  cout << "Cross product:\n" << v.cross(w) << endl;
}


//矩阵内一些性质：平均值、和、迹
int main()
{
  Eigen::Matrix2d mat;
  mat << 1, 2,
         3, 4;
  cout << "Here is mat.sum():       " << mat.sum()       << endl;
  cout << "Here is mat.prod():      " << mat.prod()      << endl;
  cout << "Here is mat.mean():      " << mat.mean()      << endl;
  cout << "Here is mat.minCoeff():  " << mat.minCoeff()  << endl;
  cout << "Here is mat.maxCoeff():  " << mat.maxCoeff()  << endl;
  cout << "Here is mat.trace():     " << mat.trace()     << endl;
}


//矩阵极大小值元素及其位置
int main(int argc, char const *argv[])
{
  Matrix3f m = Matrix3f::Random();
  std::ptrdiff_t i, j;
  float minOfM = m.minCoeff(&i,&j);
  cout << "Here is the matrix m:\n" << m << endl;
  cout << "Its minimum coefficient (" << minOfM 
       << ") is at position (" << i << "," << j << ")\n\n";
  RowVector4i v = RowVector4i::Random();
  int maxOfV = v.maxCoeff(&i);
  cout << "Here is the vector v: " << v << endl;
  cout << "Its maximum coefficient (" << maxOfV 
       << ") is at position " << i << endl;
  return 0;
}

//矩阵子块（子矩阵）
int main()
{
  Eigen::MatrixXf m(4,4);
  m <<  1, 2, 3, 4,
        5, 6, 7, 8,
        9,10,11,12,
       13,14,15,16;
  cout << "Block in the middle" << endl;
  cout << m.block<2,2>(1,1) << endl << endl;
  for (int i = 1; i <= 3; ++i)
  {
    cout << "Block of size " << i << "x" << i << endl;
    cout << m.block(0,0,i,i) << endl << endl;
  }
}


//矩阵子块操作
int main()
{
  Array22f m;
  m << 1,2,
       3,4;
  Array44f a = Array44f::Constant(0.6);
  cout << "Here is the array a:" << endl << a << endl << endl;
  a.block<2,2>(1,1) = m;
  cout << "Here is now a with m copied into its central 2x2 block:" << endl << a << endl << endl;
  a.block(0,0,2,3) = a.block(2,1,2,3);
  cout << "Here is now a with bottom-right 2x3 block copied into top-left 2x2 block:" << endl << a << endl << endl;
}


//列操作
int main()
{
  Eigen::MatrixXf m(3,3);
  m << 1,2,3,
       4,5,6,
       7,8,9;
  cout << "Here is the matrix m:" << endl << m << endl;
  cout << "2nd Row: " << m.row(1) << endl;
  m.col(2) += 3 * m.col(0);
  cout << "After adding 3 times the first column into the third column, the matrix m is:\n";
  cout << m << endl;
}

//子列、子行
int main()
{
  Eigen::Matrix4f m;
  m << 1, 2, 3, 4,
       5, 6, 7, 8,
       9, 10,11,12,
       13,14,15,16;
  cout << "m.leftCols(2) =" << endl << m.leftCols(2) << endl << endl;
  cout << "m.bottomRows<2>() =" << endl << m.bottomRows<2>() << endl << endl;
  m.topLeftCorner(1,3) = m.bottomRightCorner(3,1).transpose();
  cout << "After assignment, m = " << endl << m << endl;
}

//向量的分拆
int main()
{
  Eigen::ArrayXf v(6);
  v << 1, 2, 3, 4, 5, 6;
  cout << "v.head(3) =" << endl << v.head(3) << endl << endl;
  cout << "v.tail<3>() = " << endl << v.tail<3>() << endl << endl;
  v.segment(1,4) *= 2;
  cout << "after 'v.segment(1,4) *= 2', v =" << endl << v << endl;
}


//向量拼接
int main()
{
  RowVectorXd vec1(3);
  vec1 << 1, 2, 3;
  std::cout << "vec1 = " << vec1 << std::endl;
  RowVectorXd vec2(4);
  vec2 << 1, 4, 9, 16;
  std::cout << "vec2 = " << vec2 << std::endl;
  RowVectorXd joined(7);
  joined << vec1, vec2;
  std::cout << "joined = " << joined << std::endl;
  return 0;
}

//向量子块的操作与赋值
int main(int argc, char const *argv[])
{
  MatrixXf matA(2, 2);
  matA << 1, 2, 3, 4;
  MatrixXf matB(4, 4);
  matB << matA, matA/10, matA/10, matA;
  std::cout << matB << std::endl;

  Matrix3f m;
  m.row(0) << 1, 2, 3;
  m.block(1,0,2,2) << 4, 5, 7, 8;
  m.col(2).tail(2) << 6, 9;                   
  std::cout << m <<std::endl;
  return 0;
}


//多维数组赋值
int main(int argc, char const *argv[])
{
  std::cout << "A fixed-size array:\n";
  Array33f a1 = Array33f::Zero();
  std::cout << a1 << "\n\n";
  std::cout << "A one-dimensional dynamic-size array:\n";
  ArrayXf a2 = ArrayXf::Zero(3);
  std::cout << a2 << "\n\n";
  std::cout << "A two-dimensional dynamic-size array:\n";
  ArrayXXf a3 = ArrayXXf::Zero(3, 4);
  std::cout << a3 << "\n";
  return 0;
}


//多维数组的数学函数运算
int main(int argc, char const *argv[])
{
  ArrayXXf table(10, 4);
  table.col(0) = ArrayXf::LinSpaced(10, 0, 90);
  table.col(1) = M_PI / 180 * table.col(0);
  table.col(2) = table.col(1).sin();
  table.col(3) = table.col(1).cos();
  std::cout << "  Degrees        Radians          Sine        Cosine\n";
  std::cout << table << std::endl;
  return 0;
}


//矩阵子块赋值等等
int main(int argc, char const *argv[])
{
  const int size = 6;
  MatrixXd mat1(size, size);
  mat1.topLeftCorner(size/2, size/2)     = MatrixXd::Zero(size/2, size/2);
  mat1.topRightCorner(size/2, size/2)    = MatrixXd::Identity(size/2, size/2);
  mat1.bottomLeftCorner(size/2, size/2)  = MatrixXd::Identity(size/2, size/2);
  mat1.bottomRightCorner(size/2, size/2) = MatrixXd::Zero(size/2, size/2);
  std::cout << mat1 << std::endl << std::endl;
  MatrixXd mat2(size, size);
  mat2.topLeftCorner(size/2, size/2).setZero();
  mat2.topRightCorner(size/2, size/2).setIdentity();
  mat2.bottomLeftCorner(size/2, size/2).setIdentity();
  mat2.bottomRightCorner(size/2, size/2).setZero();
  std::cout << mat2 << std::endl << std::endl;
  MatrixXd mat3(size, size);
  mat3 << MatrixXd::Zero(size/2, size/2), MatrixXd::Identity(size/2, size/2),
          MatrixXd::Identity(size/2, size/2), MatrixXd::Zero(size/2, size/2);
  std::cout << mat3 << std::endl;

  return 0;
}


//矩阵间运算
int main()
{
  MatrixXd m = MatrixXd::Random(3,3);
  m = (m + MatrixXd::Constant(3,3,1.2)) * 50;
  cout << "m =" << endl << m << endl;
  VectorXd v(3);
  v << 1, 2, 3;
  cout << "v =" << endl << v << endl;
  cout << "m * v =" << endl << m * v << endl << endl;

  MatrixXf mat = MatrixXf::Random(2, 3);
  std::cout << mat << std::endl << std::endl;
  mat = (MatrixXf(2,2) << 0, 1, 1, 0).finished() * mat;
  std::cout << mat << std::endl;
}

