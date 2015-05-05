#include "RNG.hpp"

RNG::RNG()
{

}

RNG::RNG(unsigned long s)
{
	seed(s);
}

void RNG::seed(unsigned long s)
{
	generator.seed(s);
}

RNG RNG::managed;
RNG RNG::unmanaged;