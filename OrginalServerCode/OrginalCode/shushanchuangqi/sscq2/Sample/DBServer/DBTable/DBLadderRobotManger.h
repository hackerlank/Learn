#ifndef  DBTOTAL_LADDERROBOT_TABLE_H__
#define  DBTOTAL_LADDERROBOT_TABLE_H__
#include "DBTableBase.h"
#include "ArenaGS.h"
using namespace NArenaGS;
class CDBTotalLadderRobot : public SLadderRobot, public CPoolObj<CDBTotalLadderRobot>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(wRank),
            UPCOL(Max)
        };

    public:
        CDBTotalLadderRobot():_bIsNew(false){}
        void InitDataByData(const SLadderRobot & rData);
        bool UpdateDataByData(const SLadderRobot & rData);
        bool GetInsertSqlStr(string& sqlstr);
        bool GetUpdateSqlStr(string& sqlstr);
        void ResetChange(void);
        void InitDataByDBRow(const mysqlpp::Row &row);
        void SetNew(bool bNew) {_bIsNew = bNew;}
        bool IsNew(){return _bIsNew;}
        bool IsChange(){ return !_setChanged.none();}
    private:
        bitset<UPCOL(Max)> _setChanged;
        bool _bIsNew;

};

class CDBTotalLadderRobotManager : public CPoolObj<CDBTotalLadderRobotManager>
{ 
    public:
        CDBTotalLadderRobotManager():_byLoad(0){}
        void GetAllLadderRobot();
        void UpdateData(const SLadderRobot &stData);
        void DumpToDB(bool bForBit =false);
        UINT32 GetUpdataNum();
    private:
        void SendAllDataToCenter();
        map<UINT16,CDBTotalLadderRobot> _mapLadderRobotData;
        UINT8 _byLoad;
};
extern CDBTotalLadderRobotManager g_CDBTotalLadderRobotManager;
#endif

