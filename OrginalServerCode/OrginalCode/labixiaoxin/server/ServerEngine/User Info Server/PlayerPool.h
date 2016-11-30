#pragma once

#include "..\GameBase\Common\GameDefine.h"
#include "ace\Null_Mutex.h"
#include "ace\Hash_Map_Manager.h"

//#define CHARACTER_COUNT_PER_BLOCK 40960

/*
typedef struct tagCharacterPoolBlock
{
	struct tagCharacterPoolBlock *prev;
	struct tagCharacterPoolBlock *next;
	ACE_UINT32 list[CHARACTER_COUNT_PER_BLOCK];
}CharacterPoolBlock;

typedef struct tagCharacterPoolLinker
{
	ACE_UINT32 unCount;
	CharacterPoolBlock *head;
	CharacterPoolBlock *tail;
}CharacterPoolLinker;

#define MAX_POOL_LINKER 60
#define LEVEL_COUNT_PER_LINKER 5
*/

#define PLAYER_COUNT_PER_BLOCK 4096

typedef struct tagPlayerPoolBlock
{
	struct tagPlayerPoolBlock *next;
	struct tagPlayerPoolBlock *prev;
	PublicPlayerInfo *list[PLAYER_COUNT_PER_BLOCK];
}PlayerPoolBlock;


/*
typedef PlayerPoolBlock * PPlayerPoolBlock;

#define MAX_PLAYER_POOL_INDEX 1024

typedef struct tagPlayerPoolIndexNode
{
	struct tagPlayerPoolIndexNode *next;
	struct tagPlayerPoolIndexNode *prev;
	PPlayerPoolBlock list[MAX_PLAYER_POOL_INDEX];
}PlayerPoolIndexNode;
*/

/*
typedef struct tagPlayerPoolLinker
{
	ACE_UINT32 unCount;
	PlayerPoolBlock *head;
	PlayerPoolBlock *tail;
}PlayerPoolLinker;

*/

/*
池中的角色不排序，删除的时候，最后一个补上来
*/


class PlayerPool
{
public:
	PlayerPool();
	~PlayerPool();

	void reset();
	int add(PublicPlayerInfo *playerInfo);
	PublicPlayerInfo *remove(PublicPlayerInfo *playerInfo);
	PublicPlayerInfo *get_last();
	void swap_2_last(int idx);
	
	//ACE_UINT32 remove(int idx);
	//ACE_UINT32 remove(PlayerPoolBlock *block);

	PublicPlayerInfo *get_player_id_by_index(int idx);

	int fill_2_array(PublicPlayerInfo *list[]);
	
	//int get_random_count

	int m_nPoolID;
	ACE_UINT32 m_unPoolType;
	ACE_UINT32 m_unCount;
private:
	
	PlayerPoolBlock *m_head;
	PlayerPoolBlock *m_tail;

	void set_player_info(PlayerPoolBlock *block, int offset, PublicPlayerInfo *playerInfo, int idx);
	PlayerPoolBlock *get_block(int idx);
	PlayerPoolBlock *get_last_block();

	//PlayerPoolBlock *get_block(int idx);

	//生成一个静态的node内存池
};

typedef PlayerPool * PPlayerPool;