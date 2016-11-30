#include <iostream>
#include <boost/asio.hpp>
#include "../src/client/MyClient.h"
#include <boost/thread/thread.hpp>
#include <boost/random.hpp>
#include "../src/data/GameDefine.h"
#include <boost/smart_ptr/scoped_array.hpp>

#define Random(x) (rand() % x) //通过取余取得指定范围的随机数

void StartClient()
{
	try
	{
		CMyClient::StartClient();
	}
	catch (...)
	{
		std::cout << "please input parameter(port,is show log),like this : *.exe 8092 1" << std::endl;//请输入参数
	}
}
#define ZeroVar(p) ZeroMemory( &p, sizeof( p ) )

int main(int argc, char *argv[])
{
	MEMORY_CHICK;//内存检测

	boost::thread thrd(&StartClient);
	thrd.yield();

	boost::mt19937 rng((boost::uint32_t)time(0));  
	boost::uniform_int<> ui(0, 10000);  
	int id = ui(rng);
	char ccc[256];
	ZeroVar(ccc);
	sprintf_s(ccc,256,"谢小%d",id);
	std::string str(ccc);

	Sleep(1000);
	MsgInfo info;
	info.m_head.unMsgID = MSG_LOGIN_ID;
	info.m_user.m_id = id;
	info.m_user.m_level = 33;
	info.m_user.m_vipLevel = 30;
	info.m_user.m_name.resize(str.size(),0); 
	memcpy(&info.m_user.m_name[0],str.c_str(),str.length());
	boost::scoped_array<char> _buffer;
	CMyAsioTools tools;
	MY_UINT32 len = tools.Serializing(info,_buffer);
	CMyClient::WriteSomeSomething(_buffer,len);

	while(true)
	{
		Sleep(1000);
		sprintf_s(ccc,256,"%d:哈哈哈哈",id);
		str = ccc;
		info.m_head.unMsgID = MSG_SEND_FROM_MSG_ID;
		info.text.resize(str.size(),0); 
		memcpy(&info.text[0],str.c_str(),str.length());
		MY_UINT32 len = tools.Serializing(info,_buffer);
		CMyClient::WriteSomeSomething(_buffer,len);
	}

	
	while(1)
	{	
		int n =0;
		std::cin>>n;

		if (n == -1)
			break;

		switch(n)
		{
		case 1:
			{
				str = "{\"ID\":1,\"uID\":1,\"name\":\"谢小军\"}";
			}break;
		case 2:
			{
				str = "{\"ID\":2,\"name\":\"谢-小-军\"}";
			}break;
		case 3:
			{
				str = "{\"ID\":3,\"tID\":0,\"text\":\"哈哈哈哈\"}";
			}break;
		}
		//CMyClient::WriteSomeSomething(str);
// 		std::map<std::string,int>::const_iterator c_it = tools.m_opMap.begin();
// 		while(c_it != tools.m_opMap.end())
// 		{
// 			if (boost::iequals(str,c_it->first))
// 			{
// 				CServerConnectionData::instance()->SendAllMessage(str);
// 				break;
// 			}
// 			c_it++;
// 		}
	}

	CMyClient::g_ios.stop();
	thrd.join();
	return 0;
}
