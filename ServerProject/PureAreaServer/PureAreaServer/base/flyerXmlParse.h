#ifndef FLYER_XML_PARSE_H
#define FLYER_XML_PARSE_H
#include "flyerValue.h"
#include <libxml/parser.h>

namespace Flyer
{
    class FlyerXmlParse
    {
        private:
            //xmlDoc *m_doc;
            xmlDocPtr m_doc;
        public:
            FlyerXmlParse();
            ~FlyerXmlParse();
            void final();
            bool loadFile(const char *fileName);
            const xmlNode* getRoot();
            const xmlNode* getChild(const xmlNode *parent, const char *name = NULL) const;
            const xmlNode* getNext(const xmlNode *node, const char *name = NULL) const;
            unsigned int childCnt(const xmlNode *parent, const char *name) const;
            bool hasAttribute(const xmlNode *node, const char *name) const;
            Flyer::FlyerValue nodeAttributeVal(const xmlNode *node, const char *name) const;
            Flyer::FlyerValue nodeTextValue(const xmlNode *node) const;
    };
    //加载配置文件的节点
    bool loadXmlConf(const char *fileName,const char *nodeName = "global");
}

#endif

