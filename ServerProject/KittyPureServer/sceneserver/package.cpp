#include "package.h"
#include "tbx.h"
#include "SceneUser.h"
#include "extractProtoMsg.h"

Package::Package(SceneUser* u)
{
	m_owner = u;
}

Package::~Package()
{

}

void Package::reset()
{
    m_attrMap.clear();
    m_itemMap.clear();
}

bool Package::init(const std::map<DWORD,DWORD> &itemMap)
{
    addOrConsumeItem(itemMap,"新建角色",true);
    return true;
}


void Package::save(ProtoMsgData::Serialize& binary)
{
    for(auto iter = m_attrMap.begin(); iter != m_attrMap.end(); iter++)
    {
        ProtoMsgData::ItemInfo* item = binary.add_iteminfo();
        if(item)
        {
            item->set_id(iter->first);
            item->set_val(iter->second);
        }
    }
	for(auto iter = m_itemMap.begin(); iter != m_itemMap.end(); iter++)
    {
        ProtoMsgData::ItemInfo* item = binary.add_iteminfo();
        *item = iter->second;
    }
}

void Package::load(const ProtoMsgData::Serialize& binary)
{
    for(int index = 0; index < binary.iteminfo_size(); index++)
    {
        const ProtoMsgData::ItemInfo &item = binary.iteminfo(index);
        if(item.id() > ProtoMsgData::Attr_Max)
        {
            m_itemMap.insert(std::make_pair(item.id(),item));
        }
        else
        {
            m_attrMap.insert(std::pair<DWORD,DWORD>(item.id(),item.val()));
        }
    }
}

bool Package::addOrConsumeItem(const std::map<DWORD,DWORD> itemMap,const char *reMark,const bool opAdd,const bool logFlg)
{
    for(auto iter = itemMap.begin();iter != itemMap.end();++iter)
    {
        addOrConsumeItem(iter->first,iter->second,reMark,opAdd,logFlg);
    }
    return true;
}

bool Package::addOrConsumeItem(const DWORD itemID,const DWORD num,const char *reMark,const bool opAdd,const bool logFlg)
{
    const pb::Conf_t_ItemInfo *confBase = tbx::ItemInfo().get_base(itemID);
	if(NULL == confBase)
    {
        Fir::logger->error("%s(%u, %u)", __PRETTY_FUNCTION__,itemID,num);
		return false;
    }
    bool ret = false;
    DWORD oldNum = 0,newNum = num;
    if(itemID < ProtoMsgData::Attr_Max)
    {
        oldNum = m_attrMap.find(itemID) == m_attrMap.end() ? 0 : m_attrMap[itemID];
        ret = opAttrVal(ProtoMsgData::AttrType(itemID),num,opAdd);
        newNum = m_attrMap.find(itemID) == m_attrMap.end() ? 0 : m_attrMap[itemID];
        if(ret)
        {
            m_owner->updateAttrVal(ProtoMsgData::AttrType(itemID),m_attrMap[itemID]);
        }
    }
    else
    {
        oldNum = m_itemMap.find(itemID) == m_itemMap.end() ? 0 : m_itemMap[itemID].val();
        ret = addOrConsumeItem(itemID,num,opAdd);
        newNum = m_itemMap.find(itemID) == m_itemMap.end() ? 0 : m_itemMap[itemID].val();
        if(ret)
        {
            //flushItem(itemID);
        }
    }
    if(ret && logFlg)
    {
        Fir::logger->debug("[%s道具(%u)]:%lu,%s,%u,%u,%u",opAdd ? "增加" : "消耗",itemID,m_owner->charid,reMark,oldNum,num,newNum);
    }
    return ret;
}

bool Package::checkAttr(const ProtoMsgData::AttrType &attrID,const DWORD value)
{
    if(m_attrMap.find(attrID) == m_attrMap.end() || m_attrMap[attrID] < value)
    {
        return false;
    }
    return true;
}

DWORD Package::getAttr(const ProtoMsgData::AttrType &attrID)
{
    return m_attrMap.find(attrID) == m_attrMap.end() ? 0 : m_attrMap[attrID];
}

bool Package::opAttrVal(const ProtoMsgData::AttrType &attrID,const DWORD value,const bool opAdd)
{
    bool ret = true;
    if(opAdd)
    {
        if(m_attrMap.find(attrID) == m_attrMap.end())
        {
            m_attrMap.insert(std::pair<DWORD,DWORD>(attrID,value));
        }
        else
        {
            m_attrMap[attrID] += value;
        }
    }
    else
    {
        if(!checkAttr(attrID,value))
        {
            ret = false;
        }
        else
        {
            m_attrMap[attrID] -= value;
        }
    }
    return ret;
}

bool Package::addOrConsumeItem(const DWORD itemID,const DWORD num,const bool opAdd)
{
    bool ret = true;
	auto iter = m_itemMap.find(itemID);
    if(opAdd)
    {
        if(!hasEnoughSpace(itemID,num))
        {
            return false;
        }
        if(iter == m_itemMap.end())
        {
            ProtoMsgData::ItemInfo temp;
            temp.set_id(itemID);
            temp.set_val(num);
            m_itemMap.insert(std::make_pair(itemID,temp));
        }
        else
        {
            iter->second.set_val(iter->second.val() + num);
        }
    }
    else
    {
        if(iter == m_itemMap.end() || iter->second.val() < num)
        {
            ret = false;
        }
        else
        {
            iter->second.set_val(iter->second.val() - num);
        }
        if(!iter->second.val())
        {
            m_itemMap.erase(iter);
        }
    }
    return ret;
}

DWORD Package::getItemCount()
{
	DWORD itemcount = 0;
	for(auto iter = m_itemMap.begin(); iter != m_itemMap.end(); ++iter)
	{
        itemcount += iter->second.val();
	}
	return itemcount;
}

bool Package::hasEnoughSpace(const DWORD itemID,const DWORD itemcount)
{
    const pb::Conf_t_ItemInfo *confBase = tbx::ItemInfo().get_base(itemID);
	if(NULL == confBase)
    {
        Fir::logger->error("%s(%u, %u)", __PRETTY_FUNCTION__,itemID,itemcount);
		return false;
    }
    if(itemID <= ProtoMsgData::Attr_Max)
    {
        return true;
    }
	DWORD store_limit = getAttr(ProtoMsgData::Attr_Package_Size);
    DWORD cur_item_count = getItemCount();
    DWORD remain_space = store_limit > cur_item_count ? store_limit - cur_item_count : 0;
    return remain_space >= itemcount;
}

bool Package::hasEnoughItem(const DWORD itemid, const DWORD itemcount)
{
	auto iter = m_itemMap.find(itemid);
	if(iter == m_itemMap.end())
	{
		return false;
	}
    return iter->second.val() >= itemcount;
}

bool Package::hasEnoughSpace(const std::map<DWORD,DWORD>&itemMap)
{
    DWORD needSpace = 0;
    for(auto iter = itemMap.begin();iter != itemMap.end();++iter)
    {
        const pb::Conf_t_ItemInfo *confBase = tbx::ItemInfo().get_base(iter->first);
        if(NULL == confBase)
        {
            Fir::logger->error("%s(%u, %u)", __PRETTY_FUNCTION__,iter->first,iter->second);
            return false;
        }
        if(iter->first <= ProtoMsgData::Attr_Max) 
        {
            continue;
        }
        needSpace += iter->second;
    }
	DWORD store_limit = getAttr(ProtoMsgData::Attr_Package_Size);
    DWORD cur_item_count = getItemCount();
    DWORD remain_space = store_limit > cur_item_count ? store_limit - cur_item_count : 0;
    return remain_space >= needSpace;
}
