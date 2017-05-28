#ifndef GPIO_H
#define GPIO_H

#include <string>
#include <fstream>
#include <fcntl.h>
#include <sstream>
#include <stdlib.h>
using namespace std;
class GPIO
{
    string _gpioNum;
    enum value{LOW,HIGH};
public:
    GPIO()=default;
    GPIO(const unsigned int gpioNum);
    GPIO(const string& gpioNum):_gpioNum(gpioNum){}

    int Gexport();
    int Gdirection(const string &data);
    int GsetValue(unsigned int num);
    int GgetValue();
    int Gunexport();
    virtual ~GPIO();
private:
    int openFile(const string& path,const string& data);
    string toString(unsigned int num);
};

#endif // GPIO_H
