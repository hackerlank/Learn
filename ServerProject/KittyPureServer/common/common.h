#ifndef _COMMON_H_
#define _COMMON_H_

#include <string>
#include "Fir.h"

#pragma pack(1)

namespace CMD
{ 
    struct stSaleCell
    {
        DWORD cellid;
        DWORD itemid;
        DWORD itemcount;
        DWORD status; // 0空 1放上物品 2已售
        char nickname[MAX_NAMESIZE]; // 购买者的名字
        stSaleCell()
        {
            bzero(this,sizeof(*this));
        }
    };

}
#pragma pack()
#define ISSTATICNPC(ID) (ID > 0 && ID <= 10)
#define ACTIVECNPCMin 11
#define ACTIVECNPCMAx 100
#define ISACTIVECNPC(ID) (ID >= ACTIVECNPCMin && ID <= ACTIVECNPCMAx)
#ifdef _MSC_VER
#pragma warning( pop )
#endif
#endif
