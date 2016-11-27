#ifndef BASE_SUPER_CLIENT_H
#define BASE_SUPER_CLIENT_H

#include "baseTcpClientBuffer.h"
#include "baseSubService.h"

class SuperClient : public TcpClientBufferQueue
{
	public:
		friend class SubNetService;
		SuperClient();
		virtual ~SuperClient();

		void run();
		bool msgParseStart(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
		virtual bool msgParseForward(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
		bool msgParse(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
	private:
		bool m_verify;
};

#endif
