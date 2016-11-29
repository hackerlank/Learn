#include "GUIDMgr.h"
#include "DBQueryMgr.h"

#define BIT_MASK(digit) ((1LL << (digit)) - 1)

static void OnOtherSaveGUID(UINT16 wGroup, UINT8 byIndex, EGUIDType eType, UINT64 qwCounter)
{
	CQuery oQuery;
	oQuery.AddSQL("INSERT INTO tblmaxid VALUES(%p, %p, %p, %p) ON DUPLICATE KEY UPDATE Counter = %p;");
	oQuery.AddParam<eTypeUINT16>(wGroup);
	oQuery.AddParam<eTypeUINT8>(byIndex);
	oQuery.AddParam<eTypeUINT8>((UINT8)eType);
	oQuery.AddParam<eTypeUINT64>(qwCounter);
	oQuery.AddParam<eTypeUINT64>(qwCounter);
	g_DBQueryMgr.DoModifyQuery(oQuery, [eType](INT8 byRet, UINT32 dwAffectRow){
		if(byRet != 0)
			CGUIDMgr::Instance().OnSaveFail(eType, byRet);
	});
}

const UINT32 SAVE_OFFSET = 100;
const UINT64 MAX_COUNTER = BIT_MASK(42);

CGUIDMgr* CGUIDMgr::_pGUIDMgr;

CGUIDMgr& CGUIDMgr::Instance()
{
	assert(_pGUIDMgr != nullptr);
	return *_pGUIDMgr;
}

void CGUIDMgr::Init(UINT16 wGroup, UINT8 byIndex, TFuncOnLoaded fnOnLoaded /*= nullptr*/)
{
	_wGroup = wGroup;
	_byIndex = byIndex;
	_fnOnLoaded = fnOnLoaded;
}

bool CGUIDMgr::InitType(const vector<EGUIDType>& vecType, bool bSave)
{
	for(EGUIDType eType : vecType)
	{
		SGUIDInfoPtr& pGUIDInfo = _arGUIDInfo[eType];
		if(pGUIDInfo == NULL)
			pGUIDInfo.reset(new SGUIDInfo);
		if(pGUIDInfo == NULL)
		{
			LOG_CRI << "pGUIDInfo is NULL!";
			return false;
		}
		if(bSave)
			pGUIDInfo->fnSaveGUID = OnOtherSaveGUID;
	}
	if(bSave)
		_setSaveType.insert(vecType.begin(), vecType.end());
	return true;
}

void CGUIDMgr::InitCounter(EGUIDType eType, UINT64 qwCounter)
{
	SGUIDInfoPtr& pGUIDInfo = _arGUIDInfo[eType];
	if(pGUIDInfo == NULL)
	{
		LOG_CRI << "pGUIDInfo is NULL!";
		return;
	}
	pGUIDInfo->qwSavedCounter = pGUIDInfo->qwCounter = qwCounter;
}

bool CGUIDMgr::LoadGUID()
{
	CQuery oQuery;
	oQuery.AddSQL("SELECT Type, Counter FROM tblmaxid WHERE Grp = %q AND Idx = %q;");
	oQuery.AddParam<eTypeUINT16>(_wGroup);
	oQuery.AddParam<eTypeUINT8>(_byIndex);
	return g_DBQueryMgr.DoSelectQuery(oQuery, [this](INT8 byRet, const TVecTable& vecTable){
		if(byRet != 0)
		{
			LOG_CRI << "LoadGUID fails!";
			return;
		}
		if(!vecTable.empty())
		{
			const STable& rTable = vecTable[0];
			for(size_t i = 0; i < rTable.Size(); ++i)
			{
				EGUIDType eType = GUID_NONE;
				UINT64 qwCounter = 0;
				rTable[i][0] >> (UINT8&)eType;
				rTable[i][1] >> qwCounter;
				if(_setSaveType.find(eType) != _setSaveType.end())
					InitCounter(eType, qwCounter);
			}
		}
		_bLoaded = true;
		if(_fnOnLoaded != nullptr)
			_fnOnLoaded();
	});
	return false;
}

UINT64 CGUIDMgr::GenGUID(EGUIDType eType)
{
	if(eType > GUID_MAX)
	{
#ifdef _DEBUG
		DebugBreak();
#endif
		LOG_CRI << "Invalid eType: " << eType;
		return 0;
	}
	SGUIDInfoPtr pGUIDInfo = _arGUIDInfo[eType];
	if(pGUIDInfo == NULL)
	{
#ifdef _DEBUG
		DebugBreak();
#endif
		LOG_CRI << "Invalid eType: " << eType;
		return 0;
	}
	if(!pGUIDInfo->bSaveSucceed)
	{
		LOG_CRI << "GUID save fails! eType: " << eType;
		return 0;
	}
	++pGUIDInfo->qwCounter;
	if(pGUIDInfo->qwCounter >= MAX_COUNTER - SAVE_OFFSET)
	{
		LOG_CRI << "GUID exceed max! eType: " << eType;
		return 0;
	}
	if(pGUIDInfo->qwCounter >= pGUIDInfo->qwSavedCounter)
	{
		pGUIDInfo->qwSavedCounter = pGUIDInfo->qwCounter + SAVE_OFFSET;
		if(pGUIDInfo->fnSaveGUID != nullptr)
			pGUIDInfo->fnSaveGUID(_wGroup, _byIndex, eType, pGUIDInfo->qwSavedCounter);
	}
	return GetGUID(_wGroup, _byIndex, eType, pGUIDInfo->qwCounter);
}

void CGUIDMgr::OnSaveFail(EGUIDType eType, UINT8 byRet)
{
	SGUIDInfoPtr pGUIDInfo = _arGUIDInfo[eType];
	assert(pGUIDInfo != NULL);
    // TODO:
	// pGUIDInfo->bSaveSucceed = false;
    LOG_CRI << "Save GUID ERROR with RET: " << (UINT32)byRet;
}

//GUID结构：
//[63 - 52], Group, 0 ~ 4096
//[51 - 46], Index, 0 ~ 64
//[45 - 42], Type, 0 ~ 16
//[41 - 0], Counter

UINT64 CGUIDMgr::GetGUID(UINT16 wGroup, UINT8 byIndex, EGUIDType eType, UINT64 qwCounter)
{
	return (UINT64)wGroup << 52 | (UINT64)byIndex << 46 | (UINT64)eType << 42 | qwCounter;
}

UINT16 CGUIDMgr::GetGroupId(UINT64 qwGUID)
{
	return EGUIDType(BIT_MASK(12) & (qwGUID >> 52));
}

EGUIDType CGUIDMgr::GetType(UINT64 qwGUID)
{
	return EGUIDType(BIT_MASK(4) & (qwGUID >> 42));
}

UINT8 CGUIDMgr::GetIndex(UINT64 qwGUID)
{
	return UINT8(BIT_MASK(6) & (qwGUID >> 46));
}

UINT64 CGUIDMgr::GetCounter(UINT64 qwGUID)
{
	return MAX_COUNTER & qwGUID;
}

