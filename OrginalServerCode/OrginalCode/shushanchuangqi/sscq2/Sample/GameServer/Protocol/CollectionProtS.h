
#pragma once
#include "CollectionProtSvr.h"

using namespace NCollectionProt;

class CCollectionProtS : public CCollectionProtSvr
{
public:
	//接收：获取成就信息
	virtual bool OnRecv_GeCollectionInfo(
		shared_func<SGeCollectionInfoAck>& fnAck //返回回调函数
	);


private:
};

extern CCollectionProtS g_CollectionProtS;
