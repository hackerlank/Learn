#ifndef PACKAGE_H 
#define PACKAGE_H 

#include "zType.h"
#include "CharBase.h"
#include <map>
#include <set>
#include <bitset>
#include "serialize.pb.h"
#include "Fir.h"
#include "dataManager.h"
#include "common.pb.h"
#include "item.pb.h"

class SceneUser;
class Package
{
	public:
		Package(SceneUser* u);
		~Package();
        //序列化保存数据
		void save(ProtoMsgData::Serialize& binary);
        //反序列化加载数据
		void load(const ProtoMsgData::Serialize& binary);
        //增加道具
        bool addOrConsumeItem(const std::map<DWORD,DWORD> itemMap,const char *reMark,const bool opAdd = true,const bool logFlg = true);
	    //增加或者消耗道具接口(包括属性)	
        bool addOrConsumeItem(const DWORD itemID,const DWORD num,const char *reMark,const bool opAdd = true,const bool logFlg = true);
        //是否有足够道具
		bool hasEnoughItem(const DWORD itemid, const DWORD itemcount);
        //仓库空间是否足够
        bool hasEnoughSpace(const DWORD itemID,const DWORD itemcount);
        //库空间是否足够
        bool hasEnoughSpace(const std::map<DWORD,DWORD>&itemMap);
        //初始化仓库信息
        bool init(const std::map<DWORD,DWORD> &itemMap);        
        //获得属性值
        DWORD getAttr(const ProtoMsgData::AttrType &attrID);
        //检测属性值足够
        bool checkAttr(const ProtoMsgData::AttrType &attrID,const DWORD value);
    private:
        //增加或者消耗道具接口(不包含属性,外部慎用)
        bool addOrConsumeItem(const DWORD itemID,const DWORD num,const bool opAdd = true);
        //获得仓库现有道具数量
        DWORD getItemCount();
        //重置数据
        void reset();
        //操作属性函数
        bool opAttrVal(const ProtoMsgData::AttrType &attrID,const DWORD value,const bool opAdd = true);
	private:
		SceneUser* m_owner;
        // 仓库道具
		std::map<DWORD,ProtoMsgData::ItemInfo> m_itemMap; 
        //属性数值
        std::map<DWORD,DWORD> m_attrMap;
};

#endif

