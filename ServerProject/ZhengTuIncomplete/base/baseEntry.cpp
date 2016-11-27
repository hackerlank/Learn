#include "baseEntry.h"

Entry::Entry():id(0),tempid(0)
{
	bzero(name,sizeof(name));
}

Entry::Entry(const DWORD _id):id(_id),tempid(0)
{
	bzero(name,sizeof(name));
}

Entry::Entry(const DWORD _id,const char *_name):id(_id),tempid(0)
{
	bzero(name,sizeof(name));
	strncpy(name,_name,sizeof(name));
}



