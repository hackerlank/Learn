/********************************************************************
//	Log Server Source File.
//	File name:	NetMgr.cpp
//	Created:	2011/12/26	14:00
//	Organization:	
//	Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
//	Author:		Jingyuan Wang
//	E-Mail:		tyketom@hotmail.com
//	Http://
// ------------------------------------------------------------------
//	Purpose:	
//	Version:	1.0
//	Histroy:
 *********************************************************************/

#include "stdafx.h"

bool CLogNetMgr::OnUserLogic()
{
    bool bBusy = CDBMgr::Instance().ProcessResult();
    return bBusy;
}

