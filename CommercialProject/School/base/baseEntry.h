#ifndef BASE_ENTRY_H
#define BASE_ENTRY_H
#include <ext/hash_map>
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
using namespace std;

#include "common/baseDef.h"
#include "baseClass.h"
#include "global.h"
#include "baseFunc.h"


class Entry : private Noncopyable
{
	public:
		union
		{
			DWORD id;
			struct
			{
				//低16位
				WORD wid1;
				//高16位
				WORD wid2;
			};
			struct
			{
				//低8位
				BYTE cid1;
				//低16位
				BYTE cid2;
				//底24位
				BYTE cid3;
				//32位
				BYTE cid4;
			};
		};
		union
		{
			DWORD tempid;
			struct
			{
				WORD tempid1;
				WORD tempid2;
			};
		};
		char name[MAX_NAME_SIZE];
		Entry();
		Entry(const DWORD id);
		Entry(const DWORD id,const char* name);
		virtual ~Entry() {};
};

/**
* \brief 回调函数类模板
*/
template <typename T,typename RTValue = bool>
struct EntryCallBack
{
	virtual RTValue exec(T *e)=0;
	virtual ~EntryCallBack(){};
};

 /**
 * \brief key值等值比较,目前支持 (DWORD,char *)，两>    种类型
 */
 template <class keyT>
 struct key_equal : public std::binary_function<keyT,keyT,bool>
 {
 	inline bool operator()(const keyT s1,const keyT s2) const;
};

/**
* \brief 模板偏特化
* 对字符串进行比较
*/
template<>
inline bool key_equal<const char *>::operator()(const char * s1,const char * s2) const
{
	return strcmp(s1,s2) == 0;
}

/**
* \brief 模板偏特化
* 对整数进行比较
*/
template<>
inline bool key_equal<DWORD>::operator()(const DWORD s1,const DWORD s2) const
{
	return s1  == s2;
}

template<class YourEntry>
struct RemoveEntry_Pred
{
	std::vector<YourEntry*> removeVec;
	virtual bool isIt(YourEntry *entry) = 0;
	virtual ~RemoveEntry_Pred()
	{
	}
};

/**
* \brief 有限桶Hash管理模板,非线程安全
** 目前支持两种key类型(DWORD,char *),value类型不作限 制,但此类型要可copy的。
* \param keyT key类型(DWORD,char *)
* \param valueT value类型
*/

 template <class keyT,class valueT>
 class LimitHash : private Noncopyable
 {
 	protected:
		/**
		* \brief hash_map容器
		*/
		typedef __gnu_cxx::hash_map<keyT,valueT,__gnu_cxx::hash<keyT>,key_equal<keyT> >HashMap;
		typedef typename HashMap::iterator iter;
		typedef typename HashMap::const_iterator const_iter;
		HashMap ets;
	 	/**
	 	* \brief 插入数据，如果原来存在相同key值的数据>      ，原来数据将会被替换
	 	* \param key key值
	 	* \param value 要插入的数据
	 	* \return 成功返回true，否则返回false
	 	*/
	 	inline bool insert(const keyT &key,valueT &value)
		{
	 		ets[key]=value;
			return true;
		}

		/**
		* \brief 根据key值查找并得到数据
		* \param key 要寻找的key值
		* \param value 返回结果将放入此处,未找到将不会>      改变此值
		* \return 查找到返回true，未找到返回false
		*/
		inline bool find(const keyT &key,valueT &value) const
		{
			const_iter it = ets.find(key);
			if (it != ets.end())
			{
				value = it->second;
				return true;
			}
			return false;
		}
		/**
		* \brief 查找并得到一个数据
		* \param value 返回结果将放入此处,未找到将不会>      改变此值
		* \return 查找到返回true，未找到返回false
		*/
		inline bool findOne(valueT &value) const
		{
		  	if(!ets.empty())
			{
				value=ets.begin()->second;
				return true;
			}
			return false;
		}

		/**
		* \brief 构造函数
		*
		*/
		LimitHash()
		{
		}
	
		/**
		* \brief 析构函数,清除所有数据
		*/
		~LimitHash()
		{
			clear();
		}

		/**
		* \brief 移除数据
		* \param key 要移除的key值
		*/
		inline void remove(const keyT &key)
		{
			ets.erase(key);
		}
	
		/**
		* \brief 清除所有数据
		*/
		inline void clear()
		{
			ets.clear();
		}

		/**
		* \brief 统计数据个数
		*/
		inline DWORD size() const
		{
			return ets.size();
		}

		/**
		* \brief 判断容器是否为空
		*/
		inline bool empty() const
		{
			return ets.empty();
		}
};

 /**
 * \brief Entry以ID为key值的指针容器，需要继承使用
 */

class EntryID : public LimitHash<DWORD,Entry*>
{
	protected:
		/**
		* \brief 将Entry加入容器中
		* \param e 要加入的Entry
		* \return 成功返回true,否则返回false
		*/
		inline bool push(Entry * &e)
		{
			Entry *temp;
			if (!find(e->id,temp))
				return insert(e->id,e);
			else
				return false;
		}

		/**
		* \brief 移除Entry
		* \param e 要移除的Entry
		*/
		inline void remove(Entry * e)
		{
			if (e!=NULL)
			{
				LimitHash<DWORD,Entry *>::remove(e->id);
			}
		}
		/*
		* \return 返回Entry指针,未找到返回NULL
		*/
		inline Entry * getEntryByID(const DWORD id) const
		{
			Entry *ret=NULL;
			LimitHash<DWORD,Entry *>::find(id,ret);
			return ret;
		}
};

/**
* \brief Entry以名字为key值的指针容器，需要继承使用
*/
class EntryName:public LimitHash<const char*,Entry *>{
	protected:
		 /**
		 * \brief 将Entry加入容器中,如果容器中有相同key>值的添加失败
		 * \param e 要加入的Entry
		 * \return 成功返回true,否则返回false
		 */
		 inline bool push(Entry * &e)
		 {
		 	Entry *temp;
			if (!find(e->name,temp))
				return insert(e->name,e);
			else
				return false;
		}

		/**
		* \brief 移除Entry
		* \param e 要移除的Entry
		*/
		inline void remove(Entry * e)
		{
			if (e!=NULL)
			{
				LimitHash<const char*,Entry *>::remove(e->name);
			}
		}

		 /**
		 * \brief 通过名字得到Entry
		 * \param name 要得到Entry的名字
		 * \return 返回Entry指针,未找到返回NULL
		 */
		 inline Entry* getEntryByName( const std::string& name) const
		 {
		 	return getEntryByCharName( name.c_str() );
		}
		inline Entry* getEntryByCharName( const char* name ) const
		 {
		 	Entry *ret=NULL;
			LimitHash<const char*,Entry*>::find( name,ret );
			return ret;
		}

		/**
		* \brief 通过名字得到Entry
		* \param name 要得到Entry的名字
		* \return 返回Entry指针,未找到返回NULL
		*/
		inline Entry* getEntryByName(const char* name) const
		{
			return getEntryByCharName( name );
		}
};

/**
* \brief Entry以临时ID为key值的指针容器，需要继承使用*/

class EntryTempID:public LimitHash<DWORD,Entry*>
{
	protected:
		EntryTempID() {}
		virtual ~EntryTempID() {}

		/**
		* \brief 将Entry加入容器中,tempid重复添加失败	     * \param e 要加入的Entry
		* \return 成功返回true,否则返回false
		*/
		
		inline bool push(Entry * e)
		{
			if (e!=NULL && getUniqeID(e->tempid))
			{
				Entry *temp;
				if (!find(e->tempid,temp))
				{
					if (insert(e->tempid,e))
						return true;
				}
				putUniqeID(e->tempid);
			}
			return false;
		}

		/**
		* \brief 移除Entry
		* \param e 要移除的Entry
		*/
		inline void remove(Entry * e)
		{
			if (e!=NULL)
			{
				putUniqeID(e->tempid);
				LimitHash<DWORD,Entry *>::remove(e->tempid);
			}
		}

		/**
		* \brief 通过临时ID得到Entry
		* \param tempid 要得到Entry的临时ID
		* \return 返回Entry指针,未找到返回NULL
		*/

		inline Entry * getEntryByTempID(const DWORD tempid) const
		{
			Entry *ret=NULL;
			LimitHash<DWORD,Entry *>::find(tempid,ret);
			return ret;
		}

		 /**
		 * \brief 得到一个临时ID
		 * \param tempid 存放要得到的临时ID
		 * \return 得到返回true,否则返回false
		 */

		 virtual bool getUniqeID(DWORD &tempid) = 0;

		 /**
		 * \brief 放回一个临时ID
		 * \param tempid 要放回的临时ID
		 */

		 virtual void putUniqeID(const DWORD &tempid) = 0;
};

template<int i>
class EntryNone
{
	protected:
		bool push(Entry *entry) { return true; }
		void remove(Entry *entry) { }
		void clear() {}
};

template < typename e1,typename e2=EntryNone<2>,typename e3=EntryNone<3>,bool need_list=true >
class EntryManager : protected e1,protected e2,protected e3
{
	protected:
		bool addEntry(Entry *entry)
		{
			if(e1::push(entry))
			{
				if(e2::push(entry))
				{
					if(e3::push(entry))
					{
						_list.push_back(entry);
						return true;
					}
					else
					{
						e2::remove(entry);
						e1::remove(entry);
					}
				}
				else
				{
					e1::remove(entry);
				}
			}
			return false;
		}

		void removeEntry(Entry *entry)
		{
			e1::remove(entry);
			e2::remove(entry);
			e3::remove(entry);
			for(EntryManagerList_iter iter = _list.begin();iter != _list.end();)
			{
				if(*iter == entry)
				{
					_list.erase(iter);
					break;
				}
			}
		}

		~EntryManager() {}
		size_t size() const
		{
			return e1::size();
		}

		bool empty() const
		{
			return e1::empty();
		}

		void clear()
		{
			e1::clear();
			e2::clear();
			e3::clear();
			_list.clear();
		}

		template <typename YourEntry>
		bool execEveryEntry(EntryCallBack<YourEntry> &callBackInst)
		{
			EntryManagerList_iter iter_temp;
			EntryManagerList_iter list_end = _list.end();
			for(EntryManagerList_iter iter = _list.begin();iter != list_end;)
			{
				iter_temp = iter;
				++iter;
				if(!callBackInst.exec((YourEntry*)*iter_temp))
				{
					return false;
				}
			}
			return true;
		}
		template <typename YourEntry>
		bool execEveryEntryConst(EntryCallBack<const YourEntry> &callBackInst) const
		{
			EntryManagerList_iter iter_temp;
			EntryManagerList_iter list_end = _list.end();
			for(EntryManagerList_iter iter = _list.begin();iter != list_end;)
			{
				iter_temp = iter;
				++iter;
				if(!callBackInst.exec((const YourEntry*)*iter_temp))
				{
					return false;
				}
			}
			return true;
		}
		template <class YourEntry>
		bool execRandomEntry(EntryCallBack<YourEntry> &exec)
		{
			int random = Global::randBetween(0,size()-1);
			return exec.exec((YourEntry*)_list[random]);
		}
		void listAll()
		{
			struct ListAllExec : public EntryCallBack<Entry>
			{
				bool exec(Entry *entry)
				{
					Global::logger->debug("遍历容器 :%u,%u,%s",entry->id,entry->tempid,entry->name);
					return true;
				}
			};
			ListAllExec exec;
			execEveryEntry(exec);
		}
		template<class YourEntry>
		void removeEntry_if(RemoveEntry_Pred<YourEntry> &pred)
		{
			typename e1::iter it = e1::ets.begin();
			while(it != e1::ets.end())
			{
				if(pred.isIt((YourEntry*)it->second))
				{
					pred.removeVec.push_back((YourEntry*)it->second);
				}
				++it;
			}
			for(size_t index = 0;index < pred.removeVec.size();++index)
			{
				removeEntry(pred.removeVec[index]);
			}
		}
		template<class YourEntry>
		void deleteEntry_if(RemoveEntry_Pred<YourEntry> &pred)
		{
			typename e1::iter it = e1::ets.begin();
			while(it != e1::ets.end())
			{
				if(pred.isIt((YourEntry*)it->second))
				{
					pred.removeVec.push_back((YourEntry*)it->second);
				}
				++it;
			}
			for(size_t index = 0;index < pred.removeVec.size();++index)
			{
				removeEntry(pred.removeVec[index]);
				DELETE(pred.removeVec[index]);
			}
		}
		typedef bool (*SortFunc) (Entry *e1,Entry *e2);
		void sort(SortFunc sortFunc)
		{
			std::sort(_list.begin(),_list.end(),sortFunc);
		}
		void deleteAll()
		{
			for(EntryManagerList_iter it = _list.begin();it != _list.end();++it)
			{
				Entry *entry = *it;
				DELETE(entry);
			}
			clear();
		}
	private:
		typedef std::vector<Entry*> EntryManagerList;		 typedef EntryManagerList::iterator EntryManagerList_iter;
		EntryManagerList _list;
};


#endif













