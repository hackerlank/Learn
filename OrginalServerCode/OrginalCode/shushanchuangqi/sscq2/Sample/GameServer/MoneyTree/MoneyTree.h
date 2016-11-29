#ifndef _MONEYTREE_H_
#define _MONEYTREE_H_
#include "MoneyTreeProt.h"

using namespace NMoneyTreeProt;

class CMoneyTree : public CPoolObj<CMoneyTree>
{
public:

   CMoneyTree(CPlayer& rPlayer): _rPlayer(rPlayer) {}
   ~CMoneyTree() {}

public:
   
   void GetMoneyTreeInfo(UINT16& wTodayUseCount); 
   
   bool GetMoney(UINT16& wTodayUseCount); 

private:

   CPlayer& _rPlayer;

};

#endif // _MONEYTREE_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

