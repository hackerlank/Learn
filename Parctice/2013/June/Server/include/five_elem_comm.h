/****************************************************************
 * Filename: five_elem_comm.h
 * 
 * Description: 五行系统与客户端的通信
 *
 * Original Author : bison, 2012-7-23
 *
 ****************************************************************/
#include<string>
using namespace std;

//开启人物五行
void openFiveElemComm(char *buffer);
//更改五行属性的通信
void changFiveElemComm(char *buffer);
//使用五行丹药提升五行等级
void useFiveElemGoodsComm(char *buffer);
//获取五行数据
void viewFiveElemComm(char *buffer);