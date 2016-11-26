/************************************************************
	文件名：cpy_series_command_function.h
	文件作用：处理副本相关命令的系列处理函数
	作者：chenzhen
	创建日期：2012.06.21
************************************************************/


#ifndef CPY_SERISE_COMMAND_FUNCTION_H
#define CPY_SERISE_COMMAND_FUNCTION_H

/*进副本*/
void entCpy(char *buffer);    

/*进副本场景*/
void entCpyNextMap(char *buffer);  

/*退出副本场景*/
void exitCpy(char *buffer);  

/*场景回应函数*/
void  enterScenResponse(char *buffer);

/*使用道具进副本*/
void enterCpyByTool(char *buffer);

/*面板请求处理函数*/
void panelResponse(char *buffers);

/*点菜*/
void olderDish(char *buffer);

/*玩家点帮派盛宴*/
void pickGuildFeast(char *buffer);

/*进入帮派大本营*/
void enterCampRom(char *buffer);

/*进入黑木崖副本*/
void enterTowerLayerCopy(char *buffer);

/*开始扫荡青衣楼*/
void swapTowerLayerCopy(char *buffer);

/*刷新青衣楼副本*/
void brushTower(char *buffer);
#endif   