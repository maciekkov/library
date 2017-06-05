#include "GPIO.h"
 
using namespace std;


GPIO::GPIO(const unsigned int gpioNum,const string& direction)
{
    if(openStreamRead("/gpio"+toString(gpioNum)+"/direction")<0)
    {
        _gpioNum = toString(gpioNum);
        Gexport();
        Gdirection(direction);
    }
    else
    {
		 _gpioNum = toString(gpioNum);
         cout<<"GPIO number: "<<gpioNum<<" already exist"<<endl;
    }
   
    
}
GPIO::GPIO(const string& gpioNum,const string& direction)
{
   if(openStreamRead("/gpio"+ gpioNum +"/value")<0)
    {
        _gpioNum = gpioNum ;
        Gexport();
        Gdirection(direction);
    }
    else
    {
		 _gpioNum = gpioNum;
        cout<<"GPIO number: "<<gpioNum<<" already exist"<<endl;
    }
}
int GPIO::openStreamWrite(const string& path,const string& data)
{
    fstream fd;
    string bufor = "/sys/class/gpio"+path;
    fd.open(bufor.c_str());
    if(fd.good())
    {
        fd << data;
        fd.close();
        return 1;
    }
    return -1;
     
}
int GPIO::openStreamRead(const string& path)
{
    fstream fd;
    string bufor = "/sys/class/gpio"+path;
    fd.open(bufor.c_str());
    string data;
    if(fd.good())
    {
        fd >>data;
        fd.close();
        int num = atoi(data.c_str());
        return num;
        
    }
    return -1;
    
}
int GPIO::Gexport()
{
    string path ="/export";
    if(openStreamWrite(path,_gpioNum)<0)
    {
        perror("error export");
        return -1;
    }
    return 1;
}
int GPIO::Gdirection(const string &data)
{
	 
    string path ="/gpio"+_gpioNum+"/direction";
     if(openStreamWrite(path,data)<0)
    {
        perror("error direction");
        return -1;
    }
    return 1;
}
int GPIO::GsetValue(unsigned int num)
{
	cout<<_gpioNum<<endl;
    string path ="/gpio"+_gpioNum+"/value";
     if(openStreamWrite(path,toString(num))<0)
    {
        perror("error setValue");
        return -1;
    }
    return 1;
}
int GPIO::GsetEdge(const string& type)
{
    string path ="/gpio"+_gpioNum+"/edge";
     if(openStreamWrite(path,type))
    {
        perror("error setEdge");
        return -1;
    }
    return 1;
}
int GPIO::GgetValue()
{
    string path ="/gpio"+_gpioNum+"/value";
    int value=0;
     value= openStreamRead(path);
     if(value <0)
     {
         perror("getValue()");
         return -1;
     }
     if(value==0)
        return 0;
     else
        return 1; 
}
int GPIO::Gunexport()
{
	cout<<"usuwanie "<<_gpioNum<<endl;
    string path ="/unexport";
   if(openStreamWrite(path,_gpioNum))
    {
        perror("error unexport");
        return -1;
    }
    return 1;
}
string GPIO::toString(unsigned int num)
{
    string bufor;
    stringstream ss;
    ss<<num;
    bufor = ss.str();
    return bufor;
}
GPIO::~GPIO()
{
  Gunexport();
}
