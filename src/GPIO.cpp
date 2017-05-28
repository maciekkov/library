#include "GPIO.h"

using namespace std;

GPIO::GPIO(const unsigned int gpioNum)
{
    _gpioNum = toString(gpioNum);
}
int GPIO::openFile(const string& path,const string& data)
{
    ofstream fd;
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
    string path = "export";
    if(openFile(path,_gpioNum)<0)
    {
        perror("error export");
        exit(-1);
    }
}
int GPIO::Gdirection()
{

}
int GPIO::GsetValue(unsigned int num)
{

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
