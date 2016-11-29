#include "Gemstone.h"

CGemstone::CGemstone(UINT16 wItemID):
    CItem(wItemID),
     _qwOwnerID(0)
{
}
CGemstone::~CGemstone() 
{
}



UINT64 CGemstone::GetOwnerID() const
{
    return _qwOwnerID;
}

void CGemstone::SetOwnerID(UINT64 qwOwnerID)
{
    _qwOwnerID = qwOwnerID;
}

SItemPtr CGemstone::ToProt() const
{
    SGemstone* pGemstone = new SGemstone;
    if(pGemstone == NULL)
        return NULL;
    if(!ToStream(*pGemstone))
    {
        delete pGemstone;
        return NULL;
    }
    return SItemPtr(pGemstone);
}

bool CGemstone::FromStream(const SGemstone& rStream)
{
    CItem::FromStream(rStream);
    _qwOwnerID = rStream.qwOwnerID;
    return true;
}

bool CGemstone::ToStream(SGemstone& rStream) const
{
    CItem::ToStream(rStream);
    rStream.qwOwnerID = _qwOwnerID;
    return true;
}

