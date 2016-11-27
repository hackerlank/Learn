#ifndef BASE_FUN_H
#define BASE_FUN_H
#include<string.h>

#ifndef DELETE
#define DELETE(x)\
if( (x) )\
{\
	delete (x);\
	(x) = NULL;\
}
#endif

#ifndef DELETE_VEC
#define DELETE_VEC(x)\
if( (x) )\
{\
	delete [] (x);\
	(x) = NULL;\
}
#endif

#ifndef bcopy
#define bcopy(src,des,desSize)\
{\
	memcpy( (des),(src),(desSize));\
}
#endif

#ifndef bzero
#define bzero(ptr,size)\
{\
	memset( (ptr),0,(size) );\
}
#endif

#ifndef CheckConditonVoid
#define CheckConditonVoid( cond ) \
do{\
	if( !(cond) )\
		return;\
}while(0)
#endif

#ifndef CheckConditonReturn
#define CheckConditonReturn( cond,ret ) \
do{\
	if( !(cond) )\
		return ret;\
}while(0)
#endif

#ifndef LogCheckConditionOnly
#define LogCheckConditionOnly( cond,msg,... )\
do{\
	if( !(cond) )\
	{\
		Global::logger->debug( msg,##__VA_ARGS__ );\
	}\
}while(0)
#endif

#ifndef LogInfoCheckConditionOnly
#define LogInfoCheckConditionOnly( cond,msg,... )\
do{\
	if( !(cond) )\
	{\
		Global::logger->info( msg,##__VA_ARGS__ );\
	}\
}while(0)
#endif


#ifndef LogErrorCheckConditionOnly
#define LogErrorCheckConditionOnly( cond,msg,... )\
do{\
	if( !(cond) )\
	{\
		Global::logger->error( msg,##__VA_ARGS__ );\
	}\
}while(0)
#endif

#ifndef LogCheckCondition
#define LogCheckCondition( cond,ret,msg,... )\
do{\
	if( !(cond) )\
	{\
		Global::logger->debug( msg,##__VA_ARGS__ );\
		return( ret );\
	}\
}while(0)
#endif

#ifndef LogErrorCheckCondition
#define LogErrorCheckCondition( cond,ret,msg,... )\
do{\
	if( !(cond) )\
	{\
		Global::logger->error( msg,##__VA_ARGS__ );\
		return( ret );\
	}\
}while(0)
#endif

#endif

