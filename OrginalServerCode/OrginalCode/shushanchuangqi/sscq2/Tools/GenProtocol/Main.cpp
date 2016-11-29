/********************************************************************
//	Communication Protocol Generation Tool Source File.
//	File name:	Main.cpp
//	Created:	2011/06/03	15:00
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
#ifdef _WIN32
#include <Windows.h>
#else
#include "Utility/Linux.h"
#endif
#include <iostream>
#include "Document.h"

int main(int argc, char* argv[])
{
	if(argc < 4)
	{
		cerr << "parameters are not sufficient!" << endl;
		return 1;
	}
    int iQuite = atoi(argv[1]);
	char* szXMLFile = argv[2];
	char* szDestDir = argv[3];

	string strDir = szXMLFile;
#ifdef _WIN32
	size_t pos = strDir.find_last_of('\\');
#else
	size_t pos = strDir.find_last_of('/');
#endif
	CDocument doc;
	doc.SetDir(strDir.substr(0, pos + 1));
	if(!doc.ParseXML(szXMLFile))
	{
		cerr << "parse XML file: " << szXMLFile << " fails!" << endl;
		return 1;
	}
	if(!doc.GenCodeFile(szDestDir))
	{
		cerr << "Generate C++ code file in directory: " << szDestDir << " fails!" << endl;
		return 2;
	}
	if(!doc.GenPHP(szDestDir))
	{
		cerr << "Generate PHP code file in directory: " << szDestDir << " fails!" << endl;
		return 3;
	}
	if(!doc.GenRuby(szDestDir))
    {
		cerr << "Generate Ruby code file in directory: " << szDestDir << " fails!" << endl;
        return 4;
    }
	if(argc >= 5)
	{
		char* szPkg = argv[4];
		if(!doc.GenActionScript(szDestDir, szPkg))
		{
			cerr << "Generate ActionScript code file in directory: " << szDestDir <<  " fails!" << endl;
			return 5;
		}
	}
    if (iQuite)
        cout << "Generate code for protocol " << szXMLFile << " succeeds!" << endl;
	return 0;
}

