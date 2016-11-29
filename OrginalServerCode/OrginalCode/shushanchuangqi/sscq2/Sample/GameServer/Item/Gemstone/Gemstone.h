#ifndef GEMSTONE_H
#define GEMSTONE_H

#include "Item.h"
#include "ProtoCommon.h"

using namespace NProtoCommon;

#define GEMSTONE_DEBUG

#ifdef GEMSTONE_DEBUG
#define GEMSTONE_DBG LOG_DBG
#else
#define GEMSTONE_DBG if(1) {} else LOG_DBG
#endif //#ifdef GEMSTONE_DEBUG


class CGemstone : public CItem
{

    public:
        CGemstone(UINT16 wItemID);
        virtual ~CGemstone();
        DEF_NEW_DELETE(CGemstone);

        UINT64 GetOwnerID() const;
        void SetOwnerID(UINT64 qwOwnerID);

        virtual SItemPtr ToProt() const;
        bool FromStream(const SGemstone& rStream);
        bool ToStream(SGemstone& rStream) const;
        UINT8 GetStoneLevel() 
        {
            return GetItemConfig()._StoneLevel;
        }
    private:
        UINT64          _qwOwnerID;
};

typedef vector<CGemstone> TVecGemstoneItem;

#endif // #ifndef GEMSTONE_H

