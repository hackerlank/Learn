#ifndef AUTO_LIFE_HOOK_H
#define AUTO_LIFE_HOOK_H

#include "boost/weak_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "boost/noncopyable.hpp"

class AutoLifeHook;

typedef boost::weak_ptr<AutoLifeHook> SafePtr;

class AutoLifeHook : public boost::enable_shared_from_this<AutoLifeHook>,public boost::noncopyable
{
	private:
		struct Done
		{
			void operator() ( AutoLifeHook *ptr ){}
		};
	protected:
		AutoLifeHook()
		{
			shared_ptr.reset( this,Done() );
		}
		boost::shared_ptr<AutoLifeHook> shared_ptr;
	public:
		SafePtr getWeakPtr() const
		{
			return shared_ptr;
		}
};

#endif
