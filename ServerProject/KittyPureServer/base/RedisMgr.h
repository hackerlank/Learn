#ifndef _REDIS_MGR_H
#define _REDIS_MGR_H

#include "zSingleton.h"
#include "CharBase.h"
#include "serialize.pb.h"

struct stPuppet
{
	CharBase charbase;
    ProtoMsgData::Serialize binary;
};

class RedisMgr : public Singleton<RedisMgr>
{
	friend class Singleton<RedisMgr>;
public:
	virtual ~RedisMgr(){}

	bool get_charbase(const QWORD charid, CharBase& charbase); 
	bool get_binary(const QWORD charid, ProtoMsgData::Serialize& binary);
	bool get_binary(const QWORD charid, const char* input_buf, DWORD input_size, ProtoMsgData::Serialize& binary);
	bool get_puppet(const QWORD charid, stPuppet& puppet);
    bool is_login_first(const QWORD charid);
    //更新redis中的accountInfo
    bool updateRedisAccount(const AccountInfo &accountInfo);
    //获得redis中的accountInfo数据
    bool getRedisAccountByEmail(const char *email,AccountInfo &accountInfo);
    //获得redis中的accountInfo数据
    bool getRedisAccountByPhoneNum(const char *phoneNum,AccountInfo &accountInfo);
private:
	RedisMgr(){}
};

#endif
