#pragma once

class CServiceDateMgr
{
public:
	static bool Init();
	static time_t GetServiceDate();

private:
	static time_t _tServiceDate;
};
