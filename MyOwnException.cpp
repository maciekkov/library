#include <exception>

class MyOwnException:public exception
{
	public:
	virtual const char* what() const throw()
	{
		return "could not open file";
	}
	
	
};

