#include "stdafx.h"
#include "MoneyParam.h"

//SGoldpieceCFG CMoneyParamMgr::_arID2GoldPiece[eGoldParamEnd];

bool CMoneyParamMgr::Init()
{
    /*
	memset(_arID2GoldPiece, 0, sizeof(_arID2GoldPiece));
	string strPath = Config._strConfigDir + "Conf/DB/Goldpiece.xml";
	CGoldpieceLoader oGoldpieceLoader;
	if(!oGoldpieceLoader.LoadData(strPath))
	{
		LOG_CRI << "oGoldpieceLoader.LoadData fails! Path: " << strPath;
		return false;
	}
	for(size_t i = 0; i < oGoldpieceLoader._vecData.size(); ++i)
	{
		SGoldpieceCFG* pGoldpieceCFG = oGoldpieceLoader._vecData[i];
		if(pGoldpieceCFG == NULL)
			return false;
		if(pGoldpieceCFG->_Id >= eGoldParamEnd)
		{
			LOG_CRI << "pGoldpieceCFG->_Id " << pGoldpieceCFG->_Id << " is invalid";
			continue;
		}
		_arID2GoldPiece[pGoldpieceCFG->_Id] = *pGoldpieceCFG;
	}
    */

	return true;
}

/*
const SGoldpieceCFG* CMoneyParamMgr::GetMoneyParam(EMoneyParamID eParamID)
{
	if(eParamID >= eGoldParamEnd)
	{
		LOG_CRI << "eParamID is too big, ParamID is " << eParamID;
		return NULL;
	}
	return &_arID2GoldPiece[eParamID];
}
*/
