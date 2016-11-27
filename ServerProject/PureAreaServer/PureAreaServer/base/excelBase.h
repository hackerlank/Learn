#ifndef EXCEL_BASE_H
#define EXCEL_BASE_H
#include "singleton.h"
#include <unordered_map>
#include "excelManager.h"
#include "flyer.h"

namespace ExcelTbx
{
    typedef boost::function<void (const std::string &, char *&, int &)> ReadExcelFunc;

    template<typename TabelType,typename ConfType,typename TbxType>
    class ExcelTable
    {
        private:
            TabelType m_proto;
            std::unordered_map<unsigned int,const ConfType*> m_tbxMap;
        public:
            ExcelTable() {};
            virtual ~ExcelTable() {};
            void load(const std::string &fileName,const ExcelTbx::ReadExcelFunc &readFunc)
            {
                clear();
                char *buf = NULL;
                int size = 0;
                std::string path = Flyer::globalConfMap["exceltbx"] + fileName;
                readFunc(path,buf,size);
                if(buf)
                {
                    m_proto.ParseFromArray(buf,size);
                    delete [] buf;
                }
                char temp[100] = {0};
                snprintf(temp,sizeof(temp),"[加载Excel表格](%s)",fileName.c_str());
                Info(Flyer::logger,temp);
                for(int cnt = 0;cnt < m_proto.datas_size();++cnt)
                {
                    TbxType *obj = m_proto.mutable_datas(cnt);
                    ConfType *conf = new ConfType(obj);
                    if(conf->init())
                    {
                        m_tbxMap[conf->getKey()] = conf;
                    }
                    else
                    {
                        delete conf;
                        conf = NULL;
                    }
                }
            }
            void clear()
            {
                for(auto iter = m_tbxMap.begin();iter != m_tbxMap.end();++iter)
                {
                    ConfType *conf = const_cast<ConfType*>(iter->second);
                    if(conf)
                    {
                        delete conf;
                        conf = NULL;
                    }
                }
                m_tbxMap.clear();
            }
            inline const ConfType& get(const unsigned int id) const
            {
                static ConfType temp;
                auto iter = m_tbxMap.find(id);
                return iter == m_tbxMap.end() ? temp : *iter->second;
            }
            inline const ConfType* getBase(const unsigned int id) const
            {
                auto iter = m_tbxMap.find(id);
                return iter == m_tbxMap.end() ? NULL : iter->second;
            }
    };

    class ExcelManager : public Singleton<ExcelManager>
    {
        private:
            std::map<std::string,std::string> m_fileMap;
        private:
            template<typename TableType,typename ConfType,typename TbxType>
            void loadTable(const std::string &name,ExcelTbx::ExcelTable<TableType,ConfType,TbxType> &table,const ExcelTbx::ReadExcelFunc &readFun)
            {
                auto iter = m_fileMap.find(name);
                if(iter != m_fileMap.end())
                {
                    table.load(iter->second,readFun);
                }
            }
            void loadConf(const std::string &fileName)
            {
                using namespace boost::property_tree;
                ptree tree;
                read_xml(fileName,tree);
                std::string treeNode = "tbx";
                ptree child = tree.get_child(treeNode.c_str());
                for(auto iter = child.begin();iter != child.end();++iter)
                {
                    if(iter->first == "<xmlattr>" || iter->first == "<xmlcomment>")
                    {
                        continue;
                    }
                    std::string file = iter->second.get<std::string>("<xmlattr>.name");
                    std::string path = iter->second.get<std::string>("<xmlattr>.path");
                    m_fileMap.insert(std::pair<std::string,std::string>(file,path));
                }
            }
        public:
            void init(const std::string &fileName,const ExcelTbx::ReadExcelFunc &readFun);
    };
}

#endif


