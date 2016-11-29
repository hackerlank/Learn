#include "stdafx.h"
#include "ServiceDateMgr.h"

#define BUFF_SIZE 64

time_t CServiceDateMgr::_tServiceDate;
bool CServiceDateMgr::Init()
{
	string strPath = Config._strConfigDir + "/ServiceDate.txt";
	ifstream ifs(strPath.c_str());
	if(!ifs)
	{
		ofstream ofs(strPath.c_str());
		if(!ofs)
			return false;
		time_t tCurTime = time(NULL);
		tm tmCurDate;
		localtime_s(&tmCurDate, &tCurTime);
		char szBuff[BUFF_SIZE] = {0};
		if(-1 == sprintf(szBuff, "%4d-%02d-%02d", tmCurDate.tm_year + 1900, tmCurDate.tm_mon + 1, tmCurDate.tm_mday))
			return false;
		ofs.write(szBuff, BUFF_SIZE);
		tmCurDate.tm_hour = tmCurDate.tm_min = tmCurDate.tm_sec = 0;
		_tServiceDate = mktime(&tmCurDate);
		return true;
	}
	char szBuff[BUFF_SIZE] = {0};
	ifs.read(szBuff, BUFF_SIZE - 1);
	tm tmDate;
	memset(&tmDate, 0, sizeof(tm));
	if(-1 == sscanf(szBuff, "%4d-%2d-%2d", &tmDate.tm_year, &tmDate.tm_mon, &tmDate.tm_mday))
		return false;
	tmDate.tm_year -= 1900;
	tmDate.tm_mon -= 1;
	tmDate.tm_isdst = -1;
	_tServiceDate = mktime(&tmDate);
	return true;
}

time_t CServiceDateMgr::GetServiceDate()
{
	return _tServiceDate;
}


#undef BUFF_SIZE