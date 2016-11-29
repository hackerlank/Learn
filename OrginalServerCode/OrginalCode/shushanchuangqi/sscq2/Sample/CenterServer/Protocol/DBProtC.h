#pragma once
#include "DBProtClt.h"

using namespace NDBProt;

class CDBProtC : public CDBProtClt
{
public:
	//接收：无结果集的返回
	virtual void OnRecv_ResultRet(
		UINT32 dwTransID, //事务的ID
		INT8 byRet, //返回结果：0为成功，1为语法错误，2为参数错误，3为其它错误
		UINT32 dwAffectRow //影响的行数
		);

	//接收：有结果集的返回
	virtual void OnRecv_ResultDataRet(
		UINT32 dwTransID, //事务的ID
		INT8 byRet, //返回结果：0为成功，1为语法错误，2为参数错误，3为其它错误
		const TVecTable& vecTable, //返回的结果表集
		UINT8 byCount //结果表数量
		);

	//接收：增加唯一性名称返回
	virtual void OnRecv_NameAddAck(
		UINT32 dwSessionID, //Session ID
		INT8 byRet //返回结果：0为成功，1为名称重复，2为其它错误
		);

	//接收：删除唯一性名称返回
	virtual void OnRecv_NameDelAck(
		UINT32 dwSessionID, //Session ID
		INT8 byRet //返回结果：0为成功，1为失败
		);

	//接收：更改唯一性名称返回
	virtual void OnRecv_NameModifyAck(
		UINT32 dwSessionID, //Session ID
		INT8 byRet //返回结果：0为成功，1为旧名称不存在，2为新名称重复，3为其它错误
		);
};
