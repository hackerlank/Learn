/*
***   Using for Output server  diary information Mainly
      eg:
	  Debug("Hero","heroName:%s",hero.getnick());
      This function can use in everywhere;
      
	  if you use the function,you can check the program running path where have a temp directory,
      you can use the tailf to check the log information;
	  eg: tailf log.out
***
*/

#ifndef LOGGER_H
#define LOGGER_H

class Log{
public:
static void Read_log_conf(); //用于扩展
static void Debug(const char* str, const char* format, ...);
static void Error(const char*format,...);
static int Attempt2createdir();
~Log();
private:
char targ[256];
//vector<char*> targ;
};

#endif /* LOGGER_H */
