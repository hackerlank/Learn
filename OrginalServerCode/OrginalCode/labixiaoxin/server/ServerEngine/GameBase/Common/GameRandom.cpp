#include "GameRandom.h"

GameRandom::GameRandom()
{
	m_seed = 0;
}

GameRandom::~GameRandom()
{

}

void GameRandom::set_seed(int seed)
{
	m_seed = seed;
}

int GameRandom::rand()
{
	ACE_UINT64 c = 262147L;	//2^18 + 3
	ACE_UINT64 t = c * m_seed;
	ACE_UINT64 m = 1L << 31;
	m = m - 1;
	m = m & 0x7fffffff;
	m_seed = t % m;
	int ret = (int)m_seed;

	printf("my rand value = %d\n", ret);

	return ret;
}