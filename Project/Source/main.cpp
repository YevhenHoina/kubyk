
#include "core/engineWindow/engineWindow.h"
#include "core/gameWindow/gameWindow.h"
#include <iostream>





int main(int argc, char** argv)
{
	bool is_game = true;

	kubykEngineInit(argc, argv, is_game);

	return 1;
}