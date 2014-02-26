#include "Equipment.h"
#include "Macro.h"
#include "Photon.h"
#include <iostream>

Equipment::Equipment()
{
	setOrigin(BLOCK_SIZE/2, BLOCK_SIZE/2);
	setRotation(0.0);
}