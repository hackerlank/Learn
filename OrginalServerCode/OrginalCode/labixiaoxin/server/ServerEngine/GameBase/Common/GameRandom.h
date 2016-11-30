#pragma once

#include "ace\ace.h"

class GameRandom
{
public:
	GameRandom();
	~GameRandom();

	void set_seed(int seed);
	int rand();

private:
	ACE_UINT64 m_seed;
};