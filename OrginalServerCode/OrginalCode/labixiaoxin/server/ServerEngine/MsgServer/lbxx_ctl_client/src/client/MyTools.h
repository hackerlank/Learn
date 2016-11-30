#ifndef MYTOOLS_H_
#define MYTOOLS_H_
#include <boost\algorithm\string.hpp>
#include <vector>

//全局函数 初始化 所有
class MyTools
{
public:
  /*
  fname:当前可执行路径里文件夹下data目录下文件名
  prints：要打印的值，一个元素（std::string）代表要打印的一行数据
  isClear:是否清除数据
  */ 
  static void PrintToFile(std::string fname,std::vector<std::string> & prints,bool isClear=true);//打印结果

  /*
  fname:当前可执行路径里文件夹下data目录下文件名
  reads：读出存储的位置，一行文件内容存到一个boost::string里
  */
  static bool ReadFromFile(std::string fname,std::vector<std::string> & reads);//读如数据
  
public://ini 配置文件相关
	static std::string g_strServerIP;
	
	static std::string GetStringConfig(const char * tag);

	static void SetStringConfig(const char * tag,std::string str);
};

#endif

