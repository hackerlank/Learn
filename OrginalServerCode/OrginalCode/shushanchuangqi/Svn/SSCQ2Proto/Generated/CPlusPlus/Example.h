/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Example.h
//  Purpose:      通信协议示例
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

namespace NExample
{

/////////////////////以下为类型定义/////////////////////
//枚举类型示例
enum EExTest
{
	eExTest1, //枚举值1
	eExTest2 = 10, //枚举值2
	eExTest3 = 0x7FFF //枚举值3
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EExTest);
bool EnumStrToVal(const char*, EExTest&);
#endif //PROT_USE_XML
const char* GetDescription(EExTest);

//结构体：SExBase的继承体系类型
enum EType_SExBase
{
	eType_SExBase, //类型：SExBase
	eType_SExDerived1, //类型：SExDerived1
	eType_SExDerived2, //类型：SExDerived2
	eType_SExDescend3, //类型：SExDescend3
	eType_SExDescend4 //类型：SExDescend4
};

//前置声明
struct SExBase;
typedef std::shared_ptr<SExBase> SExBasePtr;
typedef std::vector<SExBasePtr> TVecExBase;

//前置声明测试
struct STest
{
	SExBasePtr pBase; //父类指针
	TVecExBase vecBase; //父类指针列表

	STest();
#ifdef __GNUG__
	STest(const STest& src) = default; //默认拷贝构造函数
	STest& operator=(const STest& rhs) = default; //默认赋值操作符
#endif
	STest(STest&& src); //转移构造函数
	STest& operator=(STest&& rhs); //转移赋值操作符
};

//只在服务器生成
struct SServer
{
	UINT32 dwValue; //成员

	SServer();
	SServer(UINT32 dwValue_);
};

//按智能指针传递的结构体
struct SPointer
{
	UINT32 dwValue; //成员

	SPointer();
	SPointer(UINT32 dwValue_);
	DEF_NEW_DELETE(SPointer); //使用对象池
};

typedef std::shared_ptr<SPointer> SPointerPtr;
typedef std::weak_ptr<SPointer> SPointerWtr;

//结构体父类型示例
struct SExBase
{
	UINT32 member1; //成员1
	TVecString vecMember2; //成员2

	SExBase();
	virtual ~SExBase() { }
	DEF_NEW_DELETE(SExBase); //使用对象池
	virtual EType_SExBase GetClassType() const { return eType_SExBase; }
};

typedef std::shared_ptr<SExBase> SExBasePtr;
typedef std::weak_ptr<SExBase> SExBaseWtr;
typedef std::vector<SExBasePtr> TVecExBase;

//父类：SExBase的辅助结构体
struct SExBase_Wrapper
{
	SExBasePtr ptr;
	SExBase_Wrapper(const SExBasePtr& ptr_ = NULL) : ptr(ptr_) { }
};

//结构体子类型1示例
struct SExDerived1 : public SExBase
{
	UINT16 byMember3; //成员3
	INT64 qwMember4; //成员4

	SExDerived1();
	virtual ~SExDerived1() { }
	DEF_NEW_DELETE(SExDerived1); //使用对象池
	virtual EType_SExBase GetClassType() const { return eType_SExDerived1; }
};

typedef std::shared_ptr<SExDerived1> SExDerived1Ptr;
typedef std::weak_ptr<SExDerived1> SExDerived1Wtr;
typedef std::vector<SExDerived1Ptr> TVecExDerived1;

//父类：SExDerived1的辅助结构体
struct SExDerived1_Wrapper
{
	SExDerived1Ptr ptr;
	SExDerived1_Wrapper(const SExDerived1Ptr& ptr_ = NULL) : ptr(ptr_) { }
};

//结构体子类型3示例
struct SExDescend3 : public SExDerived1
{
	SExBasePtr base; //成员5
	SExDerived1Ptr s; //成员6
	TVecExDerived1 vecExDerive; //成员7
	TVecExBase vecExBase; //成员8

	SExDescend3();
#ifdef __GNUG__
	SExDescend3(const SExDescend3& src) = default; //默认拷贝构造函数
	SExDescend3& operator=(const SExDescend3& rhs) = default; //默认赋值操作符
#endif
	SExDescend3(SExDescend3&& src); //转移构造函数
	SExDescend3& operator=(SExDescend3&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SExDescend3); //使用对象池
	virtual EType_SExBase GetClassType() const { return eType_SExDescend3; }
};

typedef std::shared_ptr<SExDescend3> SExDescend3Ptr;
typedef std::weak_ptr<SExDescend3> SExDescend3Wtr;
typedef std::vector<SExDescend3Ptr> TVecExDescend3;

//结构体子类型4示例
struct SExDescend4 : public SExDerived1
{
	UINT16 wMember5; //成员5
	INT64 qwMember6; //成员6
	TVecExDescend3 vecExDesc; //成员7

	SExDescend4();
#ifdef __GNUG__
	SExDescend4(const SExDescend4& src) = default; //默认拷贝构造函数
	SExDescend4& operator=(const SExDescend4& rhs) = default; //默认赋值操作符
#endif
	SExDescend4(SExDescend4&& src); //转移构造函数
	SExDescend4& operator=(SExDescend4&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SExDescend4); //使用对象池
	virtual EType_SExBase GetClassType() const { return eType_SExDescend4; }
};

typedef std::shared_ptr<SExDescend4> SExDescend4Ptr;
typedef std::weak_ptr<SExDescend4> SExDescend4Wtr;
typedef std::vector<SExDescend4Ptr> TVecExDescend4;

//结构体子类型2示例
struct SExDerived2 : public SExBase
{
	double dMember3; //成员3
	bool bMember4; //成员4

	SExDerived2();
	DEF_NEW_DELETE(SExDerived2); //使用对象池
	virtual EType_SExBase GetClassType() const { return eType_SExDerived2; }
};

typedef std::shared_ptr<SExDerived2> SExDerived2Ptr;
typedef std::weak_ptr<SExDerived2> SExDerived2Wtr;
typedef std::vector<SExDerived2Ptr> TVecExDerived2;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, STest&);
COutArchive& operator<<(COutArchive&, const STest&);

CInArchive& operator>>(CInArchive&, SServer&);
COutArchive& operator<<(COutArchive&, const SServer&);

CInArchive& operator>>(CInArchive&, SPointer&);
COutArchive& operator<<(COutArchive&, const SPointer&);

CInArchive& operator>>(CInArchive&, SExBase&);
COutArchive& operator<<(COutArchive&, const SExBase&);
CInArchive& operator>>(CInArchive&, SExBase_Wrapper&);
COutArchive& operator<<(COutArchive&, const SExBase_Wrapper&);
CInArchive& operator>>(CInArchive&, TVecExBase&);
COutArchive& operator<<(COutArchive&, const TVecExBase&);

CInArchive& operator>>(CInArchive&, SExDerived1&);
COutArchive& operator<<(COutArchive&, const SExDerived1&);
CInArchive& operator>>(CInArchive&, SExDerived1_Wrapper&);
COutArchive& operator<<(COutArchive&, const SExDerived1_Wrapper&);
CInArchive& operator>>(CInArchive&, TVecExDerived1&);
COutArchive& operator<<(COutArchive&, const TVecExDerived1&);

CInArchive& operator>>(CInArchive&, SExDescend3&);
COutArchive& operator<<(COutArchive&, const SExDescend3&);
CInArchive& operator>>(CInArchive&, TVecExDescend3&);
COutArchive& operator<<(COutArchive&, const TVecExDescend3&);

CInArchive& operator>>(CInArchive&, SExDescend4&);
COutArchive& operator<<(COutArchive&, const SExDescend4&);
CInArchive& operator>>(CInArchive&, TVecExDescend4&);
COutArchive& operator<<(COutArchive&, const TVecExDescend4&);

CInArchive& operator>>(CInArchive&, SExDerived2&);
COutArchive& operator<<(COutArchive&, const SExDerived2&);
CInArchive& operator>>(CInArchive&, TVecExDerived2&);
COutArchive& operator<<(COutArchive&, const TVecExDerived2&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, STest&);
bool ToXML(const STest&, TiXmlElement&);

bool FromXML(TiXmlElement&, SServer&);
bool ToXML(const SServer&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPointer&);
bool ToXML(const SPointer&, TiXmlElement&);

bool FromXML(TiXmlElement&, SExBase&);
bool ToXML(const SExBase&, TiXmlElement&);
bool SuperFromXML(TiXmlElement&, SExBasePtr&);
bool SuperToXML(const SExBase&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecExBase&);
bool VectorToXML(const TVecExBase&, TiXmlElement&);

bool FromXML(TiXmlElement&, SExDerived1&);
bool ToXML(const SExDerived1&, TiXmlElement&);
bool SuperFromXML(TiXmlElement&, SExDerived1Ptr&);
bool SuperToXML(const SExDerived1&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecExDerived1&);
bool VectorToXML(const TVecExDerived1&, TiXmlElement&);

bool FromXML(TiXmlElement&, SExDescend3&);
bool ToXML(const SExDescend3&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecExDescend3&);
bool VectorToXML(const TVecExDescend3&, TiXmlElement&);

bool FromXML(TiXmlElement&, SExDescend4&);
bool ToXML(const SExDescend4&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecExDescend4&);
bool VectorToXML(const TVecExDescend4&, TiXmlElement&);

bool FromXML(TiXmlElement&, SExDerived2&);
bool ToXML(const SExDerived2&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecExDerived2&);
bool VectorToXML(const TVecExDerived2&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NExample
