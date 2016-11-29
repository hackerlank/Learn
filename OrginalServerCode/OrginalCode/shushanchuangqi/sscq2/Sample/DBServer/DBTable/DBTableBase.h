
#ifndef DBTableBase_H__
#define DBTableBase_H__

#include <bitset> 
#include "RoleInfoDefine.h"
#include "ItemProt.h"
#include "FighterProt.h"
#include "FriendProt.h"
#include "Game2DBComm.h"
#include "../DB/DBMgr.h"

#define UPCOL(ColName) UPdata_##ColName
#define UPCOLSet(ColName) _setChanged.set(UPCOL(ColName))
#define DIFF(ColName) do {                  \
    if (newData.ColName != ColName)         \
    {                                       \
        _setChanged.set(UPCOL(ColName));    \
        ColName = newData.ColName;          \
    }                                       \
} while (0)

#define DIFFFLOAT(ColName) do {                 \
    if (abs(newData.ColName-ColName) > 0.001f)  \
    {                                           \
        _setChanged.set(UPCOL(ColName));        \
        ColName = newData.ColName;              \
    }                                           \
} while (0)

#define DIFF2(ColName, Local) do {          \
    if (newData.ColName != Local)           \
    {                                       \
        _setChanged.set(UPCOL(ColName));    \
        Local = newData.ColName;            \
    }                                       \
} while (0)

#define DIFFFLOAT2(ColName, Local) do {     \
    if (abs(newData.ColName-Local) > 0.001f)\
    {                                       \
        _setChanged.set(UPCOL(ColName));    \
        Local = newData.ColName;            \
    }                                       \
} while (0)

#define DIFFONLY2(ColName, NewValue, Local) do {          \
    if (NewValue != Local)           \
    {                                       \
        _setChanged.set(UPCOL(ColName));    \
        Local = NewValue;            \
    }                                       \
} while (0)


//数据库名和定义名不一致
//int8
#define UPDATE_TINYINT(ColName, Value) if (_setChanged.test(UPCOL(ColName)))   \
    ostr << "," << #ColName << "=" <<(mysqlpp::sql_tinyint)Value
//uint8
#define UPDATE_UTINYINT(ColName, Value) if (_setChanged.test(UPCOL(ColName)))  \
    ostr << "," << #ColName << "=" <<(mysqlpp::sql_tinyint_unsigned)Value
//int16
#define UPDATE_SMALLINT(ColName, Value) if (_setChanged.test(UPCOL(ColName)))  \
    ostr << "," << #ColName << "=" <<(mysqlpp::sql_smallint)Value
//uint16
#define UPDATE_USMALLINT(ColName, Value) if (_setChanged.test(UPCOL(ColName))) \
    ostr << "," << #ColName << "=" <<(mysqlpp::sql_smallint_unsigned)Value
//int32
#define UPDATE_INT(ColName, Value) if (_setChanged.test(UPCOL(ColName)))       \
    ostr << "," << #ColName << "=" <<(mysqlpp::sql_int)Value
//uint32
#define UPDATE_UINT(ColName, Value) if (_setChanged.test(UPCOL(ColName)))      \
    ostr << "," << #ColName << "=" <<(mysqlpp::sql_int_unsigned)Value
//int64
#define UPDATE_BIGINT(ColName, Value) if (_setChanged.test(UPCOL(ColName)))    \
    ostr << "," << #ColName << "=" <<(mysqlpp::sql_bigint)Value
//uint64
#define UPDATE_UBIGINT(ColName, Value) if (_setChanged.test(UPCOL(ColName)))   \
    ostr << "," << #ColName << "=" <<(mysqlpp::sql_bigint_unsigned)Value
//float
#define UPDATE_FLOAT(ColName, Value) if (_setChanged.test(UPCOL(ColName)))     \
    ostr << "," << #ColName << "=" <<(mysqlpp::sql_float)Value
//double
#define UPDATE_DOUBLE(ColName, Value) if (_setChanged.test(UPCOL(ColName)))    \
    ostr << "," << #ColName << "=" <<(mysqlpp::sql_double)Value
//string_char
#define UPDATE_STRING_CHAR(ColName, Value) if(_setChanged.test(UPCOL(ColName)))     \
    ostr << "," << #ColName << "=" << mysqlpp::quote << (mysqlpp::sql_char)Value
//string_text(0~65535)
#define UPDATE_STRING_TEXT(ColName, Value) if(_setChanged.test(UPCOL(ColName)))     \
    ostr << "," << #ColName << "=" << mysqlpp::quote << (mysqlpp::sql_text)Value

//以下是Get函数
//int8
#define GET_TINYINT(ColName, Local) Local = (mysqlpp::sql_tinyint)(rRow[#ColName]);
//uint8
#define GET_UTINYINT(ColName, Local) Local = (mysqlpp::sql_tinyint_unsigned)(rRow[#ColName]);
//int16
#define GET_SMALLINT(ColName, Local) Local = (mysqlpp::sql_smallint)(rRow[#ColName]);
//uint16
#define GET_USMALLINT(ColName, Local) Local = (mysqlpp::sql_smallint_unsigned)(rRow[#ColName]);
//int32
#define GET_INT(ColName, Local) Local = (mysqlpp::sql_int) rRow[#ColName];
//uint32
#define GET_UINT(ColName, Local) Local = (mysqlpp::sql_int_unsigned) rRow[#ColName];
//int64
#define GET_BIGINT(ColName, Local) Local = (mysqlpp::sql_bigint)rRow[#ColName];
//uint64
#define GET_UBIGINT(ColName, Local) Local = (mysqlpp::sql_bigint_unsigned)rRow[#ColName];
//float
#define GET_FLOAT(ColName, Local) Local = (mysqlpp::sql_float)rRow[#ColName];
//double 
#define GET_DOUBLE(ColName, Local) Local = (mysqlpp::sql_double)rRow[#ColName];
//string_char
#define GET_STRING_CHAR(ColName, Local) const mysqlpp::String& str##ColName = rRow[#ColName];   \
    if (str##ColName != mysqlpp::null && !(str##ColName.empty()))                               \
    str##ColName.to_string(Local)
//string_text
#define GET_STRING_TEXT(ColName, Local) GET_STRING_CHAR(Local,ColName)
//数据库名和定义名一致
//int8
#define UPDATE_TINYINT_SAME(ColName) UPDATE_TINYINT(ColName,ColName)
//uint8
#define UPDATE_UTINYINT_SAME(ColName) UPDATE_UTINYINT(ColName,ColName)
//int16
#define UPDATE_SMALLINT_SAME(ColName) UPDATE_SMALLINT(ColName,ColName)
//uint16
#define UPDATE_USMALLINT_SAME(ColName) UPDATE_USMALLINT(ColName,ColName)
//int32
#define UPDATE_INT_SAME(ColName) UPDATE_INT(ColName,ColName)
//uint32
#define UPDATE_UINT_SAME(ColName) UPDATE_UINT(ColName,ColName)
//int64
#define UPDATE_BIGINT_SAME(ColName) UPDATE_BIGINT(ColName,ColName)
//uint64
#define UPDATE_UBIGINT_SAME(ColName) UPDATE_UBIGINT(ColName,ColName)
//float
#define UPDATE_FLOAT_SAME(ColName) UPDATE_FLOAT(ColName,ColName)
//double
#define UPDATE_DOUBLE_SAME(ColName) UPDATE_DOUBLE(ColName,ColName)
//string_char
#define UPDATE_STRING_CHAR_SAME(ColName) UPDATE_STRING_CHAR(ColName,ColName)
//string_text
#define UPDATE_STRING_TEXT_SAME(ColName) UPDATE_STRING_TEXT(ColName,ColName)

//int8
#define GET_TINYINT_SAME(ColName) GET_TINYINT(ColName,ColName)
//uint8
#define GET_UTINYINT_SAME(ColName) GET_UTINYINT(ColName,ColName)
//int16
#define GET_SMALLINT_SAME(ColName) GET_SMALLINT(ColName,ColName)
//uint16
#define GET_USMALLINT_SAME(ColName) GET_USMALLINT(ColName,ColName)
//int32
#define GET_INT_SAME(ColName) GET_INT(ColName,ColName)
//uint32
#define GET_UINT_SAME(ColName) GET_UINT(ColName,ColName)
//int64
#define GET_BIGINT_SAME(ColName) GET_BIGINT(ColName,ColName)
//uint64
#define GET_UBIGINT_SAME(ColName) GET_UBIGINT(ColName,ColName)
//float
#define GET_FLOAT_SAME(ColName) GET_FLOAT(ColName,ColName)
//double
#define GET_DOUBLE_SAME(ColName) GET_DOUBLE(ColName,ColName)
//string-char
#define GET_STRING_CHAR_SAME(ColName) GET_STRING_CHAR(ColName,ColName)
//string-text
#define GET_STRING_TEXT_SAME(ColName) GET_STRING_TEXT(ColName,ColName)

using namespace NGame2DBComm;
using namespace NRoleInfoDefine;
using namespace NItemProt;
using namespace NFighterProt;
using namespace NFriendProt;

typedef function<void(INT8)> DumpFun;
typedef function<void(INT8,UINT32)> QueryFun;
typedef function<void(UINT32,UINT32)> ManagerUpdateFun;

#define UNKNOWNERR 100

class CInArchive;
class TableRowBase
{
    public:
        enum eDataState
        {
            eInInit,//初始状态
            eNoDB,//不在DB
            eInDB,//已经在DB且没有数据更新
            eInDBUpdate,//在DB并且有数据更新
        };

    public:
        virtual ~TableRowBase();
        //数据更新
        bool Update(string& strData, bool bIsAdd);
        //数据更新
        bool Update(const string& strData, bool bIsAdd);
        bool HasOP(void);
        bool IsInDB(void);
        void DumpToDB(UINT8 byLine,DumpFun dumpfun);
        void DumpToDBOther(DumpFun dumpfun);
        void DumpToDBGuild(DumpFun dumpfun);
        void DumpToDBRank(DumpFun dumpfun);
        TableRowBase():_eDBState(eInInit) {}
        eDataState GetDBState();

    protected:
        virtual void InitDataByStr(string& strData) = 0; //利用更新初始化
        virtual bool UpdateDataByStr(string& strData) = 0;//返回值：变化值大于0 true
        virtual bool GetInsertSqlStr(string& sqlstr) = 0;//生成插入语句 
        virtual bool GetUpdateSqlStr(string& sqlstr) = 0;//根据变化生成sql语句
        virtual void ResetChange(void) = 0;// 清理变化的记录

    protected:
        virtual void  InitDataByDBRow(const mysqlpp::Row &row);//利用查询初始化

    protected:
        eDataState _eDBState;
};

//管理器
class TableManagerBaseForRole
{
    public:
        TableManagerBaseForRole(EDataType etype, UINT64 setqwRoleID,UINT8 byDBLine) : 
            _eType(etype), _qwRoleID(setqwRoleID),_byLine(byDBLine)
        {}

        virtual ~TableManagerBaseForRole() {};
        //查询
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun) = 0;//返回查询的结果数量
        //删除
        virtual void DelData(string& strData) = 0;
        //更新，增加
        virtual void Update(string& strData, bool bIsAdd) = 0;
        //获得原始数据
        virtual void GetALLInfo(RoleDataInfo& rData) = 0;
        //更新放入数据库
        virtual void  DumpToDB(ManagerUpdateFun fun) = 0;
        virtual UINT32 GetUpdataNum() = 0; 

        static TableManagerBaseForRole* CreateManager(EDataType eType, UINT64 setqwRoleID,UINT8 byDBLine);
        static void DestroyManager(TableManagerBaseForRole* pManager);
        EDataType GetDataType() { return _eType; }

    private:
        EDataType _eType;
    protected:
        UINT64 _qwRoleID;
        UINT8 _byLine;
};

#endif

