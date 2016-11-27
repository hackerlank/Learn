#ifndef RECORD_CLIENT_H
#define RECORD_CLIENT_H

#include "base/baseTcpClientBuffer.h"
#include "base/baseAnalysisCmd.h"
#include "base/baseSubService.h"

class RecordClient : public TcpClientBufferQueue 
{
	public:
		friend class SubNetService;
		RecordClient(const std::string &name,const std::string &ip,const WORD port,const QWORD serverid);
		virtual ~RecordClient()
		{
		}
		bool connectToRecordServer();
		void run();
		bool msgParseStart(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
		bool broadCmdToScene(const void *cmd,const DWORD cmdLen);
		virtual bool msgParseForward(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
		bool msgParse(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
		void analysisSendingCmd(const BYTE cmd,const BYTE param,const DWORD cmdLen);
		void analysisRecvingCmd(const BYTE cmd,const BYTE param,const DWORD cmdLen);
		void switchCmdAnalysis(const bool switchOn);
	private:
		AnalysisCmd m_analysisSend;
		AnalysisCmd m_analysisRecv;
};

extern RecordClient *recordClient;

#endif
