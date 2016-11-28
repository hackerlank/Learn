/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    MailProt.h
//  Purpose:      邮件CenterServer通讯协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include <vector>
#include <string>
#include <memory>
#include "ServerDefine.h"
#include "Archive.h"
#ifdef PROT_USE_XML
#include "tinyxml.h"
#endif
#include "ItemProt.h"

namespace NMailProt
{

/////////////////////以下为类型定义/////////////////////
//邮件状态
enum EMailQueryType
{
	eQueryNew = 0, //新邮件
	eQueryReaded = 1, //已读
	eQueryTotal = 2, //全部
	eQueryPerson = 3, //个人
	eQuerysysTem = 4, //系统
	eQueryAttch //附件
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMailQueryType);
bool EnumStrToVal(const char*, EMailQueryType&);
#endif //PROT_USE_XML

//邮件状态
enum EMailState
{
	eStateNew = 0, //新邮件
	eStateReaded = 1, //已读
	eStateDelete = 2 //已删
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMailState);
bool EnumStrToVal(const char*, EMailState&);
#endif //PROT_USE_XML

//邮件状态
enum EMailErrorResult
{
	EMail_SendOk = 1, //发送成功
	EMail_SendFail = 2, //发送失败
	EMail_DeleteOk = 3, //删除成功
	EMail_DeleteFail = 4, //删除失败
	EMail_OverMaxCount = 5 //超过最大上限
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMailErrorResult);
bool EnumStrToVal(const char*, EMailErrorResult&);
#endif //PROT_USE_XML

//邮件类型
enum EMailType
{
	EMAILTYPE_NORMAL = 0, //普通邮件
	EMAILTYPE_SYSTEM = 1 //系统邮件
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMailType);
bool EnumStrToVal(const char*, EMailType&);
#endif //PROT_USE_XML

//附件类型
enum EMailAttachType
{
	ATTACH_ITEM = 0, //有模板物品
	ATTACH_INSTANCE = 1, //有实例物品
	ATTACH_MAX = 255 //不当位处理，作为附件已经领取的特殊标记
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMailAttachType);
bool EnumStrToVal(const char*, EMailAttachType&);
#endif //PROT_USE_XML

//附件提取结果
enum EMailDRawResult
{
	DRAW_SUC = 0, //提取成功
	PACK_FULL = 1 //包裹满
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMailDRawResult);
bool EnumStrToVal(const char*, EMailDRawResult&);
#endif //PROT_USE_XML
const char* GetDescription(EMailDRawResult);

//结构体：SMailBaseAttachment的继承体系类型
enum EType_SMailBaseAttachment
{
	eType_SMailBaseAttachment, //类型：SMailBaseAttachment
	eType_SItemAttachment, //类型：SItemAttachment
	eType_SItemBaseCT //类型：SItemBaseCT
};

//系统邮件标题，及其内容
struct SysMailSendTxt
{
	UINT32 dwstrMsgID; //消息ID
	TVecString vecParam; //参数列表

	SysMailSendTxt();
	SysMailSendTxt(UINT32 dwstrMsgID_, const TVecString& vecParam_);
};

typedef std::vector<SysMailSendTxt> TVecSysMailSendTxt;

//邮件摘要列表
struct SMailSummary
{
	UINT64 uMailID; //邮件ID
	EMailType eMailType; //邮件类型
	EMailState eMailState; //邮件状态
	UINT32 uSendTime; //邮件发送时间
	UINT8 byHasAttachment; //0:没有   1:有
	std::string strTitle; //邮件标题
	std::string strSendName; //发送者

	SMailSummary();
	SMailSummary(UINT64 uMailID_, EMailType eMailType_, EMailState eMailState_, UINT32 uSendTime_, UINT8 byHasAttachment_, 
		const std::string& strTitle_, const std::string& strSendName_);
#ifdef __GNUG__
	SMailSummary(const SMailSummary& src) = default; //默认拷贝构造函数
	SMailSummary& operator=(const SMailSummary& rhs) = default; //默认赋值操作符
#endif
	SMailSummary(SMailSummary&& src); //转移构造函数
	SMailSummary& operator=(SMailSummary&& rhs); //转移赋值操作符
};

typedef std::vector<SMailSummary> TVecMailList;

//道具格式
struct SMailItemInfo
{
	UINT64 qwInstID; //道具类型ID
	UINT32 wItemID; //物品模板
	NItemProt::EItemQuality eItemQuelity; //物品品质
	UINT32 wCount; //道具数量
	NItemProt::EBindType eBindType; //绑定类型
	UINT8 byExpired; //是否时效，>0 时效物品
	UINT32 dwExpireTime; //过期时间
	UINT64 qwOPID; //操作ID

	SMailItemInfo();
	SMailItemInfo(UINT64 qwInstID_, UINT32 wItemID_, NItemProt::EItemQuality eItemQuelity_, UINT32 wCount_, NItemProt::EBindType eBindType_, 
		UINT8 byExpired_, UINT32 dwExpireTime_, UINT64 qwOPID_);
};

typedef std::vector<SMailItemInfo> TVecMailItemInfo;

//邮件附件
struct SMailBaseAttachment
{
	SMailBaseAttachment();
	virtual ~SMailBaseAttachment() { }
	DEF_NEW_DELETE(SMailBaseAttachment); //使用对象池
	virtual EType_SMailBaseAttachment GetClassType() const { return eType_SMailBaseAttachment; }
};

typedef std::shared_ptr<SMailBaseAttachment> SMailBaseAttachmentPtr;
typedef std::weak_ptr<SMailBaseAttachment> SMailBaseAttachmentWtr;
typedef std::vector<SMailBaseAttachmentPtr> TVecMailAttachment;

//父类：SMailBaseAttachment的辅助结构体
struct SMailBaseAttachment_Wrapper
{
	SMailBaseAttachmentPtr ptr;
	SMailBaseAttachment_Wrapper(const SMailBaseAttachmentPtr& ptr_ = NULL) : ptr(ptr_) { }
};

//物品附件
struct SItemAttachment : public SMailBaseAttachment
{
	TVecMailItemInfo vecItemInfo; //物品

	SItemAttachment();
#ifdef __GNUG__
	SItemAttachment(const SItemAttachment& src) = default; //默认拷贝构造函数
	SItemAttachment& operator=(const SItemAttachment& rhs) = default; //默认赋值操作符
#endif
	SItemAttachment(SItemAttachment&& src); //转移构造函数
	SItemAttachment& operator=(SItemAttachment&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SItemAttachment); //使用对象池
	virtual EType_SMailBaseAttachment GetClassType() const { return eType_SItemAttachment; }
};

typedef std::shared_ptr<SItemAttachment> SItemAttachmentPtr;
typedef std::weak_ptr<SItemAttachment> SItemAttachmentWtr;

//物品附件:具体物品对象
struct SItemBaseCT : public SMailBaseAttachment
{
	NItemProt::TVecItem vecItems; //物品

	SItemBaseCT();
#ifdef __GNUG__
	SItemBaseCT(const SItemBaseCT& src) = default; //默认拷贝构造函数
	SItemBaseCT& operator=(const SItemBaseCT& rhs) = default; //默认赋值操作符
#endif
	SItemBaseCT(SItemBaseCT&& src); //转移构造函数
	SItemBaseCT& operator=(SItemBaseCT&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SItemBaseCT); //使用对象池
	virtual EType_SMailBaseAttachment GetClassType() const { return eType_SItemBaseCT; }
};

typedef std::shared_ptr<SItemBaseCT> SItemBaseCTPtr;
typedef std::weak_ptr<SItemBaseCT> SItemBaseCTWtr;

//邮件详细信息
struct SMailDetail
{
	UINT64 qwMailID; //邮件ID
	EMailState eMailState; //邮件状态
	UINT32 dwSendTime; //邮件发送时间
	UINT8 byGeted; //255表示有附件，并且已经领取，其他为按位表示有附件的类型
	EMailType eMailType; //邮件类型
	TVecMailAttachment vecMailAttachment; //附件
	std::string strTitle; //邮件标题
	std::string strSendName; //发送者
	std::string strMessage; //信息

	SMailDetail();
#ifdef __GNUG__
	SMailDetail(const SMailDetail& src) = default; //默认拷贝构造函数
	SMailDetail& operator=(const SMailDetail& rhs) = default; //默认赋值操作符
#endif
	SMailDetail(SMailDetail&& src); //转移构造函数
	SMailDetail& operator=(SMailDetail&& rhs); //转移赋值操作符
};

typedef std::vector<SMailDetail> TVecMailDetail;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SysMailSendTxt&);
COutArchive& operator<<(COutArchive&, const SysMailSendTxt&);

CInArchive& operator>>(CInArchive&, SMailSummary&);
COutArchive& operator<<(COutArchive&, const SMailSummary&);

CInArchive& operator>>(CInArchive&, SMailItemInfo&);
COutArchive& operator<<(COutArchive&, const SMailItemInfo&);

CInArchive& operator>>(CInArchive&, SMailBaseAttachment&);
COutArchive& operator<<(COutArchive&, const SMailBaseAttachment&);
CInArchive& operator>>(CInArchive&, SMailBaseAttachment_Wrapper&);
COutArchive& operator<<(COutArchive&, const SMailBaseAttachment_Wrapper&);
CInArchive& operator>>(CInArchive&, TVecMailAttachment&);
COutArchive& operator<<(COutArchive&, const TVecMailAttachment&);

CInArchive& operator>>(CInArchive&, SItemAttachment&);
COutArchive& operator<<(COutArchive&, const SItemAttachment&);

CInArchive& operator>>(CInArchive&, SItemBaseCT&);
COutArchive& operator<<(COutArchive&, const SItemBaseCT&);

CInArchive& operator>>(CInArchive&, SMailDetail&);
COutArchive& operator<<(COutArchive&, const SMailDetail&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SysMailSendTxt&);
bool ToXML(const SysMailSendTxt&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSysMailSendTxt&);
bool VectorToXML(const TVecSysMailSendTxt&, TiXmlElement&);

bool FromXML(TiXmlElement&, SMailSummary&);
bool ToXML(const SMailSummary&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMailList&);
bool VectorToXML(const TVecMailList&, TiXmlElement&);

bool FromXML(TiXmlElement&, SMailItemInfo&);
bool ToXML(const SMailItemInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMailItemInfo&);
bool VectorToXML(const TVecMailItemInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SMailBaseAttachment&);
bool ToXML(const SMailBaseAttachment&, TiXmlElement&);
bool SuperFromXML(TiXmlElement&, SMailBaseAttachmentPtr&);
bool SuperToXML(const SMailBaseAttachment&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMailAttachment&);
bool VectorToXML(const TVecMailAttachment&, TiXmlElement&);

bool FromXML(TiXmlElement&, SItemAttachment&);
bool ToXML(const SItemAttachment&, TiXmlElement&);

bool FromXML(TiXmlElement&, SItemBaseCT&);
bool ToXML(const SItemBaseCT&, TiXmlElement&);

bool FromXML(TiXmlElement&, SMailDetail&);
bool ToXML(const SMailDetail&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMailDetail&);
bool VectorToXML(const TVecMailDetail&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NMailProt
