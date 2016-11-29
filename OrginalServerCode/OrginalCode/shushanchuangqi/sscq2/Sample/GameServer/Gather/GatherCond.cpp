#include "GatherCond.h"
#include "Player.h"
#include "User.h"

CGatherCondBase* CGatherCondBase::CreateCond(EGatherConType eType, UINT32 dwParam1,UINT32 dwParam2)
{
    switch (eType)
    {
        case eGCT_Level:
            {
                if(dwParam1 == 0)
                {
                    break;
                }
                return new CGatherCondLevel(dwParam1); 
            }
            break;
        case eGCT_Item:
            {
                if(dwParam1 == 0 || dwParam2 == 0)
                {
                    break;
                }
                return new CGatherCondItem(dwParam1,dwParam2);
            }
            break;
        case eGCT_VIP:
            {
                if(dwParam1 == 0)
                {
                    break;
                }
                return new CGatherCondVIP(dwParam1); 
            }
            break;
        default:
            break;
    }
    return NULL;
}

EGatherResult CGatherCondLevel::CheckCond(CPlayer & rPlayer)
{
    if( _wLevel > rPlayer.GetLevel())
    {
        return eGatherLevel;
    }
    return eGatherSuccess;
}

EGatherResult CGatherCondItem::CheckCond(CPlayer & rPlayer)
{

    if(_wItemId > EMONEY_NONE && _wItemId < EMONEY_END)
    { 
        SResource sRes;
        sRes._eRes = static_cast<EMoneyType>(_wItemId);
        sRes._dwValue = _wItemNum;
        TVecResource vecSource;
        vecSource.push_back(sRes);
        if(!CStore::CanSubResource(rPlayer.GetUser(),vecSource))
        {
            return eGatherItemLimit;
        }
    }
    else if(!(rPlayer.GetUser().GetPack().GetItemCount(_wItemId) >= _wItemNum))
    {
        return eGatherItemLimit;
    }
    return  eGatherSuccess;
}

void CGatherCondItem::DoCond(CPlayer & rPlayer)
{
    if(CheckCond(rPlayer) != eGatherSuccess)
    {
        return ;
    }
    if(_wItemId > EMONEY_NONE && _wItemId < EMONEY_END)
    { 
        SResource sRes;
        sRes._eRes = static_cast<EMoneyType>(_wItemId);
        sRes._dwValue = _wItemNum;
        TVecResource vecSource;
        vecSource.push_back(sRes);
        CStore::SubResource(rPlayer.GetUser(),vecSource,NLogDataDefine::ItemTo_GatherCond);
    }
    else
    {
        rPlayer.GetUser().GetPack().DelItemByItemID(_wItemId, _wItemNum, true, NLogDataDefine::ItemTo_GatherCond);
    }
}

EGatherResult CGatherCondVIP::CheckCond(CPlayer & rPlayer)
{
    return eGatherVIP;
}

