#include "MyTools.h"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/locale.hpp>
#include <boost/xpressive/xpressive.hpp>//动态正则表达式库
#include <memory>
#include <direct.h>
//#define MAX_WAIT_TIME 60
//using namespace boost::xpressive;//正则表达式库

void MyTools::PrintToFile( std::string fname,std::vector<std::string> & prints,bool isClear)
{
	setlocale(LC_ALL, "chs");
	std::string path = fname; // GetModulePath(strF, fname);
	//path = "\\\\QGFPVZ3ZLRZTTEH\\iPad\\TXT\\"+ fname;
	namespace newfs = boost::filesystem;
	newfs::ofstream ofs(path.c_str(),(isClear?(std::ios_base::out|std::ios::trunc):(std::ios_base::app|std::ios::ate)));
	if (!ofs.is_open())
	{
		unsigned int loc = fname.find("/",0);
		if( loc != std::string::npos )
		{
			std::string dir(fname.begin(),fname.begin()+loc);
			_mkdir(dir.c_str());
			std::cout<<"build dir \n";
			PrintToFile(fname,prints,isClear);
			return;
		}
	}

	if (ofs.is_open())//如果打开了
	{
		std::vector<std::string>::const_iterator it = prints.begin();
		while(it != prints.end())
		{
			ofs<<*it<<std::endl;
			it++;
		}
		ofs.close();
	}
	else//没有打开
		assert(false);
}

bool MyTools::ReadFromFile( std::string fname,std::vector<std::string> & reads, std::string strF)
{
	reads.clear();//清除老元素

	setlocale(LC_ALL, "chs");
	std::string path = fname;
	namespace newfs = boost::filesystem;
	newfs::ifstream ifs(path.c_str(),std::ios::in);
	std::string str;
	if (ifs.is_open())//如果打开了
	{
		while(!ifs.eof())
		{
			std::getline(ifs,str);
			if (str.length() >0)//空行取消存取
				reads.push_back(str);
		}
		ifs.close();

		return true;
	}
	else//没有打开
		return false;

}

std::string MyTools::FindFirstStr( std::string & strSrc,int n,bool isBlank )
{
	boost::iterator_range<std::string::iterator> ir;
	ir = boost::find_head(strSrc,n);
	std::string str = std::string(ir.begin(),ir.end());
	if (!isBlank)
	{
		boost::trim_left(str);
		boost::trim_right(str);
	}
	return str;
}

std::string MyTools::FindLastStr( std::string & strSrc,int n,bool isBlank )
{
	boost::iterator_range<std::string::iterator> ir;
	ir = boost::find_tail(strSrc,n);
	std::string str = std::string(ir.begin(),ir.end());
	if (!isBlank)
	{
		boost::trim_left(str);
		boost::trim_right(str);
	}
	return str;
}

std::string MyTools::SplitString(std::string str, unsigned int nsplit /*= 4*/, const std::string addStr /*= ","*/)
{
	std::string strTemp(str.rbegin(),str.rend());
	std::string strResult = "";
	int n = 0;
	while(true)
	{
		n = (strTemp.length() > nsplit) ? nsplit:strTemp.length();
		strResult.append(FindFirstStr(strTemp, n, true));
		strTemp = FindLastStr(strTemp,strTemp.length() - n,true);
		if (strTemp.length() != 0)
			strResult.append(addStr);
		else
			break;
	}
	return std::string(strResult.rbegin(), strResult.rend());
}

int MyTools::Get_filenames( const std::string& dir, std::vector<std::string>& filenames,bool isSubDir /*= true */,bool isImage /*= false*/ )
{
	filenames.clear();
	boost::filesystem::path path(dir);  
	if (!boost::filesystem::exists(path))  
	{ 
		boost::filesystem::create_directories(path);//创建目录	
		//boost::filesystem::create_directory(path);//创建目录(不能创建数型目录)	
		return -1;
	}  

	boost::filesystem::directory_iterator end_iter;  
	for (boost::filesystem::directory_iterator iter(path); iter!=end_iter; ++iter)  
	{  
		if (boost::filesystem::is_regular_file(iter->status()))  
		{
			if (!isImage || boost::icontains(".JPEG.JPG.TIFF.TIF.BMP.GIF.PNG",iter->path().extension().string()))
				filenames.push_back(iter->path().filename().string());  
		}  
		else if (boost::filesystem::is_directory(iter->status()))  
		{ 
			if (isSubDir)//查找子目录
			{
				Get_filenames(iter->path().string(), filenames, isSubDir,isImage); 
			}
			else
			{
				//boost::filesystem::remove(iter->path());//删除文件
				boost::filesystem::remove_all(iter->path());//删除目录
			} 
		}  
	}  

	return filenames.size();  
}

bool MyTools::DeleteFile( const std::string & strPath )
{
	boost::filesystem::path path(strPath);
	if (boost::filesystem::exists(path))  
		boost::filesystem::remove(path);//删除文件

	return true;
}

bool MyTools::FileIsExist( const std::string & strPath )
{
	boost::filesystem::path path(strPath);
	return boost::filesystem::exists(path);
}

std::string MyTools::GetUtf8(const std::string & str)
{
	return boost::locale::conv::between(str,"UTF-8","GBK");
}

std::string MyTools::GetGBK(const std::string & str)
{
	return boost::locale::conv::between(str, "GBK", "UTF-8");
}

std::vector<std::string> MyTools::SplitStringUtf8(const std::string & str,unsigned int len)
{
	int size = str.length();
	std::string strTemp;
	std::vector<std::string> verStr;
	int n = 0;
	int n1 = 0;
	int i = 0;
	while (i<size)
	{
		if (str[i] > 0)//直接添加
		{
			strTemp.append(1,str[i]);
			i++;
			n1++;
		}
		else
		{
			strTemp.append(str.begin() + i, str.begin() + i + 3);
			i += 3;
			n++;
		}

		
		if ((n + (n1+1)/2 ) == len)
		{
			verStr.push_back(strTemp);
			strTemp.clear();
			n = 0;
			n1 = 0;
		}
	}

	if (strTemp.length() > 0)
		verStr.push_back(strTemp);

	return verStr;
}

std::string MyTools::BuildString(const std::string & str0, const std::string & str1)
{
	std::string str = "";
	str.append(str0);
// 	int n = 5 - str0.length()/3;
// 	str.append(n,' ');

//	n = str1.length();
// 	if (n < 6)
// 		str.append("[");
	str.append("["+str1+"]");

	return str;
}

std::vector<std::string> MyTools::RegexAnalysis(const std::string & str, const std::string & strRegex)
{
	boost::xpressive::cregex _reg = boost::xpressive::cregex::compile(str, boost::xpressive::icase);//更新的正则表达式不会变的，故为了加快速度，icase表示大小写不敏感
	boost::xpressive::cmatch what;//匹配结果列表
	std::vector<std::string> ver;
	try{
		boost::xpressive::cregex_iterator pos(str.c_str(),str.c_str() + str.length()+1, _reg);
		boost::xpressive::cregex_iterator end;
		while (pos != end)
		{
			ver.push_back((*pos)[0]);
 		}
	}
	catch (boost::xpressive::regex_error e){
		//printf("regex error by compile :%d", e.code());
	}

	return ver;
}
