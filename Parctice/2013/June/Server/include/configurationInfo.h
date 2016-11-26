/******************************************
	文件类型：头文件
	
	文件名称：configuration.h
	
	文件作用：设置和获取角色对应挂机和快捷栏数据;
*******************************************/

#ifndef CONFIGURATION_INFO_H
#define CONFIGURATION_INFO_H
//设置角色对应挂机数据；
void setHangUpInfo(char* buffers);

//获取角色对应挂机数据；
void getHangUpInfo(char* buffers);

//获取角色快捷栏数据；
void getShortCutInfo(char* buffers);

//设置角色快捷栏数据；
void setShortCutInfo(char* buffers);

//设置系统设置数据；
void setSystemDataInfo(char* buffers);

//获取系统设置数据；
void getSystemDataInfo(char* buffers);

//设置操作设置数据；
void setOperationDataInfo(char* buffers);

//获取操作设置数据；
void getOperationDataInfo(char* buffers);

//获取角色金币数据；
void getGoldInfo(char* buffers);

#endif