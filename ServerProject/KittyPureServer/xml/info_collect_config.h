#ifndef _XML_INFO_COLLECT_CONFIG_H_
#define _XML_INFO_COLLECT_CONFIG_H_
#include "xmlcommon.h"

namespace config
{
 	struct info_collect_config_t
	{
		public:
			struct Modules_t
			{
				public:
					struct module_t
					{
						public:
							void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
							{
								if (!node)
								{
									return;
								}
								if (!xml.has_attribute(node, "interval"))
								{
									const Fir::XMLParser::Node *sub = xml.child(node, "interval");
									if (sub)
									{
										_interval = xml.node_value(sub);
									}
								}
								else
								{
									_interval = xml.node_attribute(node, "interval");
								}
								if (!xml.has_attribute(node, "name"))
								{
									const Fir::XMLParser::Node *sub = xml.child(node, "name");
									if (sub)
									{
										_name = xml.node_value(sub);
									}
								}
								else
								{
									_name = xml.node_attribute(node, "name");
								}
								if (!xml.has_attribute(node, "times"))
								{
									const Fir::XMLParser::Node *sub = xml.child(node, "times");
									if (sub)
									{
										_times = xml.node_value(sub);
									}
								}
								else
								{
									_times = xml.node_attribute(node, "times");
								}
								if (!xml.has_attribute(node, "type"))
								{
									const Fir::XMLParser::Node *sub = xml.child(node, "type");
									if (sub)
									{
										_type = xml.node_value(sub);
									}
								}
								else
								{
									_type = xml.node_attribute(node, "type");
								}
							}

							const Fir::VarType &interval() const { return _interval; }
							const Fir::VarType &name() const { return _name; }
							const Fir::VarType &times() const { return _times; }
							const Fir::VarType &type() const { return _type; }

						private:
							Fir::VarType _interval;
							Fir::VarType _name;
							Fir::VarType _times;
							Fir::VarType _type;
					};

				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						const Fir::XMLParser::Node *module_node = xml.child(node, "module");
						while (module_node)
						{
							_module.load(xml, module_node);
							module_node = xml.next(module_node, "module");
						}
					}

					const module_t &module() const { return _module; }

				private:
					module_t _module;
			};

			struct collectitem_t
			{
				public:
					struct baoxian_t
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
							}

							const Fir::VarType &id() const { return _id; }

						private:
							Fir::VarType _id;
					};

					struct item_t
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
							}

							const Fir::VarType &id() const { return _id; }

						private:
							Fir::VarType _id;
					};

				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						const Fir::XMLParser::Node *baoxian_node = xml.child(node, "baoxian");
						while (baoxian_node)
						{
							_baoxian.load(xml, baoxian_node);
							baoxian_node = xml.next(baoxian_node, "baoxian");
						}
						const Fir::XMLParser::Node *item_node = xml.child(node, "item");
						while (item_node)
						{
							_item.load(xml, item_node);
							item_node = xml.next(item_node, "item");
						}
						if (!xml.has_attribute(node, "maxsize"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "maxsize");
							if (sub)
							{
								_maxsize = xml.node_value(sub);
							}
						}
						else
						{
							_maxsize = xml.node_attribute(node, "maxsize");
						}
					}

					const baoxian_t &baoxian() const { return _baoxian; }
					const item_t &item() const { return _item; }
					const Fir::VarType &maxsize() const { return _maxsize; }

				private:
					baoxian_t _baoxian;
					item_t _item;
					Fir::VarType _maxsize;
			};

			struct timer_t
			{
				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						if (!xml.has_attribute(node, "interval"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "interval");
							if (sub)
							{
								_interval = xml.node_value(sub);
							}
						}
						else
						{
							_interval = xml.node_attribute(node, "interval");
						}
						if (!xml.has_attribute(node, "last"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "last");
							if (sub)
							{
								_last = xml.node_value(sub);
							}
						}
						else
						{
							_last = xml.node_attribute(node, "last");
						}
						if (!xml.has_attribute(node, "startTime"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "startTime");
							if (sub)
							{
								_startTime = xml.node_value(sub);
							}
						}
						else
						{
							_startTime = xml.node_attribute(node, "startTime");
						}
						if (!xml.has_attribute(node, "time"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "time");
							if (sub)
							{
								_time = xml.node_value(sub);
							}
						}
						else
						{
							_time = xml.node_attribute(node, "time");
						}
					}

					const Fir::VarType &interval() const { return _interval; }
					const Fir::VarType &last() const { return _last; }
					const Fir::VarType &startTime() const { return _startTime; }
					const Fir::VarType &time() const { return _time; }

				private:
					Fir::VarType _interval;
					Fir::VarType _last;
					Fir::VarType _startTime;
					Fir::VarType _time;
			};

		public:
			void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
			{
				if (!node)
				{
					return;
				}
				const Fir::XMLParser::Node *Modules_node = xml.child(node, "Modules");
				while (Modules_node)
				{
					_Modules.load(xml, Modules_node);
					Modules_node = xml.next(Modules_node, "Modules");
				}
				const Fir::XMLParser::Node *collectitem_node = xml.child(node, "collectitem");
				while (collectitem_node)
				{
					_collectitem.load(xml, collectitem_node);
					collectitem_node = xml.next(collectitem_node, "collectitem");
				}
				const Fir::XMLParser::Node *timer_node = xml.child(node, "timer");
				while (timer_node)
				{
					_timer.load(xml, timer_node);
					timer_node = xml.next(timer_node, "timer");
				}
			}

			const Modules_t &Modules() const { return _Modules; }
			const collectitem_t &collectitem() const { return _collectitem; }
			const timer_t &timer() const { return _timer; }

		private:
			Modules_t _Modules;
			collectitem_t _collectitem;
			timer_t _timer;
	};

}

#endif

