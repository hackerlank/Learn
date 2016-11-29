// =====================================================================================
//
//       Filename:  FoundationMgr.cpp
//
//    Description:  基金管理类
//
//        Version:  1.0
//        Created:  04/17/2015 10:52:19 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================


#include "FoundationMgr.h"

#include "Tokenizer.h"

// ===  FUNCTION  ======================================================================
//         Name:  ~CFoundationMgr
//  Description:  析构函数
// =====================================================================================
CFoundationMgr::~CFoundationMgr ()
{
}		// -----  end of function ~CFoundationMgr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  Init
//  Description:  初始化
// =====================================================================================
bool CFoundationMgr::Init()
{
    string strPath = Config._strConfigDir + "Conf/Table/Foundation.xml";
    CFoundationLoader oFoundationLoader;
    if(!oFoundationLoader.LoadData(strPath))
    {
        LOG_CRI << "oFoundationLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oFoundationLoader._vecData.size(); ++i)
    {
        SFoundationCFG* pFoundationCFG = oFoundationLoader._vecData[i];
        SFoundationCFGEx& rFoundationCFGEx = _mapID2FoundationCFG[pFoundationCFG->_Uid];
        rFoundationCFGEx.SetConfig(*pFoundationCFG);

        if (rFoundationCFGEx._Level.length() > 0)
        {
            Tokenizer yatk(rFoundationCFGEx._Level, ",");
            for (size_t j = 0; j < yatk.size(); ++ j)
            {
                rFoundationCFGEx._mapID2Level.insert(make_pair(j+1, atoi(yatk[j].c_str())));
            }
        }
        Tokenizer tk(rFoundationCFGEx._Reward, "|");
        for (size_t j = 0; j < tk.size(); ++ j)
        {
            Tokenizer yatk(tk[j], ",");
            UINT32 dwItemID = atoi(yatk[0].c_str());
            if (!dwItemID)
                continue;
            SItemGenInfo stItemGen;
            if (yatk.size() > 1)
                stItemGen.dwCount = atoi(yatk[1].c_str());
            else
                stItemGen.dwCount = 1;
            stItemGen.wItemID = dwItemID;
            stItemGen.eBindType = eBindGet;
            rFoundationCFGEx._mapItemGen.insert(make_pair(j+1, stItemGen));
        }
    }

    return true;
}		// -----  end of function Init  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetFoundationCFG
//  Description:  获取配置
// =====================================================================================
SFoundationCFGEx* CFoundationMgr::GetFoundationCFG(UINT8 byType)
{
    auto itr = _mapID2FoundationCFG.find(byType);
    if(itr != _mapID2FoundationCFG.end())
        return &itr->second;
    return NULL;
}		// -----  end of function GetFoundationCFG  ----- //

