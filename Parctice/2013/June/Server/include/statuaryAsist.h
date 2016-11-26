/************************************************************
	文件名：statuaryAsist.h
	文件作用：雕像相关辅助函数
	作者：chenzhen
	创建日期：2013.03.04
************************************************************/


#ifndef STATUARY_ASIST_H
#define STATUARY_ASIST_H

/*开启服务器时，从缓存里面提取雕像信息*/
void openServerStatuaryMsg(void);

/*关闭服务器时，往缓存里面存雕像信息*/
void closeServerStatuaryMsg(void);

/*初始化雕像对应雕像像列表，就是雕像缓存的键*/
void initStrtuaryTitleIdList(void);

/*测试存*/
void testInStatuary(void);

/*测试取*/
void testOutStatuary(void);

/*塑造雕像*/
void setUpStatuary(char* heroId,char* titleId);

/*摧毁雕像*/
void destoryStatuary(char* titleId);

/*测试用*/
void destroyAllStatuary(void);

/*测试雕像坐标点*/
void printStatuaryPt(void);

#endif   