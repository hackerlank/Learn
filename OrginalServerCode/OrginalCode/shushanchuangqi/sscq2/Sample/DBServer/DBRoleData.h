#ifndef RoleData_h__
#define RoleData_h__

#include <bitset>
#include <Game2DBComm.h>
#include "DBMgr.h"
using namespace NGame2DBComm;

#include "DBTable/DBRoleBaseTable.h"
#include "DBTable/DBRoleItemTable.h"
#include "ShipProt.h"
using namespace NShipProt;
// 人物属性 ：　人物数据状态
enum EUserState
{
    eUserNone,
    eUserLoadData,		//加载账号数据
    eUserCreateUser,	//创建帐号
    eUserInGame,		//在游戏中
    eUserLeaveAway,		//离开游戏(GameServer上还有数据)
    eUserLeaveOff,		//离开游戏(GameServer上数据已清除)
    eUserReplace		//替换角色
};

// 人物属性 ： 人物数据信息
class SDBRoleData :  public CPoolObj<SDBRoleData>
{
    public: 
        enum RoleUpdateStatus
        {
            DATAUPDATE_NONE,//无数据更新
            DATAUPDATA_WILL,//有数据更新
        };

        enum RoleOffLineStatus
        {
            OUTOF_OFFQUEUE,
            IN_OFFQUEUE,
        };

        UINT32 nMaxUpdata;
        UINT32 nNowUpdata;   
        UINT32 nServerId;
        map<EDataType,TableManagerBaseForRole*> _mapDataManager;
        RoleUpdateStatus _eUpdateDataStatus;    
        RoleOffLineStatus _eOffLineStatus;
        UINT64 _qwRoleId;
        UINT8  _byLineID;
        TVecEventOffLine vecEventOffLine;
        TVecShipReport vecShipReport;
        bool HasUpdateNum();
        UINT32 GetFreezeTimer();
        UINT32 UpDateNum();
        TableManagerBaseForRole* GetDataManagerByType(EDataType etype);
        EUserState GetUserState();
        void SetUserState(EUserState eUserState);
        UINT8 GetLine(){return _byLineID;}
        // 构造函数
    public:
        SDBRoleData(UINT64 qwRoleId)
            : nMaxUpdata(0), nNowUpdata(0), nServerId(0),
            _eUpdateDataStatus(DATAUPDATE_NONE),
            _eOffLineStatus(OUTOF_OFFQUEUE),
            _qwRoleId(qwRoleId),
            _eUserState(eUserNone)
        {
            _byLineID = CDBMgr::Instance().GetFreeLine();
            for (int i = 0; i < eTypeMax; ++i)
            {
                TableManagerBaseForRole* pTable = TableManagerBaseForRole::CreateManager((EDataType)i, _qwRoleId,_byLineID);
                if(NULL == pTable)
                {
                    LOG_CRI << "Table is NULL :" << (EDataType)i;
                    continue;
                }

                _mapDataManager[(EDataType)i] = pTable;
            }
        }

        ~SDBRoleData()
        {
            for (auto iter = _mapDataManager.begin();iter != _mapDataManager.end();iter++)
                TableManagerBaseForRole::DestroyManager(iter->second);
            _mapDataManager.clear();
            CDBMgr::Instance().FreeLine(_byLineID);
        }

        UINT16 GetMapID();

    private:
        EUserState _eUserState;
};
#endif

