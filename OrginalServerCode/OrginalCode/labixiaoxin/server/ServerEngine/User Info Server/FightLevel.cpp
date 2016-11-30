#include "FightLevel.h"
#include "..\ace\os_include\os_assert.h"

CFightLevel::CFightLevel()
{
	m_unCount = 0;
	ZeroVar(m_list);
}

CFightLevel::~CFightLevel()
{

}

void CFightLevel::Update( const FightPlayerInfoBase & info )
{
	ACE_ASSERT(m_unCount <= MAX_FIGHT_LEVEL_COUNT);
// 	if (m_unCount == 0)
// 	{
// 		m_list[m_unCount] = info;
// 		m_unCount++;
// 		return;
// 	}
// 	if (m_unCount > MAX_FIGHT_LEVEL_COUNT)
// 		m_unCount = MAX_FIGHT_LEVEL_COUNT;

	if ((m_unCount < MAX_FIGHT_LEVEL_COUNT) || (m_list[m_unCount-1].m_hurt <= info.m_hurt))//有更新
	{
		InsertionSort(info);
	}
}

void CFightLevel::InsertionSort(const FightPlayerInfoBase & info )
{
	bool isAdd = true;
	for (int i=0;i<m_unCount;i++)
	{
		if (m_list[i].m_userID == info.m_userID)
		{
			m_list[i] = info;
			isAdd = false;
			break;
		}
	}

	int len = m_unCount;
	if (isAdd)
	{
		m_list[m_unCount] = info;
		if (m_unCount < MAX_FIGHT_LEVEL_COUNT)
			m_unCount ++;
		++len;
	}

	//插入排序
	for (int j=1; j<len; j++)  
	{  
		FightPlayerInfoBase key = m_list[j];  
		int i = j-1;  
		while (i>=0 && m_list[i].m_hurt  <  key.m_hurt)  
		{  
			m_list[i+1] = m_list[i];  
			i--;
		}  
		m_list[i+1] = key; 
	}
}

