#include "luaFun.h"
#include <iostream>
using namespace std;

int luaAdd(lua_State *l,const int x,const int y)
{
    //lua函数名字
    lua_getglobal(l,"add");
    //塞入参数1
    lua_pushnumber(l,x);
    //塞入参数2
    lua_pushnumber(l,y);
    //调用lua函数,2个参数,1个返回值
    lua_call(l,2,1);
    //获得返回结果
    int sum = (int)lua_tonumber(l,-1);
    //把返回结果出栈
    lua_pop(l,-1);
    return sum;
}

int cAdd(lua_State *l)
{
    int x = lua_tonumber(l,-1);
    int y = lua_tonumber(l,-2);
    lua_pushnumber(l,x+y);
    return 1;
}

int main(int argc,char *argv[])
{
    //初始化lua
    lua_State *l = lua_open();
    //加载lua的lib文件
    luaopen_base(l);
    //加载lua文件
    luaL_dofile(l,"./lua/add.lua");
    std::cout << "sum :" << luaAdd(l,10,15) << std::endl;

    //注册在lua中使用的c函数  
    lua_pushcfunction(l,cAdd); 
    //绑定到lua中的名字cAdd
    lua_setglobal(l,"cAdd");

    //调用lua中的mysum函数，该函数调用本程序中定义的cAdd函数实现加法  
    lua_getglobal(l,"myadd");           
    lua_pushnumber(l,2);  
    lua_pushnumber(l,3);  
    int ret = lua_pcall(l,2,1,0);  
    if(ret != 0)
    {
        std::cout << "err:" << lua_tostring(l,-1);
    }
    else
    {
        int sum = (int)lua_tonumber(l,-1); 
        std::cout << "mysum :" << sum << std::endl;
    }
    lua_pop(l,-1);

    //关闭lua
    lua_close(l);
    return 0;
}

