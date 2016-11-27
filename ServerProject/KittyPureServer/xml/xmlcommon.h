#ifndef __XML_COMMON_H__
#define __XML_COMMON_H__
#include <map>
#include <vector>
#include "vartype.h"
#include "xmlparser.h"

namespace config
	{
	template <typename T>
	void load_vector(std::string vec_name, std::string sub_nodename, std::vector<T> &var, const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
	{
		const Fir::XMLParser::Node *vec_node = xml.child(node, "vector");
		while (vec_node)
		{
			if (xml.node_attribute(vec_node, "var") == vec_name)
			{
				var.resize(xml.child_count(vec_node, sub_nodename.c_str()));
				const Fir::XMLParser::Node *sub_node = xml.child(vec_node, sub_nodename.c_str());
				size_t i = 0;
				while (sub_node && i < var.size())
				{
					var[i].load(xml, sub_node);
					++i;
					sub_node = xml.next(sub_node, sub_nodename.c_str());
				}
				break;
			}
			vec_node = xml.next(vec_node, "vector");
		}
	}

	static void load_vartype_vector(std::string vec_name, std::vector<Fir::VarType> &var, const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
	{
		const Fir::XMLParser::Node *vec_node = xml.child(node, "vector");
		while (vec_node)
		{
			if (xml.node_attribute(vec_node, "var") == vec_name)
			{
				const Fir::XMLParser::Node *sub_node = xml.child(vec_node, NULL);
				while (sub_node)
				{
					var.push_back(xml.node_value(sub_node));
					sub_node = xml.next(sub_node, NULL);
				}
				break;
			}
			vec_node = xml.next(vec_node, "vector");
		}
	}

}

#endif

