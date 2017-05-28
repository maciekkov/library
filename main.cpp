#include <iostream>
#include "GPIO.h"
#include <unistd.h>
using namespace std;

int main()
{
    GPIO gpio4(4);
    GPIO gpio17(17);
    GPIO gpio23(23);
    gpio4.Gexport();
    gpio17.Gexport();
    gpio23.Gexport();

    gpio4.Gdirection("out");
    gpio17.Gdirection("in"); 
    gpio23.Gdirection("in"); 
    gpio23.GsetEdge("both");
    int num = 0;
	int stan;
	gpio23.Ginterupt();
    while(1)
    { 
		stan = gpio17.GgetValue();
		if(stan ==0)
		{	 
			usleep(2000);
			stan = gpio17.GgetValue();
			if(stan ==0)
			{
				while(stan==0)
				{
				stan = gpio17.GgetValue();
				gpio4.GsetValue(1);
				num++;
				 	printf("%d\r",num); 
				}	
			} 
		}
		 gpio4.GsetValue(0);
	}
    return 0;
}
