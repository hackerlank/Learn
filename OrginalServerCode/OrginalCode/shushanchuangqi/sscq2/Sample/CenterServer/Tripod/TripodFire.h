#ifndef TRIPODFIRE_H_
#define TRIPODFIRE_H_

#include "TripodProt.h"

using namespace NTripodProt;

class CFire: public CPoolObj<CFire>
{
public:
    CFire(UINT16 wFireID);
    ~CFire();

    //void SetOwnerID(UINT64 qwRoleID) { _qwOwnerID = qwRoleID; }
    //UINT64 GetOwnerID() const { return _qwOwnerID; }
    UINT16 GetID() const { return _wFireID; }
    void SetSucceedCnt(UINT32 dwCnt) { _dwSucceed = dwCnt; }
    void SetRemainCnt(UINT32 dwCnt) { _dwRemain = dwCnt; }
    void AddSucceedCnt(UINT32 dwCnt) { _dwSucceed += dwCnt; }
    void AddRemainCnt(UINT32 dwCnt) { _dwRemain += dwCnt; }
    void SubSucceedCnt(UINT32 dwCnt) { _dwSucceed = _dwSucceed > dwCnt ? _dwSucceed-dwCnt : 0; }
    void SubRemainCnt(UINT32 dwCnt) { _dwRemain = _dwRemain > dwCnt ? _dwRemain-dwCnt : 0; }
    UINT32 GetSucceedCnt() const { return _dwSucceed; }
    UINT32 GetRemainCnt() const { return _dwRemain; }

    void ToProt(SFireInfo& rInfo);
private:
    UINT16 _wFireID;
    UINT32 _dwSucceed;
    UINT32 _dwRemain;
};

#endif // TRIPODFIRE_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

