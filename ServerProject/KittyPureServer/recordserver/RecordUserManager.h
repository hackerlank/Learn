/**
 * \file	RecordUserManager.h
 * \version  	$Id: RecordUserManager.h 64 2013-04-23 02:05:08Z  $
 * \author  	, @ztgame.com 
 * \date 	2007年01月30日 08时15分17秒 CST
 * \brief 	档案用户管理器定义
 *
 * 
 */


#ifndef RECORDUSER_MANAGER_H
#define RECORDUSER_MANAGER_H

#include <unordered_map>
#include <unordered_set>
#include "zSingleton.h"
#include "zMisc.h"
#include "zRWLock.h"
#include "RecordCommand.h"
#include "common.h"
#include "zSocket.h"

#define MAX_CHAR_ID 9999999
#define Max_CHAR_ONCE 10000

class RecordUser;
struct SaveData
{   
    SaveData()
    {   
        role_size = 0;
        bzero(role, sizeof(role));
        bzero(&charbase,sizeof(charbase));
    }   
    //角色档案数据大小 
    CharBase charbase;
    //角色档案数据,二进制数据
    DWORD role_size;
    unsigned char role[zSocket::MAX_DATASIZE];
}__attribute__ ((packed));

class RecordUserM : public Fir::Singleton<RecordUserM>
{
	public:
		RecordUserM() 
		{
			maxCharId = 0;
            bzero(datacol,sizeof(datacol));  
		};
		~RecordUserM();
		bool init();
		bool add(RecordUser* u,bool bNew =true);
		RecordUser* getUserByCharid(QWORD charid);
		// 加载最大的角色id
		bool loadMaxCharId();
        void saveplayer(bool forbit = false);
        void synPersonNum();
	private:
		typedef std::unordered_map<QWORD, RecordUser*> RecordUserHashmap;
		typedef RecordUserHashmap::iterator RecordUserHashmap_iterator;
		typedef RecordUserHashmap::value_type RecordUserHashmap_pair;
		RecordUserHashmap userMap;
        //本区最大的charid
		QWORD maxCharId; 
        //maxCharId的读写锁
		zRWLock rwlock_maxcharid;
        //brief 互斥变量
		zMutex mlock;
        SaveData* datacol[Max_CHAR_ONCE];
	public:
		QWORD generateCharId()
		{  
            // 获取写锁
			zRWLock_scope_wrlock lock(rwlock_maxcharid); 
			maxCharId++;
            return maxCharId;
		}   
};

#endif
