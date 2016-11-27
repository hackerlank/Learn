#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

//此文件是进一步包装excel打出来protobuf的类，方便程序中读取,类的命名规则为Conf_+需要包装的类,一定要包含一个key，此处的key可以自由发挥

#include <map>
#include "zType.h"
#include "Fir.h"
#include <set>
#include "pos.h"
#include <vector>
#include "InitRole.pb.h"
#include "ItemInfo.pb.h"

namespace pb
{
    //以tag来划开字符串
    void parseTagString(const std::string &src,const std::string &tag,std::vector<std::string> &retVec);
    //解析map
    void parseDWORDToDWORDMap(const std::string &src,std::map<DWORD,DWORD> &resultMap,const std::string &separatorTag = ",",const std::string &tag = "_");
    //解析vector
    void parseDWORDToVec(const std::string &src,std::vector<DWORD> &resultMap,const std::string &separatorTag = "_");
    //解析set
    void parseDWORDSet(const std::string &src,std::set<DWORD> &resultSet,const std::string &separatorTag = ",",const std::string &tag = "_");
    //解析map
    void parseStringToStringMap(const std::string &src,std::map<std::string,std::string> &resultMap,const std::string &separatorTag,const std::string &tag);
    //解析map<DWORD,std::map<DWORD,DWORD>>数据
    void parseDWORDToMapDWORD(const std::string &src,std::map<DWORD,std::map<DWORD,DWORD>> &resultMap,const std::string &separatorTag = ",",const std::string &tag = "_");

    //新角色属性表
    class Conf_t_InitRole
    {
        private:
            QWORD key;
            std::map<DWORD,DWORD> itemMap;
        public:
            inline QWORD getKey() const
            {
                return key;
            }
            inline const std::map<DWORD,DWORD>& getItemMap() const
            {
                return itemMap;
            }
        public:
            Conf_t_InitRole(const pb::InitRole::t_InitRole *_role) : role(_role) {};
            Conf_t_InitRole() : role(NULL) {};
            bool init();
        public:
            const pb::InitRole::t_InitRole *role;
    };

    //道具
    class Conf_t_ItemInfo
    {
        private:
            QWORD key;
        public:
            inline QWORD getKey() const
            {
                return key;
            }
        public:
            Conf_t_ItemInfo(const pb::ItemInfo::t_ItemInfo *_itemInfo) : itemInfo(_itemInfo) {};
            Conf_t_ItemInfo() : itemInfo(NULL) {};
            bool init();
        public:
            const pb::ItemInfo::t_ItemInfo *itemInfo;
    };
}


#endif



