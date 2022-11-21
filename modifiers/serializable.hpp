#ifndef SERIALIZABLE_HPP
#define SERIALIZABLE_HPP

#include <cstdio>

#define NTABS(n) for (int i = 0; i < n; i++) fprintf(outFile, "\t")

class Serializable
{
public:
	Serializable()
	{

	}

	virtual ~Serializable()
	{

	}

	virtual void serialize(FILE* outFile, int depth) = 0;
};

#endif // SERIALIZABLE_HPP
