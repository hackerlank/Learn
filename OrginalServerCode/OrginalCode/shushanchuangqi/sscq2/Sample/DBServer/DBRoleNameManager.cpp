#include "DBRoleNameManager.h"
#include "DB/DBMgr.h"
#include "GUIDMgr.h"
#include "Tokenizer.h"
#include "tinyxml.h"
#include "Random.h"
#include "Protocols.h"
#include "NameCheckMgr.h"
#include "DBRoleMgr.h"
bool RoleNameManager::AddPlayerName(UINT64 qwRoleId, const string& strName, bool DBMark)
{
    string name = MakeName(qwRoleId,strName);
    bool result = _mapName.insert(make_pair(name,qwRoleId)).second;
    if (result)
    {
        _mapId[qwRoleId] = name;

        if (!DBMark)
        {
            NPHPProt::TVecUserIDAndName vecTemp;
            NPHPProt::SUserIDAndName sUserIDAndName;
            sUserIDAndName.qwUserID = qwRoleId;
            sUserIDAndName.strName = strName;
            vecTemp.push_back(sUserIDAndName);

            g_Center2DBCommS.Send_SendAllUserIDAndName(_mapId.size(), vecTemp);
        }
    }
    return result;
}

string RoleNameManager::MakeName(UINT64 qwRoleId,const string& strName)
{ 
    //XXX: 如果合服，加上区号
    if (!_bIsMerge)
        return strName; 
    UINT16 wGroupID = CGUIDMgr::GetGroupId(qwRoleId);
    string strServerName;
    strServerName.clear();
    strServerName = strName + ".";
    char szServerGroupID[32] = {0};
    snprintf(szServerGroupID, sizeof(strServerName), "%d", wGroupID);
    strServerName += szServerGroupID;
    return strServerName;
}

UINT64 RoleNameManager::GetPlayerIdByName(const string& strName)
{
    auto pos = _mapName.find(strName);
    if (pos == _mapName.end())
    {
        return 0;
    }
    return pos->second;
}

bool RoleNameManager::CheckNameIsExist(const string& strName)
{
    auto pos = _mapName.find(strName);
    return pos != _mapName.end();
}

void RoleNameManager::LoadUserName(QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    UINT64 qwLoadTimer = GetTickCount();
    basesql << "select count(*) as dwCount from tblroledata;";
    CDBMgr::Instance().DoSelectQuery(basesql.str(),NULL,[this, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {  
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet ;
            UINT32 dwCount = 0;
            if(byRet == 0 && dataRes.size()== 1)
            {
            mysqlpp::Row& rRow = dataRes[0];
            GET_UINT_SAME(dwCount);
            }
            else
            {
            queryfun(byRet,0);
            return ;
            }
            if(dwCount == 0)
            {
            queryfun(byRet,0);
            return ;
            }
            UINT32 dwPageSize  = 10000;
            UINT32 dwTotalPage =dwCount % dwPageSize != 0 ? dwCount/dwPageSize+1 : dwCount/dwPageSize;
            for(UINT32 dwPage = 0; dwPage != dwTotalPage;dwPage++)
            {
                mysqlpp::SQLStream querysql(NULL);
                querysql << "SELECT qwRoleID,strName FROM tblroledata"; 
                querysql << " WHERE qwRoleID >= (SELECT qwRoleID FROM tblroledata LIMIT ";
                querysql << dwPage*dwPageSize;
                querysql << " ,1) LIMIT ";
                querysql << dwPageSize;
                querysql << ";";
                CDBMgr::Instance().DoSelectQuery(querysql.str(),NULL,[this,dwCount, queryfun, querysql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
                        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << querysql.str() << "result:" << byRet ;
                        UINT32 ncount = dataRes.size();
                        for (UINT32 i = 0 ; i< ncount;i++)
                        {
                        mysqlpp::Row& rRow = dataRes[i];
                        UINT64 qwRoleId = 0;
                        string strName;
                        qwRoleId  = rRow["qwRoleID"];
                        const mysqlpp::String& strname = rRow["strName"];
                        if (strname != mysqlpp::null && !strname.empty())
                        {
                        strname.to_string(strName);
                        }
                        if (!AddPlayerName(qwRoleId,strName,true))
                        {
                        LOG_CRI << "Name repeat from DB :" <<qwRoleId <<":"<< strName; 
                        }
                        _dwUserNum++;
                        if(_dwUserNum == dwCount)
                        {
                          queryfun(0,_dwUserNum);
                        }
                        
                        }
                        });
            }
    });
}

bool RoleNameManager::Init(bool bIsMerge,QueryFun fun)
{
    string strConfigFile = Config._strConfigDir + "Conf/Misc/random_name.xml";
    if(!LoadRandomName(strConfigFile))
    {
        return false;
    }
    _bIsMerge = bIsMerge;
    LoadUserName(fun);
    return true;
}

string RoleNameManager::GetPlayerName(UINT64 qwRoleId)
{
    auto iter = _mapId.find(qwRoleId);
    if (iter != _mapId.end())
    {
        return iter->second;
    }
    return "";
}

bool RoleNameManager::HasRole(UINT64 qwRoleId)
{
    return _mapId.find(qwRoleId) != _mapId.end();
}
bool RoleNameManager::LoadRandomName(const string& strFile)//加载随机名字文件
{
    TiXmlDocument doc;
    if(!doc.LoadFile(strFile.c_str()))
    {
        LOG_CRI << "LoadFile fails! File: " << strFile;
        return false;
    }
    TiXmlElement* pElemRoot = doc.RootElement();
    if(pElemRoot == NULL)
        return false;
    TiXmlElement* pElemMaleSurname = pElemRoot->FirstChildElement("malesurname");
    if(pElemMaleSurname == NULL)
        return false;
    const char* pMaleSurname = pElemMaleSurname->GetText();
    if(pMaleSurname == NULL)
    {
        return false;
    }
    buf::Tokenizer MaleSurnametk(pMaleSurname, ',');
    set<string> setRandomMaleSurname;
    for (size_t i = 0 ; i< MaleSurnametk.size();++i)
    {
        if(setRandomMaleSurname.insert(MaleSurnametk[i]).second)
        {
            _vecRandomMaleSurname.push_back(MaleSurnametk[i]);
        }
    }
    LOG_CRI << "malesurname Repeat: " << MaleSurnametk.size() - setRandomMaleSurname.size(); 
    if (_vecRandomMaleSurname.empty())
    {
        return false;
    }

    TiXmlElement* pElemMaleName = pElemRoot->FirstChildElement("malename");
    if(pElemMaleName == NULL)
        return false;
    const char* pMaleName = pElemMaleName->GetText();
    if(pMaleName == NULL)
    {
        return false;
    }
    buf::Tokenizer MaleNametk(pMaleName, ',');
    set<string> setRandomMaleName;
    for (size_t i = 0 ; i< MaleNametk.size();++i)
    {
        if(setRandomMaleName.insert(MaleNametk[i]).second)
        {
            _vecRandomMaleName.push_back(MaleNametk[i]);
        }
    }
    LOG_CRI << "malename Repeat: " << MaleNametk.size()-setRandomMaleName.size(); 

    if (_vecRandomMaleName.empty())
    {
        return false;
    }

    TiXmlElement* pElemFemaleSurname = pElemRoot->FirstChildElement("femalesurname");
    if(pElemFemaleSurname == NULL)
        return false;
    const char* pFemaleSurname = pElemFemaleSurname->GetText();
    if(pFemaleSurname == NULL)
        return false;
    buf::Tokenizer FemaleSurnametk(pFemaleSurname, ',');
    set<string> setFemaleSurname;
    for (size_t i = 0 ; i< FemaleSurnametk.size();++i)
    {
        if(setFemaleSurname.insert(FemaleSurnametk[i]).second)
        {
            _vecRandomFemaleSurname.push_back(FemaleSurnametk[i]);
        }
    }
    LOG_CRI << "femalesurname Repeat: " << FemaleSurnametk.size()-setFemaleSurname.size();  
    if (_vecRandomFemaleSurname.empty())
    {
        return false;
    }

    TiXmlElement* pElemFemaleName = pElemRoot->FirstChildElement("femalename");
    if(pElemFemaleName == NULL)
        return false;
    const char* pFemaleName = pElemFemaleName->GetText();
    if(pFemaleName == NULL)
    {
        return false;
    }
    buf::Tokenizer FemaleNametk(pFemaleName, ',');
    set<string> setRandomFemaleName;

    for (size_t i = 0 ; i< FemaleNametk.size();++i)
    {
        if(setRandomFemaleName.insert(FemaleNametk[i]).second)
        {
            _vecRandomFemaleName.push_back(FemaleNametk[i]);
        }
    }
    if (_vecRandomFemaleName.empty())
    {
        return false;
    }
    LOG_CRI << "femalename Repeat: " << FemaleNametk.size()-setRandomFemaleName.size();  

    return true;
}

bool RoleNameManager::CreateRandomName(UINT64 qwRoleId,bool bIsMale,string& strPlayerName)//生成一个随机名字
{
    //vector<string> _vecRandomMaleSurname;//男姓
    //vector<string> _vecRandomMaleName;//男名
    //vector<string> _vecRandomFemaleSurname;//女姓
    //vector<string> _vecRandomFemalename;//女名
    if(_vecRandomMaleSurname.empty() || _vecRandomMaleName.empty() || _vecRandomFemaleSurname.empty() || _vecRandomFemaleName.empty())
    {
        return false;
    }
    const vector<string> *pSurname = NULL;
    const vector<string> *pName = NULL;
    if (bIsMale)
    {
        pSurname = &_vecRandomMaleSurname;
        pName = &_vecRandomMaleName;
    }
    else
    {
        pSurname = &_vecRandomFemaleSurname;
        pName = &_vecRandomFemaleName;
    }
    if(pSurname == NULL || pName == NULL)
    {
        return false;
    }
    const vector<string> &rSurname = *pSurname;
    const vector<string> &rName = *pName;
    //确定姓
    UINT8 byTry = 0;
    do 
    { 
        byTry++;
        //随机姓
        UINT32 uiName = CRandom::RandInt(0,rSurname.size()-1);
        string strName = rSurname[uiName];
        //随机名的字数
        UINT8 byNum =  CRandom::RandInt(MinNameNums,MaxNameNums);
        for (UINT8 ucNum = 0 ;ucNum != byNum;ucNum++)
        {
            UINT32 uiAfterName = CRandom::RandInt(0,rName.size()-1);
            strName += rName[uiAfterName];
        }
        ENameLenRes res = CNameCheckMgr::CheckNameValid(strName,MIN_ROLENAME_LENGTH,MAX_ROLENAME_LENGTH);
        if(res != eNameSuc)
        {
            LOG_CRI << "Name is PingBi:" << strName;
            continue;
        }
        /*
        if(g_PingBiZhi.IsPingBi(strName))
        {
            LOG_CRI << "Name is PingBi:" << strName;
            continue;
        }
        */
        //检查是否有重复
        string SvrstrName = MakeName(qwRoleId,strName);
        if(!CheckNameIsExist(SvrstrName))
        {
            strPlayerName = strName;
            LOG_INF << "GetName:" << SvrstrName;
            return true;
        }
        else
        {
            LOG_CRI << "Name is Repeat :"<< SvrstrName; 
        }
    } while(byTry != RandomMaxTimes);
    LOG_CRI<< "CANNOT Find Name";
    return false;
}

void RoleNameManager::GetAllUserIDAndName()
{
    UINT32 dwTotalSize = _mapId.size();
    if (dwTotalSize == 0)
    {
        NPHPProt::TVecUserIDAndName vecTemp;
        g_Center2DBCommS.Send_SendAllUserIDAndName(dwTotalSize, vecTemp);
        return;
    }

    auto iter = _mapId.begin();
    while(dwTotalSize > 0)
    {
        UINT16 count = 0;
        NPHPProt::TVecUserIDAndName vecTemp;
        for(; iter!=_mapId.end(); ++iter)
        {
            {
                NPHPProt::SUserIDAndName sUserIDAndName;
                sUserIDAndName.qwUserID = iter->first;
                sUserIDAndName.strName = iter->second;
                vecTemp.push_back(sUserIDAndName);
                count++;
            }

            if(count >= 500) //每次发500条
            {
                ++iter;
                break;
            }
        }

        if (dwTotalSize > 0)
        {
            dwTotalSize -= count;
            g_Center2DBCommS.Send_SendAllUserIDAndName(dwTotalSize, vecTemp);
        }
        else
            return;
    }
}
