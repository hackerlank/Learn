#include "excelManager.h"
#include "flyer.h"

namespace ExcelConf
{
    void parseTagString(const std::string &src,std::vector<std::string> &retVec,const std::string &tag)
    {
        std::string parseSrc = src;
        size_t pos = parseSrc.find(tag);
        while(pos != std::string::npos)
        {
            size_t len = parseSrc.length();
            retVec.push_back(parseSrc.substr(0,pos));
            parseSrc = parseSrc.substr(pos+1,len-pos-1);
            pos = parseSrc.find(tag);
        }
        if(parseSrc.size())
        {
            retVec.push_back(parseSrc);
        }
    }

    bool parseIntToIntMap(const std::string &src,std::map<unsigned int,unsigned int> &retMap,const std::string &midTag,const std::string &endTag)
    {
        bool ret = false;
        do
        {
            bool flag = true;
            std::vector<std::string> sectionVec;
            parseTagString(src,sectionVec,endTag);
            for(auto iter = sectionVec.begin();iter != sectionVec.end();++iter)
            {
                const std::string &temp = *iter;
                std::vector<std::string> vec;
                parseTagString(temp,vec,midTag);
                if(vec.size() != 2)
                {
                    Error(Flyer::logger,"[加载Excel] (" << src << ")");
                    flag = false;
                    break;
                }
                unsigned int key = atol(vec[0].c_str());
                unsigned int val = atol(vec[1].c_str()); 
                retMap.insert(std::pair<unsigned int,unsigned int>(key,val));
            }
            ret = flag;
        }while(false);
        return ret;
    }

    bool parseIntToStringMap(const std::string &src,std::map<unsigned int,std::string> &retMap,const std::string &midTag,const std::string &endTag)
    {
        bool ret = false;
        do
        {
            bool flag = true;
            std::vector<std::string> sectionVec;
            parseTagString(src,sectionVec,endTag);
            for(auto iter = sectionVec.begin();iter != sectionVec.end();++iter)
            {
                const std::string &temp = *iter;
                std::vector<std::string> vec;
                parseTagString(temp,vec,midTag);
                if(vec.size() != 2)
                {
                    Error(Flyer::logger,"[加载Excel] (" << src << ")");
                    flag = false;
                    break;
                }
                unsigned int key = atol(vec[0].c_str());
                retMap.insert(std::pair<unsigned int,std::string>(key,vec[1]));
            }
            ret = flag;
        }while(false);
        return ret;
    }

    bool parseStringToStringMap(const std::string &src,std::map<std::string,std::string> &retMap,const std::string &midTag,const std::string &endTag)
    {
        bool ret = false;
        do
        {
            bool flag = true;
            std::vector<std::string> sectionVec;
            parseTagString(src,sectionVec,endTag);
            for(auto iter = sectionVec.begin();iter != sectionVec.end();++iter)
            {
                const std::string &temp = *iter;
                std::vector<std::string> vec;
                parseTagString(temp,vec,midTag);
                if(vec.size() != 2)
                {
                    Error(Flyer::logger,"[加载Excel] (" << src << ")");
                    flag = false;
                    break;
                }
                retMap.insert(std::pair<std::string,std::string>(vec[0],vec[1]));
            }
            ret = flag;
        }while(false);
        return ret;
    }

    bool parseAttrMap(const std::string &src,std::map<ProtoMsgData::AttrType,unsigned int> &retMap,const std::string &midTag,const std::string &endTag)
    {
        bool ret = false;
        do
        {
            bool flag = true;
            std::vector<std::string> sectionVec;
            parseTagString(src,sectionVec,endTag);
            for(auto iter = sectionVec.begin();iter != sectionVec.end();++iter)
            {
                const std::string &temp = *iter;
                std::vector<std::string> vec;
                parseTagString(temp,vec,midTag);
                if(vec.size() != 2)
                {
                    Error(Flyer::logger,"[加载Excel] (" << src << ")");
                    flag = false;
                    break;
                }
                unsigned int key = atol(vec[0].c_str());
                unsigned int val = atol(vec[1].c_str()); 
                ProtoMsgData::AttrType attrID = ProtoMsgData::AttrType(key);
                retMap.insert(std::pair<ProtoMsgData::AttrType,unsigned int>(attrID,val));
            }
            ret = flag;
        }while(false);
        return ret;
    }

    bool Conf_t_Init::init()
    {
        bool ret = false;
        do
        {
            m_key = m_init ? m_init->id() : 0;
            if(!m_key)
            {
                break;
            }
            if(!parseAttrMap(m_init->attr(),m_attrMap))
            {
                break;
            }
            ret = true;
        }while(false);
        return ret;
    }

    bool Conf_t_Attr::init()
    {
        bool ret = false;
        do
        {
            m_key = m_attr ? m_attr->id() : 0;
            if(!m_key)
            {
                break;
            }
            ret = true;
        }while(false);
        return ret;
    }
}
