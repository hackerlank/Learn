#pragma 

#include "..\Base\Service\BaseAdapter.h"
#include "AdminCommandSession.h"
/*
1.管理login
2.管理gateway
3.管理map server
4.管理db server
5.处理登录流程
*/

class AdminCommandMgr : public BaseAdapter
{
public:
	AdminCommandMgr(ACE_UINT32 unID);
	virtual ~AdminCommandMgr();

	virtual BaseObj *new_child_obj(ACE_UINT32 unID);

	virtual int deal_msg(MessageInfo &msgInfo);

	bool is_valid_key(const char *key);

private:
	int init_key();
	void free_key();
	bool is_same_key(const char *key, int cursor);
	void print_key(int cursor);
	char *m_key;
};