#ifndef EXCEL_MANAGER_H
#define EXCEL_MANAGER_H
#include "Business.pb.h"

namespace ExcelConf
{
    class Conf_t_Business
    {
        private:
            unsigned long key;
        public:
            inline unsigned long getKey() const
            {
                return key;
            }
        public:
            Conf_t_Business(const ExcelConf::Business::t_Business *_business) : business(_business) {};
            Conf_t_Business() : business(NULL) {};
            bool init();
        public:
            const ExcelConf::Business::t_Business *business;
    };

}



#endif
