#pragma once
#include "Point.h"

class CCreature;

enum EWalkState
{
	eWalkStop,
	eWalkMove
};

class CWalker
{
	friend class CWalkerMgr;
public:
	CWalker(CCreature& rCreature) : _rCreature(rCreature), _dwTimeIntervel(0), _dwStartMoveTick(0), _dwLastMoveTick(0),
		_dwTotalMoveTick(0), _dwLastDiffTick(0), _eWalkState(eWalkStop), _bCheckBlock(false), _fMoveSpeed(0), _fDir(0),
		/*_fDiffDistance(0),*/_dwCurIndex(0), _dwPreIndex(0), _dwWalkerMapIndex(0),_dwLastMoveTime(0) { }

	void SetPath(const vector<SPoint>& rVecPoint);
	bool CheckPath(vector<SPoint>& rVecPoint);
	bool StartPath(vector<SPoint>& rVecPoint, UINT32 dwTimeIntervel, bool bCheckBlock = true);
	void ClearPath();
	bool HasPath() const { return !_vecPoint.empty(); }
	void Abort(UINT32 dwTickCount = GetTickCount());
	bool TimerCheck(UINT32 dwTickCount);
	EWalkState GetState() const { return _eWalkState; }
	CCreature& GetCreature() { return _rCreature; }
	UINT32 GetLastMoveTick() const { return _dwLastMoveTick; }
	UINT32 GetTotalMoveTick(UINT32 dwTickCount) const;
	UINT32 GetCurIndex() const { return _dwCurIndex; }
	bool IsDestIndex() const { return _dwCurIndex >= _vecPoint.size() - 2; }
	const vector<SPoint>& GetPath() const { return _vecPoint; }
	void GetCurPath(vector<SPoint>& rVecPathPoint);
	bool GetDestPoint(SPoint& rDestPoint);
	SPoint* GetCurDestPoint();
	float GetDirection() const { return _fDir; }
	bool CheckBlock() const { return _bCheckBlock; }
	float GetStepLength() const { return _fMoveSpeed * _dwTimeIntervel / 1000; }
	bool IsStepBlocked();
    bool TrySetCurPoint(const SPoint & rPoint); 
    SPoint GetCurPoint(){return _oCurPoint;}

    bool CheckAndSetLastMoveTime();

protected:
	bool GetCurPoint(UINT32 dwTickCount);
	bool OnStep(UINT32 dwTickCount, bool bAbort = false);
	bool Continue(UINT32 dwTickCount);

	CCreature& _rCreature;
	UINT32 _dwTimeIntervel;
	UINT32 _dwStartMoveTick;
	UINT32 _dwLastMoveTick;
	UINT32 _dwTotalMoveTick;
	UINT32 _dwLastDiffTick;
	EWalkState _eWalkState;
	bool _bCheckBlock;

	float _fMoveSpeed;
	float _fDir; //客户端显示方向
	//float _fDiffDistance;
	UINT32 _dwCurIndex;
	UINT32 _dwPreIndex;
	SPoint _oCurPoint;
	SPoint _oPrePoint;
	vector<SPoint> _vecPoint;
	vector<float> _vecDistance;

	UINT32 _dwWalkerMapIndex;

    UINT32 _dwLastMoveTime;
};

class CWalkerMgr
{
public:
	static UINT32 SelectMapIndex();
	static void AddWalker(CWalker& rWalker);
	static void DelWalker(CWalker& rWalker);
	static void TimerCheck(UINT32 dwIndex);
private:
	static map<UINT64, CWalker*> _arWalkerMap[];
};
