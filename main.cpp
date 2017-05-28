#include <iostream>
#include "GPIO.h"
using namespace std;

int main()
{
    GPIO gpio4(4);
    gpio4.Gexport();

    gpio4.Gdirection("in");
    gpio4.GsetValue(1);

    return 0;
}
