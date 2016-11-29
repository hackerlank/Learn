#include <iostream>  
#include "..\include\jwsmtp.h" 
#include "Mytools.h"

void printErrorInfo(int errorid)
{
	switch(errorid)
	{
	case  500:
		{
			std::cout<<"可识别（此错误也包括命令行过长）"<<std::endl;
		}break; 
	case  501:
		{
			std::cout<<"参数格式错误"<<std::endl;
		}break; 
	case  502:
		{
			std::cout<<"命令不可实现 "<<std::endl;
		}break; 

	case  503:
		{
			std::cout<<"错误的命令序列"<<std::endl;
		}break; 

	case  504:
		{
			std::cout<<"命令参数不可实现"<<std::endl;
		}break; 

	case  211:
		{
			std::cout<<"系统状态或系统帮助响应"<<std::endl;
		}break; 

	case  214:
		{
			std::cout<<"帮助信息"<<std::endl;
		}break; 

	case  220:
		{
			std::cout<<" 服务就绪"<<std::endl;
		}break; 

	case  221:
		{
			std::cout<<"服务关闭传输信道"<<std::endl;
		}break; 

	case  421:
		{
			std::cout<<"服务未就绪，关闭传输信道（当必须关闭时，此应答可以作为对任何命令的响应）"<<std::endl;
		}break; 

	case  250:
		{
			std::cout<<"要求的邮件操作完成"<<std::endl;
		}break; 

	case  251:
		{
			std::cout<<"用户非本地，将转发向"<<std::endl;
		}break; 

	case  450:
		{
			std::cout<<"要求的邮件操作未完成，邮箱不可用（例如，邮箱忙）"<<std::endl;
		}break; 

	case  550:
		{
			std::cout<<"要求的邮件操作未完成，邮箱不可用（例如，邮箱未找到，或不可访问）"<<std::endl;
		}break; 
	case  451:
		{
			std::cout<<"放弃要求的操作；处理过程中出错  "<<std::endl;
		}break; 
	case  551:
		{
			std::cout<<"用户非本地，请尝试"<<std::endl;
		}break; 
	case  452:
		{
			std::cout<<"系统存储不足，要求的操作未执行"<<std::endl;
		}break; 
	case  552:
		{
			std::cout<<"过量的存储分配，要求的操作未执行"<<std::endl;
		}break; 
	case  553:
		{
			std::cout<<" 邮箱名不可用，要求的操作未执行（例如邮箱格式错误）"<<std::endl;
		}break; 
	case  354:
		{
			std::cout<<"开始邮件输入，以.结束"<<std::endl;
		}break; 
	case  554:
		{
			std::cout<<"操作失败"<<std::endl;
		}break; 
	case  535:
		{
			std::cout<<"用户验证失败  "<<std::endl;
		}break; 
	case  235:
		{
			std::cout<<"用户验证成功"<<std::endl;
		}break; 
	case  334:
		{
			std::cout<<"等待用户输入验证信"<<std::endl;
		}break; 
	default:
		{
			std::cout<<"未知错误"<<std::endl;
		}break;
	}
}
//注意utf8编码
int main(int argc, char* argv[])  
{  
	CMytools tools;
	if (tools.ReadText())
	{
		jwsmtp::mailer mail(tools.m_verTOaddress.at(0).c_str()/*接收者*/
			,tools.FROMaddress.c_str()/*发送者*/
			,tools.Subject.c_str()/*"这里填写邮件标题"*/
			,tools.Message.c_str()
			,tools.server.c_str()
			,jwsmtp::mailer::SMTP_PORT, false);  

		//添加多个接收者
		for (int i=1;i<tools.m_verTOaddress.size();i++)
		{
			mail.addrecipient(tools.m_verTOaddress.at(i).c_str());
		}
		// 	mail.addrecipient("testjwstmp@163.com");  
		// 	mail.addrecipient("testjwstmp@gmail.com");  
		// 	mail.addrecipient("testjwstmp@qq.com");  
		// 
		// 	//添加HTML的发送内容，它会替换构造函数中的“这里填写邮件内容”  
		// 	mail.setmessageHTML(html);  

		//经过测试，163支持的auth认证是PLAIN模式  
		mail.authtype(jwsmtp::mailer::PLAIN);  

		//这里输入认证用户名，注意哦，需要是***@163.com的用户名  
		mail.username(tools.FROMaddress.c_str());  
		//这里输入密码  
		mail.password(tools.FROPassword.c_str());
		mail.send(); // 这里发送邮件，需要注意的是，这里是同步模式哦！
		std::string str = mail.response();
		int errorinfo = atoi(str.substr(0,3).c_str());
		printErrorInfo(errorinfo);

		std ::cout << mail.response() << std::endl;//这里返回是否成功，250代表发送邮件成功; 
	}

	Sleep(10000);
	
	//system("pause");  
	return 0;  
}  

/*
附上发送Email的返回码

邮件服务返回代码含义  
500   格式错误，命令不可识别（此错误也包括命令行过长）  
501   参数格式错误  
502   命令不可实现  
503   错误的命令序列  
504   命令参数不可实现  
211   系统状态或系统帮助响应  
214   帮助信息  
220     服务就绪  
221     服务关闭传输信道  
421     服务未就绪，关闭传输信道（当必须关闭时，此应答可以作为对任何命令的响应）  
250   要求的邮件操作完成  
251   用户非本地，将转发向  
450   要求的邮件操作未完成，邮箱不可用（例如，邮箱忙）  
550   要求的邮件操作未完成，邮箱不可用（例如，邮箱未找到，或不可访问）  
451   放弃要求的操作；处理过程中出错  
551   用户非本地，请尝试  
452   系统存储不足，要求的操作未执行  
552   过量的存储分配，要求的操作未执行  
553   邮箱名不可用，要求的操作未执行（例如邮箱格式错误）  
354   开始邮件输入，以.结束  
554   操作失败  
535   用户验证失败  
235   用户验证成功  
334   等待用户输入验证信
*/