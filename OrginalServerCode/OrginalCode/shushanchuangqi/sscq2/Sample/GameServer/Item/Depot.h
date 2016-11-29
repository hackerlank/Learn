#pragma once
#include "Pack.h"

class CDepot : public CPack 
{
public:
	CDepot(CUser& rUser);
	virtual EStoreType GetStoreType() const { return eStoreDepot; }
    virtual UINT16 GetCapacity() const;
};
