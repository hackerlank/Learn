#include "excelManager.h"

namespace ExcelConf
{
    bool Conf_t_Business::init()
    {
        key = business ? business->tbxid() : 0;
        return key;
    }
}
