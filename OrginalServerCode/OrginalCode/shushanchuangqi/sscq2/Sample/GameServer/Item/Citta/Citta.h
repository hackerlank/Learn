#ifndef CITTA_H
#define CITTA_H

#include "Item.h"
#include "ProtoCommon.h"

using namespace NProtoCommon;

#define CITTA_DEBUG

#ifdef CITTA_DEBUG
#define CITTA_DBG LOG_DBG
#else
#define CITTA_DBG if(1) {} else LOG_DBG
#endif //#ifdef CITTA_DEBUG

class CCittaMgr;

typedef std::map<EFighterAttr, UINT32>    TMapCittaAttr;
class CCitta : public CItem
{
    friend class CItemMgr;
    friend class CCittaMgr;

    public:
        CCitta(UINT16 wItemID);
        virtual ~CCitta();
        DEF_NEW_DELETE(CCitta);

        UINT64 GetOwnerID() const;
        void SetOwnerID(UINT64 qwOwnerID);

        virtual SItemPtr ToProt() const;
        bool FromStream(const SCitta& rStream);
        bool ToStream(SCitta& rStream) const;
        bool ToDBStream(SCitta& rStream) const;

        bool IsInited() const;
        void SetInited(bool bInited);

        const TMapCittaAttr& GetAttr() const;

        UINT32 GetSignetID() const;

    private:
        UINT64          _qwRoleID;
        UINT64          _qwOwnerID;

        bool            _bInited;
        TMapCittaAttr   _mapAttr;
        UINT32          _dwSkillID;
        UINT32          _dwSignetID;
};

typedef vector<CCitta> TVecCittaItem;

#endif // #ifndef CITTA_H

