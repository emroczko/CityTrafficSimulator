#include <iostream>
#include "Simulator.h"
#include "Definitions.h"


int main()
{
	system("dir");
    ZPR::Simulator(SCREEN_HEIGHT, SCREEN_WIDTH, "CityTrafficSimulator");
	return EXIT_SUCCESS;
}



