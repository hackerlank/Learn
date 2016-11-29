#ifndef DBNOTICETATABLE_H_
#define DBNOTICETATABLE_H_

#include "PHPProt.h"
using namespace NPHPProt;

class CDBNoticeTable
{ 
    public:
        void AddNotice(const SNotice& sNotice);
        
        void DelNotice(UINT32 dwNoticeID);
        
        void LoadNotice();
};
extern CDBNoticeTable g_CDBNoticeTable;
#endif
