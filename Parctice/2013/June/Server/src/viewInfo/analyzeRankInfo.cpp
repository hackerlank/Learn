/*************************************************

Copyright: xhm

Author:xhm

Date:2012-12-7 

Description:客户端请求排名数据解析部分；

**************************************************/
#include "analyzeRankInfo.h"
#include "rankInfoAsist.h"

extern int sock_fd;
extern Hero* pg_hero;
extern int g_msg_len;
extern map<string, Hero*> heroId_to_pHero;


/*获取排名信息 消息的格式--> 11，11，type	1财富排名
											2活动排名
											3战力排名
											4杀戮排名
											5击杀红名排名
											6声望排名
												    */
void getRankInfo(char* buffers)
{
	MSG_BEGIN(buffers,g_msg_len)
	MSG_INT(int type);										/*获取排行榜的类型.*/	
	MSG_INT(int page);					//页数
	
	cout<<"11,11,"<<type<<","<<page<<endl;
	int number=type*4+page;
	cout<<"number:"<<number<<endl;
	char *msg=getRankInfo(number);						
	if(msg != NULL)
	{
		send_msg(sock_fd,msg);
	}
}
