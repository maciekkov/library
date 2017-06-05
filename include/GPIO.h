#ifndef GPIO_H
#define GPIO_H

#include <string>
#include <fcntl.h>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> 
#include <iostream>
#include <fstream>

using namespace std;

class GPIO
{
    string _gpioNum;                                    //zmienna przechowywujaca numer gpio 
public:
    GPIO();
    GPIO(const unsigned int gpioNum,const string& direction="out");
    GPIO(const string&  gpioNum,const string& direction="out");

    int Gexport();
    int Gdirection(const string &data);
    int GsetValue(unsigned int num);
    int GsetEdge(const string& mode);
    int GgetValue();
    int Gunexport();
    
    virtual ~GPIO();
private:
   int  openStreamWrite(const string& path,const string& data="");
   int  openStreamRead(const string& path);

    string toString(unsigned int num);
};

#endif // GPIO_H
