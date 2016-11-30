#include "CharacterList.h"
#include "..\..\GameBase\Common\GameUtils.h"
#include "ace\OS_NS_string.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif


CharacterList::CharacterList()
{
	m_list = NULL;
	m_capcity = 0;
	m_unCount = 0;
}

CharacterList::~CharacterList()
{

}

void CharacterList::init_size(int capcity)
{
	if(m_list != NULL)
	{
		delete m_list;
	}

	m_list = new CharacterInfoExt[capcity];
	m_capcity = capcity;
}

void CharacterList::init(ACE_UINT32 unCount, void *list)
{
	CharacterInfoExt *tmp = (CharacterInfoExt *)list;

	if(unCount > m_capcity)
	{
		unCount = m_capcity;
	}

	ACE_OS::memcpy(m_list, tmp, sizeof(CharacterInfoExt) * unCount);

	m_unCount = 0;
	int i;
	for(i = 0;i < unCount;i ++)
	{
		if(m_list[i].unItemID == 0)
		{
			break;
		}

		m_unCount ++;
	}
}