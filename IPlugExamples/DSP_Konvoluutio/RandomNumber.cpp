#include <stdlib.h>
#include "RandomNumber.h"

int RandomNumber::Get(int range_min, int range_max)
{
	  int randomNumber = 0;

      randomNumber =  (double)rand() / (32767 + 1) * (range_max - range_min) + range_min;

	  return randomNumber;

}
