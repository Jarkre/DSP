#ifndef __RandomNumber__
#define __RandomNumber__
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


class RandomNumber
{
public:
	int Get(int range_min, int range_max);
	void Seed() {srand( (unsigned)time( NULL ) );}
};

#endif