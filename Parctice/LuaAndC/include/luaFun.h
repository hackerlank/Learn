extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "stdio.h"
}

#define err_exit(num,fmt,args)\
    do\
    {\
        printf("[%s:%d]"fmt"\n",__FILE__,__LINE__,##args);\
        exit(num);\
    } while(0)  

#define err_return(num,fmt,args)\
    do\
    {\
        printf("[%s:%d]"fmt"\n",__FILE__,__LINE__,##args);\
        return(num);\
    } while(0)  
 
int luaAdd(lua_State *l,const int x,const int y);
int cAdd(lua_State *l);
 
