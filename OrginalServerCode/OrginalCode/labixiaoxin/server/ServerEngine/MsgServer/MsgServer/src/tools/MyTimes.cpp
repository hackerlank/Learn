#include "MyTimes.h"
#include <boost/date_time/posix_time/posix_time.hpp>

MY_UINT32 CMyTimes::get_utc()
{
	return (MY_UINT32)std::time(NULL);
	//return std::mktime(&boost::posix_time::to_tm(boost::posix_time::second_clock::local_time()));
	//std::cout<<boost::posix_time::to_simple_string(boost::posix_time::second_clock::universal_time());
}

