#include "maths.hpp"

int equals(long double n1, long double n2)
{
	return fabsl(n1 - n2) < EPSILON;
}
