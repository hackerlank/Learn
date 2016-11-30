#include "ConfigLoader.h"

ConfigLoader::ConfigLoader()
{

}

ConfigLoader::~ConfigLoader()
{

}

int ConfigLoader::load_config(int config_id, char *path)
{
	xmlDocPtr doc;           //定义解析文档指针
	xmlNodePtr rootNode;      //定义结点指针(你需要它为了在各个结点间移动)

	xmlKeepBlanksDefault(0);

	doc = xmlReadFile(path,"UTF-8",XML_PARSE_RECOVER);

	if (NULL == doc)
	{
		//文档打开错误
		return -1;
	}

	rootNode = xmlDocGetRootElement(doc); //确定文档根元素
	/*检查确认当前文档中包含内容*/
	if (NULL == rootNode)
	{
		//空得xml文件
		xmlFreeDoc(doc);
		return -1;
	}

	int nRet = deal_config(config_id, rootNode);

	xmlFreeDoc(doc);

	return nRet;
}