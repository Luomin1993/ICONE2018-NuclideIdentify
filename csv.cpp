#include <iostream>  
#include <string>  
#include <vector>  
#include <fstream>  
#include <sstream>  
#include <Eigen/Dense>
using namespace std;  
using namespace Eigen;
//g++ csv.cpp -o csv -I/download/eigen
namespace csv
{   
    template <class Type>  
    Type stringToNum(const string& str)
    {  
        istringstream iss(str);  
        Type num;  
        iss >> num;  
        return num;      
    }  

    vector<VectorXd*> get_X(string path)  
    {  
        // 写文件  
        //ofstream outFile;  
        //outFile.open("data.csv", ios::out); // 打开模式可省略  
        //outFile << "name" << ',' << "age" << ',' << "hobby" << endl;  
        //outFile << "Mike" << ',' << 18 << ',' << "paiting" << endl;  
        //outFile << "Tom" << ',' << 25 << ',' << "football" << endl;  
        //outFile << "Jack" << ',' << 21 << ',' << "music" << endl;  
        //outFile.close();  
      
        // 读文件  
        const char *char_path = path.data();
        ifstream inFile(char_path, ios::in);  
        string lineStr;  
        static vector<VectorXd*> X;  
        if (X.size()>0)
        {
            X.clear();
        }
        int line = 0;
        while (getline(inFile, lineStr))  
        {  
            // 打印整行字符串  
            //cout << lineStr << endl;  
            // 存成二维表结构  
            stringstream ss(lineStr);  
            string str;  
            VectorXd x(10);
            // 按照逗号分隔
            int dim = 0;  
            while (getline(ss, str, ',') && dim<9)  
            {
                //lineArray.push_back(str);  
                //cout<<stringToNum<double>(str)<<endl;
                x[dim] = stringToNum<double>(str);
                dim++;
            }
            //VectorXd* p_x = new VectorXd(10);
            //(*p_x).array() = x.array();    
            //cout<<x[0]<<endl;
            //X.push_back(p_x);
            X.push_back(new VectorXd(10));
            (*(X[line])).array() = x.array();
            line++;  
        }  
        return X;
    } 

    vector<int> get_y(string path)  
    {  
        // 读文件  
        const char *char_path = path.data();
        ifstream inFile(char_path, ios::in);  
        string lineStr;  
        static vector<int> y;
        if (y.size()>0)
        {
            y.clear();
        }  
        int line = 0;
        while (getline(inFile, lineStr))  
        {  
            // 打印整行字符串  
            //cout << lineStr << endl;  
            // 存成二维表结构  
            stringstream ss(lineStr);  
            string str;  
            int y_i;
            // 按照逗号分隔
            int dim = 0;  
            while (getline(ss, str, ',') && dim<11)  
            {
                //lineArray.push_back(str);  
                //cout<<stringToNum<double>(str)<<endl;
                y_i = int(stringToNum<float>(str));
                dim++;
            }
            y.push_back(y_i);
            line++;  
        }  
        return y;
    }
}


//test

int main(int argc, char const *argv[])
{
    /*vector<VectorXd*> X = csv::get_X("./new.csv");
    for (std::vector<VectorXd*>::iterator iter = X.begin(); iter != X.end(); ++iter )
    {
        cout<<(*(*iter))[0]<<endl;
    }*/
    vector<int> y = csv::get_y("./d.csv");
    for (std::vector<int>::iterator iter = y.begin(); iter != y.end(); ++iter )
    {
        cout<<*iter<<endl;
    }
    //string str =  "2.620444107055664062e+01";
    //cout<<csv::stringToNum<double>(str)<<endl;
    return 0;
}