#ifndef _XML_NEW_USER_INIT_H_
#define _XML_NEW_USER_INIT_H_
#include "xmlcommon.h"

namespace config
{
 	struct new_user_init_t
	{
		public:
			struct friendship_t
			{
				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						if (!xml.has_attribute(node, "num"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "num");
							if (sub)
							{
								_num = xml.node_value(sub);
							}
						}
						else
						{
							_num = xml.node_attribute(node, "num");
						}
					}

					const Fir::VarType &num() const { return _num; }

				private:
					Fir::VarType _num;
			};

			struct gold_t
			{
				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						if (!xml.has_attribute(node, "money"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "money");
							if (sub)
							{
								_money = xml.node_value(sub);
							}
						}
						else
						{
							_money = xml.node_attribute(node, "money");
						}
					}

					const Fir::VarType &money() const { return _money; }

				private:
					Fir::VarType _money;
			};

			struct hero_t
			{
				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						if (!xml.has_attribute(node, "itemid"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "itemid");
							if (sub)
							{
								_itemid = xml.node_value(sub);
							}
						}
						else
						{
							_itemid = xml.node_attribute(node, "itemid");
						}
						if (!xml.has_attribute(node, "leader"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "leader");
							if (sub)
							{
								_leader = xml.node_value(sub);
							}
						}
						else
						{
							_leader = xml.node_attribute(node, "leader");
						}
						if (!xml.has_attribute(node, "level"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "level");
							if (sub)
							{
								_level = xml.node_value(sub);
							}
						}
						else
						{
							_level = xml.node_attribute(node, "level");
						}
						if (!xml.has_attribute(node, "pos"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "pos");
							if (sub)
							{
								_pos = xml.node_value(sub);
							}
						}
						else
						{
							_pos = xml.node_attribute(node, "pos");
						}
						if (!xml.has_attribute(node, "star"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "star");
							if (sub)
							{
								_star = xml.node_value(sub);
							}
						}
						else
						{
							_star = xml.node_attribute(node, "star");
						}
					}

					const Fir::VarType &itemid() const { return _itemid; }
					const Fir::VarType &leader() const { return _leader; }
					const Fir::VarType &level() const { return _level; }
					const Fir::VarType &pos() const { return _pos; }
					const Fir::VarType &star() const { return _star; }

				private:
					Fir::VarType _itemid;
					Fir::VarType _leader;
					Fir::VarType _level;
					Fir::VarType _pos;
					Fir::VarType _star;
			};

			struct lingqi_t
			{
				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						if (!xml.has_attribute(node, "num"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "num");
							if (sub)
							{
								_num = xml.node_value(sub);
							}
						}
						else
						{
							_num = xml.node_attribute(node, "num");
						}
					}

					const Fir::VarType &num() const { return _num; }

				private:
					Fir::VarType _num;
			};

			struct power_t
			{
				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						if (!xml.has_attribute(node, "num"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "num");
							if (sub)
							{
								_num = xml.node_value(sub);
							}
						}
						else
						{
							_num = xml.node_attribute(node, "num");
						}
					}

					const Fir::VarType &num() const { return _num; }

				private:
					Fir::VarType _num;
			};

			struct renminbi_t
			{
				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						if (!xml.has_attribute(node, "num"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "num");
							if (sub)
							{
								_num = xml.node_value(sub);
							}
						}
						else
						{
							_num = xml.node_attribute(node, "num");
						}
					}

					const Fir::VarType &num() const { return _num; }

				private:
					Fir::VarType _num;
			};

		public:
			void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
			{
				if (!node)
				{
					return;
				}
				const Fir::XMLParser::Node *friendship_node = xml.child(node, "friendship");
				while (friendship_node)
				{
					_friendship.load(xml, friendship_node);
					friendship_node = xml.next(friendship_node, "friendship");
				}
				const Fir::XMLParser::Node *gold_node = xml.child(node, "gold");
				while (gold_node)
				{
					_gold.load(xml, gold_node);
					gold_node = xml.next(gold_node, "gold");
				}
				const Fir::XMLParser::Node *map_inithero_node = xml.child(node, "map");
				while (map_inithero_node)
				{
					if (xml.node_attribute(map_inithero_node, "var") == "inithero")
					{
						Fir::VarType keyname = xml.node_attribute(map_inithero_node, "key");
						const Fir::XMLParser::Node *sub_node = xml.child(map_inithero_node, "hero");
						while (sub_node)
						{
							hero_t temp_hero;
							temp_hero.load(xml,sub_node);
							_inithero[xml.node_attribute(sub_node, keyname)] = temp_hero;
							sub_node = xml.next(sub_node, "hero");
						}
						break;
					}
					map_inithero_node = xml.next(map_inithero_node, "map");
				}
				const Fir::XMLParser::Node *lingqi_node = xml.child(node, "lingqi");
				while (lingqi_node)
				{
					_lingqi.load(xml, lingqi_node);
					lingqi_node = xml.next(lingqi_node, "lingqi");
				}
				const Fir::XMLParser::Node *power_node = xml.child(node, "power");
				while (power_node)
				{
					_power.load(xml, power_node);
					power_node = xml.next(power_node, "power");
				}
				const Fir::XMLParser::Node *renminbi_node = xml.child(node, "renminbi");
				while (renminbi_node)
				{
					_renminbi.load(xml, renminbi_node);
					renminbi_node = xml.next(renminbi_node, "renminbi");
				}
			}

			const friendship_t &friendship() const { return _friendship; }
			const gold_t &gold() const { return _gold; }
			const std::map< Fir::VarType, hero_t > &inithero() const { return _inithero; }
			const lingqi_t &lingqi() const { return _lingqi; }
			const power_t &power() const { return _power; }
			const renminbi_t &renminbi() const { return _renminbi; }

		private:
			friendship_t _friendship;
			gold_t _gold;
			std::map< Fir::VarType, hero_t > _inithero;
			lingqi_t _lingqi;
			power_t _power;
			renminbi_t _renminbi;
	};

}

#endif

