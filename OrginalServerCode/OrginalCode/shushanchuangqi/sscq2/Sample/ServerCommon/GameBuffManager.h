#ifndef GAME_BUFF_MANAGER_H
#define GAME_BUFF_MANAGER_H

#pragma once

#include "ProtoCommon.h"
#include "BuffCFG.h"
#include "Tokenizer.h"

enum EBuffDefine
{
    eDeadInDgn = 5,//在副本里战败
};

using namespace NProtoCommon;
using namespace NProtoCommon;

class CGameBuffManager
{
    public:
        CGameBuffManager();
        virtual ~CGameBuffManager();

        bool Init();

        virtual EBuffType GetBuffType() const = 0;
        virtual void UpdateBuff2DB(const SDBBuffInfo& rDBBuffInfo, EDataChange eDataChange)= 0;

        // 通过ID新增指定Buff   返回值: eBOROverdue /eBORSuccess
        EBuffOpResult AddBuff(UINT16 wBuffID);

        // 设定指定Buff         返回值: eBOROverdue /eBORSuccess
        EBuffOpResult SetBuff(UINT16 wBuffID, const TVecUINT32& vecParam, UINT32 dwBuffTime, bool bInit = false);

        // 新增指定Buff         返回值: eBOROverdue /eBORSuccess
        EBuffOpResult AddBuff(UINT16 wBuffID, const TVecUINT32&  vecParam, UINT32 dwBuffTime);

        // 消除指定Buff         返回值: eBORNotExisted /eBORSuccess
        EBuffOpResult RemoveBuff(UINT16 wBuffID);

        // 暂停指定Buff         返回值: eBORNotExisted /eBORPaused /eBOROverdue /eBORSuccess
        EBuffOpResult PauseBuff(UINT16 wBuffID);

        // 恢复指定Buff         返回值: eBORNotExisted /eBOROverdue /eBORSuccess
        EBuffOpResult ResumeBuff(UINT16 wBuffID);

        // 增加Buff效果值     返回值: eBORNotExisted /eBORPaused /eBOROverdue /eBORSuccess
        EBuffOpResult ExtendBuffValue(UINT16 wBuffID, UINT32 dwParam, UINT8 byIndex = 0);

        // 延长Buff持续时间     返回值: eBORNotExisted /eBORPaused /eBOROverdue /eBORSuccess
        EBuffOpResult ExtendBuffTime(UINT16 wBuffID, UINT32 dwBuffTime);

        // 获取Buff的详细信息   返回值: eBORNotExisted /eBORSuccess
        EBuffOpResult GetDBBuffData(UINT16 wBuffID, SDBBuffInfo& rDBBuffInfo);

        // 获取Buff的详细信息   返回值: eBORNotExisted /eBORSuccess
        EBuffOpResult GetBuffData(UINT16 wBuffID, SBuffInfo& rBuffInfo);

        EBuffOpResult GetAllBuffData(TVecUINT16& rvecBuffID, TVecBuffInfo& rvecBuffInfo);

        virtual UINT64 GetRoleID() const = 0;
        virtual UINT64 GetOwnerID() const = 0;

        virtual void OnBuffChanged(EDataChange eType, const SBuffInfo& rInfo) = 0;
        bool HasBuff(UINT16 wBuffID) const;

        const TVecFloat& GetBufferAttrVec() const { return _vecBufferAttr; };

        void SetBufferDirty(bool bDirty)  { _bBufferDirty= bDirty; }
        bool IsBufferDirty() { return _bBufferDirty; }
    protected:

        friend class CGameBuffMgr;
        void TimerCheck(time_t tNow);

        typedef map<UINT16, SDBBuffInfo> MapInfo;

        TVecFloat _vecBufferAttr;

        MapInfo     _mapInfo;

        bool  _bBufferDirty;
    private:
        bool CheckBuffTime(UINT16 wBuffID);
        bool CheckBuffTime(MapInfo::iterator it);
};

struct SBuffCFGEx : public SBuffCFG
{
    TVecUINT32 _vecParam;
    TVecUINT32 _vecEffectMapID;
    TVecUINT32 _vecSameBuffID;
    void SetConfig(const SBuffCFG& rBuffInfo)
    {
        *(SBuffCFG*)this = rBuffInfo;
        _vecParam.clear();
        Tokenizer tk(rBuffInfo._Param1, ";");
        for (size_t i = 0; i < tk.size(); ++i)
        {               
            _vecParam.push_back(::atoi(tk[i].c_str()));
        }               
        _vecEffectMapID.clear();
        Tokenizer tk2(rBuffInfo._MapID, ";");
        for (size_t i = 0; i < tk2.size(); ++i)
        {               
            _vecEffectMapID.push_back(::atoi(tk2[i].c_str()));
        }               
        Tokenizer tk3(rBuffInfo._IsSame, ";");
        for (size_t i = 0; i < tk3.size(); ++i)
        {               
            _vecSameBuffID.push_back(::atoi(tk3[i].c_str()));
        }               
    }
};

class CGameBuffMgr : public Singleton<CGameBuffMgr>
{
    public:
        bool Init(const string& strDir);

        bool LoadConfig();
        bool Reload();

        SBuffCFGEx* GetBuff(UINT16 wBuffID);
        void TimerCheck(time_t tNow);

        void AddBuffManager(UINT64 qwInstID, CGameBuffManager* pBuffManager);
        void RemoveBuffManager(UINT64 qwInstID);
    private:
        map<UINT16, SBuffCFGEx* > _mapCFG;
        map<UINT64, CGameBuffManager*> _mapID2BuffManager;
};

#endif //#ifndef GAME_BUFF_MANAGER_H
