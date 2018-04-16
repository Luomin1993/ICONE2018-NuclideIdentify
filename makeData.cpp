#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include <unistd.h>
#include <Eigen/Dense>
#include <stdlib.h>
#define __int32 int
#define __int64 long long
#define random(x) (rand()%x)

using namespace std;
using namespace Eigen;
//g++ makeSourceData.cpp -o run -I/download/Eigen/ -std=gnu++11

//double sec_vec[] = {12.0,320.0,72.0,50.0,50.0,50.0,20.0,40.0,45.0,33.0,78.0,20.0,22.0,24.0,235.0,335.0,275.0,32.0};
//extern Matrix<double,18,1> section_data(12.0,320.0,72.0,50.0,50.0,50.0,20.0,40.0,45.0,33.0,78.0,20.0,22.0,24.0,235.0,335.0,275.0,32.0);
//section_data << 12.0,320.0,72.0,50.0,50.0,50.0,20.0,40.0,45.0,33.0,78.0,20.0,22.0,24.0,235.0,335.0,275.0,32.0;

VectorXd* makeSectionData()
{
    static VectorXd section_data(18);
    section_data << 12.0,320.0,72.0,50.0,50.0,50.0,20.0,40.0,45.0,33.0,78.0,20.0,22.0,24.0,235.0,335.0,275.0,32.0;
    return &section_data;
}


VectorXd* makeSourceData()
{
    static VectorXd source_data(18);
    VectorXd scala(18);
    scala.setConstant(1);
    source_data.setRandom();
    source_data.array() = ((source_data.array()+scala.array())/2)*(*makeSectionData()).array();
    return &(source_data);
}

VectorXd* getDataFromHttp()
{
    //to do
}

/*

bool sendDataToHttp()
{
        CURL *curl;
    CURLcode res;
    FILE *fp;
    if ((fp = fopen(filename, "w")) == NULL)
        return false;
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "&logintype=uid&u=xieyan&psw=xxx86");    // 指定post内容
        //curl_easy_setopt(curl, CURLOPT_PROXY, "10.99.60.201:8080");
        curl_easy_setopt(curl, CURLOPT_URL, " 115.28.138.54/cgi/data_handler.cgi ");   // 指定url
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    fclose(fp);
    return true;
}
*/

vector<double>* makePowerData(VectorXd* x)
{
    static vector<double> res;
    VectorXd BasicPowerDataScala(18);
    VectorXd TotalPowerDataScala(18); 
    BasicPowerDataScala.setRandom();
    TotalPowerDataScala.setRandom();
    VectorXd scala(18);
    scala.setConstant(1);
    BasicPowerDataScala.array()=(BasicPowerDataScala.array()+scala.array())*0.1;
    TotalPowerDataScala.array()=(TotalPowerDataScala.array()+scala.array())*0.8;
    res.push_back(BasicPowerDataScala.dot(*x)+random(10));
    res.push_back(TotalPowerDataScala.dot(*x)+random(25));
    return &res;
}

void testMakeSourceData()
{
    __int32 time = 0;
    while(time<50)
    {
        //cout<<*(makeSourceData())<<endl;
        VectorXd thisData = *(makeSourceData());
        sleep(2);
        cout<<"时间： "<<time*12.5<<" min"<<endl;
		cout<<"===+======+===+===+===+===+===+===+===+===+===+===+===+===+===+===+===+===+===+===+===+===+===+===+===+===+===+===+===+===+===+===+===++"<<endl;
        cout<<"喷淋开度  "<<"除盐卸压  "<<"反应程度  "<<"灰棒  "<<"白棒  "<<"黑棒  "<<"给水  "<<"给水速度  "<<"水泵功率  "<<"满功  "<<"反应调节  "<<"发电负载  "<<"调节负载  "<<"二回路给水  "<<"二回路调节  "<<"二回路负载  "<<"上充流  "<<"中子毒素  "<<"排水  "<<endl;
        cout<<thisData[0]<<" "<<thisData[1]<<" "<<thisData[2]<<" "<<thisData[3]<<" "<<thisData[4]<<" "<<thisData[5]<<" "<<thisData[6]<<" "<<thisData[7]<<" "<<thisData[8]<<" "<<thisData[9]<<" "<<thisData[10]<<" "<<thisData[11]<<" "<<thisData[12]<<" "<<thisData[13]<<" "<<thisData[14]<<" "<<thisData[15]<<" "<<thisData[16]<<" "<<thisData[17]<<" "<<endl;
        vector<double>* power = makePowerData(makeSourceData());
        cout<<"------------------------"<<endl;
        cout<<"发电功率(MW): "<<(*power)[2*time]<<endl;
        cout<<"负载功率(MW): "<<(*power)[2*time+1]<<endl;
        cout<<"------------------------"<<endl;
        cout<<"   "<<endl;
        cout<<"   "<<endl;
        time++;
    }
}

int main(int argc, char const *argv[])
{
    testMakeSourceData();
    return 0;
}

