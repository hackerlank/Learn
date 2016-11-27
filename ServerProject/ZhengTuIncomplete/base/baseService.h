#ifndef BASE_SERVICE_H
#define BASE_SERVICE_H

#include "baseEntry.h"
#include "baseClass.h"
#include "baseSqlPool.h"
#include "baseSqlRecord.h"

class Service : public Entry,public SingletonBase<Service,false>
{
	public:
		friend class SingletonBase<Service,false>;
		virtual ~Service()
		{
		}
		virtual void reloadConfig()
		{
		}
		bool isTerminate() const
		{
			return m_terminate;
		}
		void Terminate()
		{
			m_terminate = true;
		}
		virtual void TerminateWait()
		{
			m_terminate = true;
		}
		void loop();
		const char *getClassName() const
		{
			return "服务器";
		}
		bool checkZoneInfo(MysqlPool *pool,const char *ip,const WORD port);
//		Properties env;
	protected:
		Service(const std::string &name)
		{
			strncpy(this->name,name.c_str(),sizeof(this->name));
			m_terminate = false;
		}
		virtual bool init();
		virtual bool validate()
		{
			return true;
		}
		virtual bool serviceCallBack() = 0;
		virtual void final() = 0;
	private:
		bool m_terminate;
	public:
		static DWORD s_buildTime;
		static DWORD s_svnVersion;
};

#endif
