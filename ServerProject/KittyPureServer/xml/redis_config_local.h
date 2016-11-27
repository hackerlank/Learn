#ifndef _XML_REDIS_CONFIG_LOCAL_H_
#define _XML_REDIS_CONFIG_LOCAL_H_
#include "xmlcommon.h"

namespace config
{
 	struct redis_config_local_t
	{
		public:
			struct memdb_t
			{
				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						if (!xml.has_attribute(node, "id"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "id");
							if (sub)
							{
								_id = xml.node_value(sub);
							}
						}
						else
						{
							_id = xml.node_attribute(node, "id");
						}
						if (!xml.has_attribute(node, "ip"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "ip");
							if (sub)
							{
								_ip = xml.node_value(sub);
							}
						}
						else
						{
							_ip = xml.node_attribute(node, "ip");
						}
						if (!xml.has_attribute(node, "port"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "port");
							if (sub)
							{
								_port = xml.node_value(sub);
							}
						}
						else
						{
							_port = xml.node_attribute(node, "port");
						}
					}

					const Fir::VarType &id() const { return _id; }
					const Fir::VarType &ip() const { return _ip; }
					const Fir::VarType &port() const { return _port; }

				private:
					Fir::VarType _id;
					Fir::VarType _ip;
					Fir::VarType _port;
			};

		public:
			void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
			{
				if (!node)
				{
					return;
				}
				const Fir::XMLParser::Node *map_redismap_node = xml.child(node, "map");
				while (map_redismap_node)
				{
					if (xml.node_attribute(map_redismap_node, "var") == "redismap")
					{
						Fir::VarType keyname = xml.node_attribute(map_redismap_node, "key");
						const Fir::XMLParser::Node *sub_node = xml.child(map_redismap_node, "memdb");
						while (sub_node)
						{
							memdb_t temp_memdb;
							temp_memdb.load(xml,sub_node);
							_redismap[xml.node_attribute(sub_node, keyname)] = temp_memdb;
							sub_node = xml.next(sub_node, "memdb");
						}
						break;
					}
					map_redismap_node = xml.next(map_redismap_node, "map");
				}
			}

			const std::map< Fir::VarType, memdb_t > &redismap() const { return _redismap; }

		private:
			std::map< Fir::VarType, memdb_t > _redismap;
	};

}

#endif

