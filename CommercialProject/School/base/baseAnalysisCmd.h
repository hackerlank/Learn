#ifndef BASE_ANALYSIS_CMD_H
#define BASE_ANALYSIS_CMD_H

#include <iostream>
#include <map>
#include "common/baseDef.h"
#include "baseFunc.h"

using namespace std;

class AnalysisCmd
{
	private:
		std::map<DWORD,DWORD> m_cmdMap;
		char m_name[MAX_NAMESIZE];
		bool m_switchOn;
	public:
		AnalysisCmd(const char *name,const bool switchOn = false) : m_switchOn(switchOn)
		{
			bzero(m_name,sizeof(m_name));
			if(name)
			{
				strncpy(m_name,name,sizeof(m_name));
			}
		}

		void setSwitch(const bool switchFlg)
		{
			m_switchOn = switchFlg;
		}
		
		bool getSwitch()
		{
			return m_switchOn;
		}

		void addCmd(const BYTE byCmd,const BYTE byParam,const DWORD cmdLen)
		{
			CheckConditonVoid(m_switchOn);
			DWORD key = 16<<byCmd + byParam;
			if(m_cmdMap.find(key) == m_cmdMap.end())
			{
				m_cmdMap[key] = cmdLen;
			}
			else
			{
				m_cmdMap[key] += cmdLen;
			}
		}
};

#endif

