#pragma once
#include <string>
#include <vector>

class CMytools
{
public:
	CMytools(void);
	~CMytools(void);
public:
	bool ReadText();
	bool ParseJson(const std::string & str);

	std::string FROMaddress;//发送者
	std::string FROPassword;//密码
	std::string Subject;//邮件标题
	std::string Message;//邮件内容
	std::string server;//发送邮件服务器
	std::vector<std::string> m_verTOaddress;//接收者
};
