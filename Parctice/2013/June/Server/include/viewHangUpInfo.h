/******************************************
	文件类型：头文件
	
	文件名称：viewHangUpInfo.h
	
	文件作用：设置和获取角色对应挂机数据;
*******************************************/
#ifndef VIEW_HANG_UP_INFO_H
#define VIEW_HANG_UP_INFO_H
//设置角色对应挂机数据；
void setHangUpInfo(char* buffers);

//获取角色对应挂机数据；
void getHangUpInfo(char* buffers);

//获取角色快捷栏数据；
void getShortCutInfo(char* buffers);

//设置角色快捷栏数据；
void setShortCutInfo(char* buffers);

#endif