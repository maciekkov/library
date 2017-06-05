#include "GPIO.h"
#include <unistd.h>
int main()
{
	 
	GPIO gpio4(4);
	GPIO gpio22(22);
	gpio22.Gdirection("in");
	//return value as int
	int status=0;
	while(1)
	{
		cout<<status<<endl;
		status=gpio22.GgetValue();
			if(status==0)
			{
				usleep(200);
				status=gpio22.GgetValue();
				if(status==0)
				{
					while(status == 0)
					{
						status=gpio22.GgetValue();
						gpio4.GsetValue(1);
					}
					gpio4.GsetValue(0);
				}
			}
	}
	return 0;
}
