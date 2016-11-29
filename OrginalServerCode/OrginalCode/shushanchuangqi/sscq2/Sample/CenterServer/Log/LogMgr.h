#pragma once

typedef std::ostringstream SLogStream;

class CLogMgr
{
public:
	static CLogMgr& Instance();
	SLogStream& Stream();

	void LogUdpInfo(const std::string& strMsg);
private:
	CLogMgr();
	~CLogMgr();

	SLogStream _oStream;
};

