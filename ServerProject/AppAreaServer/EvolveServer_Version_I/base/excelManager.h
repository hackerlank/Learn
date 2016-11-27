#ifndef EXCEL_MANAGER_H
#define EXCEL_MANAGER_H
#include "head.h"
#include "Init.pb.h"
#include "Attr.pb.h"
#include "attr.pb.h"

namespace ExcelConf
{
    enum DataType
    {
        DT_Int = 0 , //整数
        DT_String = 1, //字符串
    };

    //解析string到vec
    void parseTagString(const std::string &src,std::vector<std::string> &retVec,const std::string &tag);
    bool parseIntToIntMap(const std::string &src,std::map<unsigned int,unsigned int> &retMap,const std::string &midTag = "-",const std::string &endTag = ";");
    bool parseIntToStringMap(const std::string &src,std::map<unsigned int,std::string> &retMap,const std::string &midTag = "-",const std::string &endTag = ";");
    bool parseStringToStringMap(const std::string &src,std::map<std::string,std::string> &retMap,const std::string &midTag = "-",const std::string &endTag = ";");
    bool parseAttrMap(const std::string &src,std::map<ProtoMsgData::AttrType,unsigned int> &retMap,const std::string &midTag = "-",const std::string &endTag = ";");

    class Conf_t_Init
    {
        private:
            unsigned long m_key;
            std::map<ProtoMsgData::AttrType,unsigned int> m_attrMap;
        public:
            inline unsigned long getKey() const
            {
                return m_key;
            }
            inline const std::map<ProtoMsgData::AttrType,unsigned int>& getAttrMap() const
            {
                return m_attrMap;
            }
        public:
            Conf_t_Init(const ExcelConf::Init::t_Init *_init) : m_init(_init) {};
            Conf_t_Init() : m_init(NULL) {};
            bool init();
        public:
            const ExcelConf::Init::t_Init *m_init;
    };

    class Conf_t_Attr
    {
        private:
            unsigned long m_key;
        public:
            inline unsigned long getKey() const
            {
                return m_key;
            }
        public:
            Conf_t_Attr(const ExcelConf::Attr::t_Attr *_attr) : m_attr(_attr) {};
            Conf_t_Attr() : m_attr(NULL) {};
            bool init();
        public:
            const ExcelConf::Attr::t_Attr *m_attr;
    };



}



#endif
