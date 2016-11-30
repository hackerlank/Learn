/********************************************************************
    创建时间：    2015/04/17  14:36:17 
    文件名：      DropCurrencyRes.h
    作者：        
    
    功能:		1.用于开奖时出贝克的资源信息提取及管理
				2.支持开奖时货币类型及相关
                
    说明:		1. 
                2. 
*********************************************************************/
#ifndef __DROPCURRENCY_H_
#define __DROPCURRENCY_H_
#include "RewardRes.h"

class CDropCurrencyRes : public RewardRes
{
public:
	CDropCurrencyRes(ACE_UINT32 unType);
	virtual ~CDropCurrencyRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	//ACE_UINT32 m_unCountDown;
private:
	
};

#endif