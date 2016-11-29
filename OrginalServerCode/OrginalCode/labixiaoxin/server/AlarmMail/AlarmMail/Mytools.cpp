#include "Mytools.h"
#include <fstream> 
#include <iostream>
#include "..\include\json\MyJson.h"
#include <Windows.h>

CMytools::CMytools(void)
{
}

CMytools::~CMytools(void)
{
}

bool CMytools::ReadText()
{
	//如果是个很大的多行存储的文本型文件可以这么读：  
	char buf[1024];                //临时保存读取出来的文件内容  
	std::string str;  
	std::ifstream infile;
	char chpath[MAX_PATH];  
	GetModuleFileNameA(NULL,(LPSTR)chpath,sizeof(chpath));  
	std::string strPath(chpath);
	int loc = strPath.rfind('\\');
	if (loc != std::string::npos)
	{
		strPath = strPath.substr(0,loc+1);
	}
	strPath += "mailConfig.json";

	infile.open(strPath.c_str());  
	if(infile.is_open())          //文件打开成功,说明曾经写入过东西  
	{  
		while(infile.good() && !infile.eof())  
		{  
			memset(buf,0,1024);  
			infile.getline(buf,1024); 
			str.append(buf); 
			str.append("\n");
		}  
		infile.close();  

		return ParseJson(str);
	}  
	else
	{
		std::cout<<"查找mailConfig.json文件失败"<<std::endl;
		return false;
	}
}

bool CMytools::ParseJson( const std::string & str )
{
	//m_verTOaddress.clear();
	//std::vector<std::string>().swap(m_verTOaddress);
	CMyJson m_myjson;
	CMyJson::JsonRoot json;
	m_myjson.InitJson(str,json);
	FROMaddress = m_myjson.GetStrValue(json,"FROMaddress");
	FROPassword = m_myjson.GetStrValue(json,"FROPassword");
	Subject = m_myjson.GetStrValue(json,"Subject");
	Message = m_myjson.GetStrValue(json,"Message");
	server = m_myjson.GetStrValue(json,"server");

	for (int i=0;i<json["TOaddress"].size();i++)
	{
		m_verTOaddress.push_back(json["TOaddress"][i].asCString());
	}


	if (m_verTOaddress.size()<1)
		return false;
	else
		return true;
}
