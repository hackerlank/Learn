#pragma once

//----------------------------
// CenterServer
//----------------------------

enum ETimePointType
{
	eTimePointStart = 0,

	eTimePointDaily0 = eTimePointStart,          // 每日0点触发
	eTimePointDaily1,                            // 每日1点触发
	eTimePointDaily2,                            // 每日2点触发
	eTimePointDaily3,                            // 每日3点触发
	eTimePointDaily4,                            // 每日4点触发
	eTimePointDaily5,                            // 每日5点触发

	eTimePointCount
};

// forward declare
struct STimePoint;

typedef void (*Callback)();
typedef bool (*CheckFunc)(time_t tNow, STimePoint& rTimePt);

struct STimePoint
{
	STimePoint() 
		: tLastTime(0)
		, pfnCheck(NULL)
	{}
	
	union
	{
		struct // used by daily
		{
			time_t tLastTime;
			int hour;
			int min;
			int sec;
		};

		struct  // used by weekly
		{
		};
	};

	void SetDailyTargetTime(int _hour, int _min, int _sec)
	{
		assert(_hour >= 0 && _hour < 24);
		assert(_min >= 0 && _min < 60);
		assert(_sec >= 0 && _sec < 60);
		hour = _hour; min = _min; sec = _sec;
	}

	CheckFunc pfnCheck;
	std::list<Callback> lstCallback;
};

class CTimePointMgr
{
public:
	static bool Init();
	static void Start();
	static void TimerCheck(time_t tNow);

	// add callback
	static void AddCallback(ETimePointType eType, Callback f);

private:
	static bool _bInit;
	static STimePoint _arrayTimePoint[];
	static bool _bRun;
};

