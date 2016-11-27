/**
 * \file
 * \version  $Id: LoginTask.h 2877 2005-09-12 12:16:19Z whj $
 * \author  Songsiliang,
 * \date 2004年11月23日 10时20分01秒 CST
 * \brief 定义登陆连接任务
 *
 */

#ifndef _LoginTask_h_
#define _LoginTask_h_

#include "zTCPServer.h"
#include "zTCPTask.h"
#include "zService.h"
#include "zMisc.h"
#include "zDBConnPool.h"
#include "LoginCommand.h"
#include "zTCPTask.h"
#include "zTime.h"
#include "FLServer.h"
#include "SlaveCommand.h"
#include "dispatcher.h"
#include "extractProtoMsg.h"
#include "login.pb.h"

#define TCP_TYPE			0
/**
 * \brief 服务器连接任务
 *
 */

class LoginTask;
typedef ProtoDispatcher<LoginTask> LoginUserCmdDispatcher;

class LoginTask : public zTCPTask
{

	public:

		LoginTask( zTCPTaskPool *pool, const int sock);
		~LoginTask() {};

		int verifyConn();
		int recycleConn();
		bool uniqueAdd();
		bool uniqueRemove();
        
        bool msgParseProto(const BYTE *data, const DWORD nCmdLen);
        bool msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen);

        inline void genTempID()
		{
			tempid = (((uniqueID % (FLService::getMe().getMaxPoolSize() * 4)) + 1) << 1) + TCP_TYPE;
			uniqueID++;
		}

		inline const DWORD getTempID() const
		{
			return tempid;
		}

		inline bool timeout(const zTime &ct)
		{
            return lifeTime.elapse(ct) >= 90 ? true : false;
		}

		inline bool checkClientIP(const char *clientIP) const { return 0 == strncmp(clientIP, getIP(), strlen(clientIP)); }
		void GetPassTmp( unsigned char *pszPass,std::string &passwd, int iLen )
		{

			char szTmp[65];
			BYTE len = pszPass[0];
			{
				memset( szTmp, 0, sizeof(char) * 65 );

				for ( int i = 0, j = 0; j < len && j < iLen - 1 ; i++, j += 2 )
				{
					DecryChar(szTmp + i, (unsigned char*)pszPass + 1 + j);
				}
				szTmp[len / 2] = 0;
			}
			passwd = szTmp;
			return;
		}
		void DecryChar(char *pszDes,unsigned  char *pszSrc )
		{
			BYTE array;
			char btmp, btmp1;

			BYTE keyData[8]={210, 41, 182, 141, 14, 242, 120, 178};//?ü??
			//BYTE keyData[8];
			//size_t keySize;
			array = (pszSrc[0] >> 4) & 0x0F;
			btmp = pszSrc[0] ^ keyData[array];
			btmp1 = pszSrc[1] ^ keyData[array];
			btmp = (btmp << 4) & 0xF0;
			btmp1 = (btmp1 >> 4) & 0x0F;
			btmp |= btmp1;

			pszDes[0] = btmp - 2;
		}

		void UnUseIPEncry( const char *pszKey, unsigned char *pszSrc, int iNum )
		{
			BYTE nKey = strlen( pszKey ), rkey = 0;
			
			for ( int i = 0; i < iNum; i++ )
			{
				pszSrc[i]--;
				pszSrc[i] ^= pszKey[rkey];
				
				if ( ++rkey >= nKey )
					rkey = 0;
			}
		}
		void DecMatirxPasswd(char *dest, unsigned char *src)
		{
			for ( int i = 0, j = 0; j < 12; i++, j += 2 )
				DecryChar( dest + i ,(unsigned char*)src + j );
		}
        //注册
        bool registerAccount(const ProtoMsgData::ReqRegister *message);
        //获得网关信息
        bool getGatewayInfo(const ProtoMsgData::ReqGateway *message);
    public:
        static LoginUserCmdDispatcher login_user_dispatcher;
    private:
        void getClientIP(char *clientIP);
		void verify_login(const DWORD loginTempID, const t_NewLoginSession& session);
    private:
        bool m_verify;
		zTime lifeTime;
		DWORD tempid;
		static DWORD uniqueID;
};

#endif


