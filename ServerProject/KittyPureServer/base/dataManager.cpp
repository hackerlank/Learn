#include "dataManager.h"
#include "key.h"
#include "zMisc.h"
#include "tbx.h"
#include "zTime.h"

namespace pb
{
    void parseTagString(const std::string &src,const std::string &tag,std::vector<std::string> &retVec)
    {
        std::string parseSrc = src;
        for(size_t pos = parseSrc.find(tag);pos != std::string::npos;)
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
    void parseDWORDToMapDWORD(const std::string &src,std::map<DWORD,std::map<DWORD,DWORD>> &resultMap,const std::string &separatorTag,const std::string &tag)
    {
        std::vector<std::string> tempVec;
        parseTagString(src,separatorTag,tempVec);
        for(auto iter = tempVec.begin();iter != tempVec.end();++iter)
        {
            std::vector<std::string> temp;
            parseTagString(*iter,tag,temp);
            if(temp.size() != 2)
            {
                continue;
            }
            DWORD type = atol(temp[0].c_str());
            DWORD tempID = atol(temp[1].c_str());
            DWORD tempVal = atol(temp[2].c_str());
            auto it = resultMap.find(type);
            if(it == resultMap.end())
            {
                std::map<DWORD,DWORD> tempMap;
                tempMap.insert(std::pair<DWORD,DWORD>(tempID,tempVal));
                resultMap.insert(std::pair<DWORD,std::map<DWORD,DWORD>>(type,tempMap));
            }
            else
            {
                std::map<DWORD,DWORD> &tempMap = const_cast<std::map<DWORD,DWORD>&>(it->second);
                if(tempMap.find(tempID) == tempMap.end())
                {
                    tempMap.insert(std::pair<DWORD,DWORD>(tempID,tempVal));
                }
                else
                {
                    tempMap[tempID] += tempVal;
                }
            }
        }
    }

    void parseDWORDToDWORDMap(const std::string &src,std::map<DWORD,DWORD> &resultMap,const std::string &separatorTag,const std::string &tag)
    {
        std::vector<std::string> strVec;
        std::string parseSrc = src;
        parseTagString(parseSrc,separatorTag,strVec);
        if(strVec.empty())
        {
            return;
        }

        for(size_t index = 0;index < strVec.size();++index)
        {
            std::vector<std::string> tempVec;
            parseTagString(strVec[index],tag,tempVec);
            if(tempVec.size() != 2)
            {
                continue;
            }

            int key = atol(tempVec[0].c_str());
            if(resultMap.find(key) != resultMap.end())
            {
                continue;
            }
            resultMap.insert(std::pair<DWORD,DWORD>(key,atol(tempVec[1].c_str())));
        }
    }

    void parseDWORDToVec(const std::string &src,std::vector<DWORD> &resultVec,const std::string &separatorTag)
    {
        std::vector<std::string> strVec;
        std::string parseSrc = src;
        parseTagString(parseSrc,separatorTag,strVec);
        if(strVec.empty())
        {
            return;
        }

        for(size_t index = 0;index < strVec.size();++index)
        {
            DWORD val = atol(strVec[index].c_str());
            resultVec.push_back(val);
        }
    }


    void parseDWORDSet(const std::string &src,std::set<DWORD> &resultSet,const std::string &separatorTag,const std::string &tag)
    {
        std::vector<std::string> strVec;
        std::string parseSrc = src;
        parseTagString(parseSrc,separatorTag,strVec);
        if(strVec.empty())
        {
            return;
        }

        for(size_t index = 0;index < strVec.size();++index)
        {
            std::vector<std::string> tempVec;
            parseTagString(strVec[index],tag,tempVec);
            int key = atol(tempVec[0].c_str());
            if(resultSet.find(key) != resultSet.end())
            {
                continue;
            }
            resultSet.insert(key);
        }
    }

    void parseStringToStringMap(const std::string &src,std::map<std::string,std::string> &resultMap,const std::string &separatorTag,const std::string &tag)
    {
        std::vector<std::string> strVec;
        std::string parseSrc = src;
        parseTagString(parseSrc,separatorTag,strVec);
        if(strVec.empty())
        {
            return;
        }

        for(size_t index = 0;index < strVec.size();++index)
        {
            std::vector<std::string> tempVec;
            parseTagString(strVec[index],tag,tempVec);
            if(tempVec.size() != 2)
            {
                continue;
            }

            if(resultMap.find(tempVec[0]) != resultMap.end())
            {
                continue;
            }
            resultMap.insert(std::pair<std::string,std::string>(tempVec[0],tempVec[1]));
        }
    }

    bool Conf_t_InitRole::init()
    {
        key = role ? role->tbxid() : 0;
        parseDWORDToDWORDMap(role->inititem(),itemMap);
        return key;
    }

    bool Conf_t_ItemInfo::init()
    {
        key = itemInfo ? itemInfo->id() : 0;
        return true;
    }
}


