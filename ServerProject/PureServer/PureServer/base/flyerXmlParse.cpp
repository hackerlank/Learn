#include "flyerXmlParse.h"
#include "flyer.h"
#include "head.h"

namespace Flyer
{
    FlyerXmlParse::FlyerXmlParse() : m_doc(NULL)
    {
    }

    FlyerXmlParse::~FlyerXmlParse()
    {
        final();
    }

    void FlyerXmlParse::final()
    {
        if(m_doc)
        {
            xmlFreeDoc(m_doc);
            m_doc = NULL;
        }
    }

    bool FlyerXmlParse::loadFile(const char *fileName)
    {
        if(fileName)
        {
            final();
            //m_doc = xmlReadFile(fileName,"UTF-8",XML_PARSE_RECOVER);
            m_doc = xmlParseFile(fileName);
        }
        return m_doc != NULL;
    }

    const xmlNode* FlyerXmlParse::getRoot()
    {
        return m_doc ? xmlDocGetRootElement(m_doc) : NULL;
    }

    const xmlNode* FlyerXmlParse::getChild(const xmlNode *parent, const char *name) const
    {
        if(!parent)
        {
            return NULL;
        }
        for(xmlNode *child = parent->children;child;child = child->next)
        {
            if(name ? !xmlStrcmp(child->name, (const xmlChar *)name) : !xmlNodeIsText(child))
            {
                return child;
            }
        }
        return NULL;
    }

    const xmlNode* FlyerXmlParse::getNext(const xmlNode *node, const char *name) const
    {
        if(!node)
        {
            return NULL;
        }
        for(xmlNode *next = node->next;next;next = next->next)
        {
            if(name ? !xmlStrcmp(next->name, (const xmlChar *)name) : !xmlNodeIsText(next))
            {
                return next;
            }
        }
        return NULL;
    }

    unsigned int FlyerXmlParse::childCnt(const xmlNode *parent, const char *name) const
    {
        unsigned int cnt = 0;
        if(parent)
        {
            const xmlNode *node = getChild(parent, name);
            while(node)
            {
                ++cnt;
                node = getNext(node, name);
            }
        }
        return cnt;
    }

    bool FlyerXmlParse::hasAttribute(const xmlNode *node, const char *name) const
    {
        bool ret = false;
        char *temp = (char *)xmlGetProp((xmlNodePtr)node, (const xmlChar *)name);
        if(temp)
        {
             xmlFree(temp);
             ret = true;
        }
        return ret;
    }

    Flyer::FlyerValue FlyerXmlParse::nodeAttributeVal(const xmlNode *node, const char *name) const
    {
        Flyer::FlyerValue ret;
        if(node && name)
        {
            char *temp = (char *)xmlGetProp((xmlNodePtr)node, (const xmlChar *)name);
            if(temp)
            {
                ret = temp;
                xmlFree(temp);
            }
        }
        return ret;
    }

    Flyer::FlyerValue FlyerXmlParse::nodeTextValue(const xmlNode *node) const
    {
        Flyer::FlyerValue ret;
        if(node)
        {
            for (xmlNode *text = node->children; text; text = text->next) 
            {
                if(xmlNodeIsText(text))
                {
                    ret = (const char *)text->content;
                    break;
                }
            }
        }
        return ret;
    }

    bool loadXmlConf(const char *fileName,const char *nodeName)
    {
        bool ret = false;
        do
        {
            if(!fileName)
            {
                break;
            }
            using namespace boost::property_tree;
            ptree tree;
            read_xml(fileName,tree);
            std::string treeNode = "Flyer.";
            treeNode += nodeName;
            ptree child = tree.get_child(treeNode.c_str());
            for(auto iter = child.begin();iter != child.end();++iter)
            {
                //去掉注释
                if(iter->first != "<xmlcomment>")
                {
                    Flyer::globalConfMap[iter->first] = iter->second.data();
                }
            }
            ret = true;
        }while(false);

        char temp[100] = {0};
        snprintf(temp,sizeof(temp),"[加载配置]%s(%s,%s)",ret ? "成功" : "失败",fileName,nodeName);
        Info(Flyer::logger,temp);
        return ret;
    }

}

