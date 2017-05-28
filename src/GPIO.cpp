#include "GPIO.h"

using namespace std;

GPIO::GPIO(const unsigned int gpioNum)
{
    _gpioNum = toString(gpioNum);
}
int GPIO::Ginterupt()
{
    bool interrupt = false;
    string  path ="/gpio"+_gpioNum+"/value";
    char bufor [RDBUF_LEN];
    int fd,ret;
    struct pollfd pfd;

    if(fd = open(path.c_str(),O_RDONLY)<0)
    {
        perror("open()");
        return -1;
    }
    pfd.fd = fd;
    pfd.events = POLLPRI;

    while(!interrupt)
    {
        memset(bufor,0,RDBUF_LEN);
        lseek(fd,0,SEEK_SET);
        if(ret = poll(&pfd,1,-1)<0)
        {
            perror("poll()");
            close(fd);
            return-1;
        }
        if(ret==0)
        {
            cout<<"timeout"<<endl;
            return -1;
        }
        ret  = read(fd,bufor,RDBUF_LEN-1);
        if(ret<0)
        {
            perror("read()");
            return -1;
        }
        interrupt = true;

    }
    return 1;
}
int GPIO::openFile(const string& path,unsigned int mode,const string& data="")
{
    fstream fd;
    string value;
    string bufor = "sys/class/gpio"+path;
    fd.open(bufor.c_str());
    if(fd.fail())
    {
        perror("couldn't open file");
        return -1;
    }
    switch(mode)
    {
    case 1:
        fd << data;
        fd.close();
        return 1;
    case 2:
        fd >> value;
        fd.close();
        return atoi(value.c_str());
    }
}
int GPIO::Gexport()
{
    string path = "/export";
    if(openFile(path,1,_gpioNum)<0)
    {
        perror("error export");
        exit(-1);
    }
}
int GPIO::Gdirection(const string &data)
{
    string path ="/gpio"+_gpioNum+"/unexport";
    if(openFile(path,1,data)<0)
    {
        perror("error direction");
        exit(-1);
    }
    return 1;

}
int GPIO::GsetValue(unsigned int num)
{
    string path ="gpio"+_gpioNum+"/value";
    if(openFile(path,1,toString(num))<0)
    {
        perror("error value");
        exit(-1);
    }
    return 1;
}
int GPIO::GsetEdge(const string& mode)
{
    string path ="gpio"+_gpioNum+"/edge";
    if(openFile(path,1,mode)<0)
    {
        perror("error value");
        exit(-1);
    }
    return 1;

}
int GPIO::GgetValue()
{
    string path ="gpio"+_gpioNum+"/value";

    int value;
    if( value = openFile(path,2)<0)
    {
        perror("error value");
        exit(-1);
    }

    if (value==0)
        return 0;
    else
        return 1;

}
int GPIO::Gunexport()
{
    string path ="/unexport";
    if(openFile(path,1,_gpioNum)<0)
    {
        perror("error unexport");
        exit(-1);
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
