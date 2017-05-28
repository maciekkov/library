#include "GPIO.h"

using namespace std;

GPIO::GPIO(const unsigned int gpioNum)
{
    _gpioNum = toString(gpioNum);
}
int GPIO::openFile(const string& path,const string& data)
{
    fstream fd;
    string bufor = "sys/class/gpio"+path;
    fd.open(bufor.c_str());
    if(fd.fail())
    {
        perror("couldn't open file");
        return -1;
    }
    fd << data;
    fd.close();
    return 1;
}
int GPIO::Gexport()
{
    string path = "/export";
    if(openFile(path,_gpioNum)<0)
    {
        perror("error export");
        exit(-1);
    }
}
int GPIO::Gdirection(const string &data)
{
    string path ="/gpio"+_gpioNum+"/unexport";
    if(openFile(path,data)<0)
    {
        perror("error direction");
        exit(-1);
    }
}
int GPIO::GsetValue(unsigned int num)
{
     string path ="gpio"+_gpioNum+"/value";
    if(openFile(path,toString(num))<0)
    {
        perror("error value");
        exit(-1);
    }
}
int GPIO::GgetValue()
{

}
int GPIO::Gunexport()
{

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
    //dtor
}
