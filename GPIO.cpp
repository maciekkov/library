#include "GPIO.h"
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
using namespace std;
enum mode
{
	WRITE  = 1,
	READ = 2
};
GPIO::GPIO(const unsigned int gpioNum)
{
    _gpioNum = toString(gpioNum);
}
int GPIO::Ginterupt()
{
    bool interrupt = false;
    string  path ="/sys/class/gpio/gpio"+_gpioNum+"/value";
    char bufor [RDBUF_LEN];
    int fd,ret;
    struct pollfd pfd[2];

    if(fd = open(path.c_str(),O_RDONLY)<0)
    {
        perror("open()");
        return -1;
    }
    pfd[0].fd = STDIN_FILENO;
    pfd[1].fd = fd;
    pfd[0].events = POLLIN;
    pfd[1].events = POLLPRI;

    while(!interrupt)
    {
		cout<<"valueMAIN:"<< endl;
        memset(bufor,0,RDBUF_LEN);
       
        if(ret = poll(pfd,2,-1)<0)
        {
            perror("poll()");
            close(fd);
            return-1;
        }
        if(ret==0)
        {
            cout<<"timeout"<<endl;
           
        }
         cout<<"timeout"<<endl;
        if (pfd[1].revents & POLLPRI) {
			lseek(pfd[1].fd, 0, SEEK_SET);
			ret = read(pfd[1].fd, bufor, RDBUF_LEN);
			cout<<"Gpio interupt occurred"<<endl;
		}

		if (pfd[0].revents & POLLIN) {
			(void)read(pfd[0].fd, bufor, 1);
			cout<<"STDIN interupt occurred"<<endl;		
			}
        interrupt = true;
	 
    }
    return 1;
}
int GPIO::openFile(const string& path,unsigned int modee,const string& data="")
{
    fstream fd;
    string value;
    string bufor = "/sys/class/gpio"+path;
    fd.open(bufor.c_str());
    if(fd.fail())
    {
        perror("couldn't open file");
        return -1;
    }
    switch(modee)
    {
    case 1:
        fd << data;
        fd.close();
        return 1;
    case 2:
        fd >> value;
        fd.close();
      //  cout<<"valueMAIN:"<<value<<endl;
        int intbufor = atoi(value.c_str());
        //cout<<"valuebufor:"<<intbufor<<endl;
        if(intbufor == 0)
        return 0;
        else
        return 1;
    }
}
int GPIO::Gexport()
{
    string path = "/export";
    if(openFile(path,WRITE,_gpioNum)<0)
    {
        perror("error export");
        return -1;
    }
    return 1;
}
int GPIO::Gdirection(const string &data)
{
    string path ="/gpio"+_gpioNum+"/direction";
    if(openFile(path,WRITE,data)<0)
    {
        perror("error direction");
        return -1;
    }
    return 1;

}
int GPIO::GsetValue(unsigned int num)
{
    string path ="/gpio"+_gpioNum+"/value";
    if(openFile(path,WRITE,toString(num))<0)
    {
        perror("error value");
        return -1;
    }
    return 1;
}
int GPIO::GsetEdge(const string& type)
{
    string path ="/gpio"+_gpioNum+"/edge";
    if(openFile(path,WRITE,type)<0)
    {
        perror("error value");
        return -1;
    }
    return 1;

}
int GPIO::GgetValue()
{
    string path ="/gpio"+_gpioNum+"/value";

    int value=0;
    value = openFile(path,READ);
    if(value <0)
    {
        perror("error value");
        return -1;
    }
  //  cout<<"value:"<<value<<endl;
	return value; 
}
int GPIO::Gunexport()
{
    string path ="/unexport";
    if(openFile(path,WRITE,_gpioNum)<0)
    {
        perror("error unexport");
       return -1;
    }
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
