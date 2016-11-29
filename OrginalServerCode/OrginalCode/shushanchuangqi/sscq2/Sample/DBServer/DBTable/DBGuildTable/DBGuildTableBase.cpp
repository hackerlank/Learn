#include "DBGuildTableBase.h"

#include "DBGuildBaseInfoTable.h"
#include "DBGuildUserTable.h"
#include "DBGuildListInfoTable.h"
#include "DBGuildApplyTable.h"
#include "DBGuildAuthorityTable.h"
#include "DBGuildBuildingTable.h"
#include "DBGuildStatueTable.h"
#include "DBGuildLogTable.h"
#include "DBLingShanShopBuyLogTable.h"

#include "DBGuildBattleTable.h"

CTableManagerBaseForGuild::CTableManagerBaseForGuild()
{
}

CTableManagerBaseForGuild::~CTableManagerBaseForGuild()
{
}

CTableManagerBaseForGuild* CTableManagerBaseForGuild::CreateManager(EGuildDataType eType,UINT64 qwGuildID)
{
    switch (eType)
    {
        case eGDTBaseInfo:
            return new CDBGuildBaseInfoTableManager(qwGuildID);
        case eGDTUser:
            return new CDBGuildUserTableManager(qwGuildID);
        case eGDTApplyInfo:
            return new CDBGuildApplyTableManager(qwGuildID);
        case eGDTAuthority:
            return new CDBGuildAuthorityTableManager(qwGuildID);
        case eGDTBuilding:
            return new CDBGuildBuildingTableManager(qwGuildID);
        case eGDTStatue:
            return new CDBGuildStatueTableManager(qwGuildID);
        case eGDTLog:
            return new CDBGuildLogTableManager(qwGuildID);
        case eGDTLSSBLog:
            return new CDBLingShanShopBuyLogTableManager(qwGuildID);
        default:
            LOG_CRI << "Invalid EGuildDataType: " << static_cast<UINT32>(eType) << ".";
            return NULL;
    }
    return NULL;
}

void CTableManagerBaseForGuild::DestroyManager(CTableManagerBaseForGuild* pManager)
{
    if (NULL != pManager)
    {
        delete pManager;
        pManager = NULL;
    }
}

CTableManagerBaseForGuildPub::CTableManagerBaseForGuildPub()
{
}

CTableManagerBaseForGuildPub::~CTableManagerBaseForGuildPub()
{
}

CTableManagerBaseForGuildPub* CTableManagerBaseForGuildPub::CreateManager(EGuildPubDataType eType,UINT64 qwGuildID)
{
    switch (eType)
    {
        case eGPDTListInfo:
            return new CDBGuildListInfoTableManager(qwGuildID);
        case eGPDTBattleInfo:
            return new CDBGuildBattleTableManager(qwGuildID);
        default:
            LOG_CRI << "Invalid EPubGuildDataType: " << static_cast<UINT32>(eType) << ".";
            return NULL;
    }
    return NULL;
}

void CTableManagerBaseForGuildPub::DestroyManager(CTableManagerBaseForGuildPub* pManager)
{
    if (NULL != pManager)
    {
        delete pManager;
        pManager = NULL;
    }
}

