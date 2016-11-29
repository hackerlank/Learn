#ifndef DBEXCHANGEDITEMTABLE_H_
#define DBEXCHANGEDITEMTABLE_H_

#include "GuildProt.h"
using namespace NGuildProt;

class CDBGuildExchangedItemTable
{ 
    public:
        void AddGuildExchangedItem(const SGuildExchangedItem& sGuildExchangedItem);
        
        void UpdateGuildExchangedItem(const SGuildExchangedItem& sGuildExchangedItem);

        void DelGuildExchangedItem();
        
        void LoadGuildExchangedItem();
};
extern CDBGuildExchangedItemTable g_CDBGuildExchangedItemTable;

#endif
