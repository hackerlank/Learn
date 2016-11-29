#pragma once

struct SSvrInfo
{
	EHostType eHostType;
	UINT32 dwSvrID;
	UINT16 wPort;
	UINT32 dwUsrCnt;
	map<UINT8, string> mapType2Addr;

	SSvrInfo() : eHostType(eHostNone), dwSvrID(0), wPort(0), dwUsrCnt(0) { }
};

class CSvrInfoMgr
{
public:
	static void AddSvrInfo(SSvrInfo& rSvrInfo);
	static UINT32 GetTotalUsrCnt();
	static SSvrInfo* GetSvrInfo(UINT32 dwSvrID);
	static void GetSvrInfo(EHostType eHostType, vector<SSvrInfo>& rVecSvrInfo);
	static SSvrInfo* GetMinUsrSvrInfo(EHostType eHostType);
	static map<UINT32, SSvrInfo>& GetSvrList() { return _mapID2SvrInfo; }
private:
	static UINT32 _dwTotalUsrCnt;
	static map<UINT32, SSvrInfo> _mapID2SvrInfo;
};