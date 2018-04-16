#include <map>  
#include <string>  
#include <vector>
#include <iostream>  
using namespace std;  
  
vector<int*> getNum(int num)
{
	//static int res = num/2;
	std::vector<int*> vec;
	for (int i = 1; i < 4; ++i)
	{
		//static int res = num/i;
		vec.push_back(new int(num/i));
	}
	return vec;
}

int main()  
{  
    map<int, string> mapStudent;  
    mapStudent[1] = "student_one";  
    mapStudent[1] = "student_two";  
    mapStudent[2] = "student_three";  
    //map<int, string>::iterator iter;  
    //for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++)  
    //   cout<<iter->first<<' '<<iter->second<<endl;  
	//cout<<*(getNum(5)[2])<<endl;
	//cout<<*(getNum(5)[1])<<endl;
	cout<<(mapStudent.find(1)==mapStudent.end())<<endl;//means not found
}  