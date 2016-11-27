#ifndef _XML_XMLTEST_H_
#define _XML_XMLTEST_H_
#include "xmlcommon.h"

namespace config
{
 	struct xmltest_t
	{
		public:
			struct field_t
			{
				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						if (!xml.has_attribute(node, "ID"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "ID");
							if (sub)
							{
								_ID = xml.node_value(sub);
							}
						}
						else
						{
							_ID = xml.node_attribute(node, "ID");
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
					}

					const Fir::VarType &ID() const { return _ID; }
					const Fir::VarType &name() const { return _name; }

				private:
					Fir::VarType _ID;
					Fir::VarType _name;
			};

			struct obj_t
			{
				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						if (!xml.has_attribute(node, "fff"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "fff");
							if (sub)
							{
								_fff = xml.node_value(sub);
							}
						}
						else
						{
							_fff = xml.node_attribute(node, "fff");
						}
						if (!xml.has_attribute(node, "fgd"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "fgd");
							if (sub)
							{
								_fgd = xml.node_value(sub);
							}
						}
						else
						{
							_fgd = xml.node_attribute(node, "fgd");
						}
						if (!xml.has_attribute(node, "sbb"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "sbb");
							if (sub)
							{
								_sbb = xml.node_value(sub);
							}
						}
						else
						{
							_sbb = xml.node_attribute(node, "sbb");
						}
						if (!xml.has_attribute(node, "ss"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "ss");
							if (sub)
							{
								_ss = xml.node_value(sub);
							}
						}
						else
						{
							_ss = xml.node_attribute(node, "ss");
						}
						if (!xml.has_attribute(node, "var"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "var");
							if (sub)
							{
								_var = xml.node_value(sub);
							}
						}
						else
						{
							_var = xml.node_attribute(node, "var");
						}
					}

					const Fir::VarType &fff() const { return _fff; }
					const Fir::VarType &fgd() const { return _fgd; }
					const Fir::VarType &sbb() const { return _sbb; }
					const Fir::VarType &ss() const { return _ss; }
					const Fir::VarType &var() const { return _var; }

				private:
					Fir::VarType _fff;
					Fir::VarType _fgd;
					Fir::VarType _sbb;
					Fir::VarType _ss;
					Fir::VarType _var;
			};

			struct obj1_t
			{
				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						if (!xml.has_attribute(node, "att"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "att");
							if (sub)
							{
								_att = xml.node_value(sub);
							}
						}
						else
						{
							_att = xml.node_attribute(node, "att");
						}
						if (!xml.has_attribute(node, "var"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "var");
							if (sub)
							{
								_var = xml.node_value(sub);
							}
						}
						else
						{
							_var = xml.node_attribute(node, "var");
						}
					}

					const Fir::VarType &att() const { return _att; }
					const Fir::VarType &var() const { return _var; }

				private:
					Fir::VarType _att;
					Fir::VarType _var;
			};

			struct obj2_t
			{
				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						if (!xml.has_attribute(node, "att"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "att");
							if (sub)
							{
								_att = xml.node_value(sub);
							}
						}
						else
						{
							_att = xml.node_attribute(node, "att");
						}
						if (!xml.has_attribute(node, "var"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "var");
							if (sub)
							{
								_var = xml.node_value(sub);
							}
						}
						else
						{
							_var = xml.node_attribute(node, "var");
						}
					}

					const Fir::VarType &att() const { return _att; }
					const Fir::VarType &var() const { return _var; }

				private:
					Fir::VarType _att;
					Fir::VarType _var;
			};

			struct obj3_t
			{
				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						if (!xml.has_attribute(node, "att"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "att");
							if (sub)
							{
								_att = xml.node_value(sub);
							}
						}
						else
						{
							_att = xml.node_attribute(node, "att");
						}
						if (!xml.has_attribute(node, "var"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "var");
							if (sub)
							{
								_var = xml.node_value(sub);
							}
						}
						else
						{
							_var = xml.node_attribute(node, "var");
						}
					}

					const Fir::VarType &att() const { return _att; }
					const Fir::VarType &var() const { return _var; }

				private:
					Fir::VarType _att;
					Fir::VarType _var;
			};

			struct obj4_t
			{
				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						if (!xml.has_attribute(node, "att"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "att");
							if (sub)
							{
								_att = xml.node_value(sub);
							}
						}
						else
						{
							_att = xml.node_attribute(node, "att");
						}
						if (!xml.has_attribute(node, "var"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "var");
							if (sub)
							{
								_var = xml.node_value(sub);
							}
						}
						else
						{
							_var = xml.node_attribute(node, "var");
						}
					}

					const Fir::VarType &att() const { return _att; }
					const Fir::VarType &var() const { return _var; }

				private:
					Fir::VarType _att;
					Fir::VarType _var;
			};

			struct st_obj_t
			{
				public:
					struct ttti_t
					{
						public:
							void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
							{
								if (!node)
								{
									return;
								}
								if (!xml.has_attribute(node, "bb"))
								{
									const Fir::XMLParser::Node *sub = xml.child(node, "bb");
									if (sub)
									{
										_bb = xml.node_value(sub);
									}
								}
								else
								{
									_bb = xml.node_attribute(node, "bb");
								}
								if (!xml.has_attribute(node, "var"))
								{
									const Fir::XMLParser::Node *sub = xml.child(node, "var");
									if (sub)
									{
										_var = xml.node_value(sub);
									}
								}
								else
								{
									_var = xml.node_attribute(node, "var");
								}
							}

							const Fir::VarType &bb() const { return _bb; }
							const Fir::VarType &var() const { return _var; }

						private:
							Fir::VarType _bb;
							Fir::VarType _var;
					};

				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						const Fir::XMLParser::Node *ttti_node = xml.child(node, "ttti");
						while (ttti_node)
						{
							_ttti.load(xml, ttti_node);
							ttti_node = xml.next(ttti_node, "ttti");
						}
						if (!xml.has_attribute(node, "var"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "var");
							if (sub)
							{
								_var = xml.node_value(sub);
							}
						}
						else
						{
							_var = xml.node_attribute(node, "var");
						}
					}

					const ttti_t &ttti() const { return _ttti; }
					const Fir::VarType &var() const { return _var; }

				private:
					ttti_t _ttti;
					Fir::VarType _var;
			};

			struct st_obj_123_t
			{
				public:
					struct ttti_t
					{
						public:
							void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
							{
								if (!node)
								{
									return;
								}
								if (!xml.has_attribute(node, "bb"))
								{
									const Fir::XMLParser::Node *sub = xml.child(node, "bb");
									if (sub)
									{
										_bb = xml.node_value(sub);
									}
								}
								else
								{
									_bb = xml.node_attribute(node, "bb");
								}
								if (!xml.has_attribute(node, "dd"))
								{
									const Fir::XMLParser::Node *sub = xml.child(node, "dd");
									if (sub)
									{
										_dd = xml.node_value(sub);
									}
								}
								else
								{
									_dd = xml.node_attribute(node, "dd");
								}
								if (!xml.has_attribute(node, "var"))
								{
									const Fir::XMLParser::Node *sub = xml.child(node, "var");
									if (sub)
									{
										_var = xml.node_value(sub);
									}
								}
								else
								{
									_var = xml.node_attribute(node, "var");
								}
							}

							const Fir::VarType &bb() const { return _bb; }
							const Fir::VarType &dd() const { return _dd; }
							const Fir::VarType &var() const { return _var; }

						private:
							Fir::VarType _bb;
							Fir::VarType _dd;
							Fir::VarType _var;
					};

				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						const Fir::XMLParser::Node *ttti_node = xml.child(node, "ttti");
						while (ttti_node)
						{
							_ttti.load(xml, ttti_node);
							ttti_node = xml.next(ttti_node, "ttti");
						}
					}

					const ttti_t &ttti() const { return _ttti; }

				private:
					ttti_t _ttti;
			};

			struct stvec_t
			{
				public:
					struct test_t
					{
						public:
							void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
							{
								if (!node)
								{
									return;
								}
								if (!xml.has_attribute(node, "ff"))
								{
									const Fir::XMLParser::Node *sub = xml.child(node, "ff");
									if (sub)
									{
										_ff = xml.node_value(sub);
									}
								}
								else
								{
									_ff = xml.node_attribute(node, "ff");
								}
								if (!xml.has_attribute(node, "var"))
								{
									const Fir::XMLParser::Node *sub = xml.child(node, "var");
									if (sub)
									{
										_var = xml.node_value(sub);
									}
								}
								else
								{
									_var = xml.node_attribute(node, "var");
								}
							}

							const Fir::VarType &ff() const { return _ff; }
							const Fir::VarType &var() const { return _var; }

						private:
							Fir::VarType _ff;
							Fir::VarType _var;
					};

					struct ttti_t
					{
						public:
							void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
							{
								if (!node)
								{
									return;
								}
								if (!xml.has_attribute(node, "bb"))
								{
									const Fir::XMLParser::Node *sub = xml.child(node, "bb");
									if (sub)
									{
										_bb = xml.node_value(sub);
									}
								}
								else
								{
									_bb = xml.node_attribute(node, "bb");
								}
								if (!xml.has_attribute(node, "var"))
								{
									const Fir::XMLParser::Node *sub = xml.child(node, "var");
									if (sub)
									{
										_var = xml.node_value(sub);
									}
								}
								else
								{
									_var = xml.node_attribute(node, "var");
								}
							}

							const Fir::VarType &bb() const { return _bb; }
							const Fir::VarType &var() const { return _var; }

						private:
							Fir::VarType _bb;
							Fir::VarType _var;
					};

				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						const Fir::XMLParser::Node *test_node = xml.child(node, "test");
						while (test_node)
						{
							_test.load(xml, test_node);
							test_node = xml.next(test_node, "test");
						}
						load_vector< ttti_t >("test_vec", "ttti", _test_vec, xml, node);
					}

					const test_t &test() const { return _test; }
					const std::vector< ttti_t > &test_vec() const { return _test_vec; }

				private:
					test_t _test;
					std::vector< ttti_t > _test_vec;
			};

			struct table_t
			{
				public:
					struct field_t
					{
						public:
							struct field2_t
							{
								public:
									void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
									{
										if (!node)
										{
											return;
										}
										if (!xml.has_attribute(node, "var"))
										{
											const Fir::XMLParser::Node *sub = xml.child(node, "var");
											if (sub)
											{
												_var = xml.node_value(sub);
											}
										}
										else
										{
											_var = xml.node_attribute(node, "var");
										}
									}

									const Fir::VarType &var() const { return _var; }

								private:
									Fir::VarType _var;
							};

							struct obj_pk_t
							{
								public:
									void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
									{
										if (!node)
										{
											return;
										}
										if (!xml.has_attribute(node, "att"))
										{
											const Fir::XMLParser::Node *sub = xml.child(node, "att");
											if (sub)
											{
												_att = xml.node_value(sub);
											}
										}
										else
										{
											_att = xml.node_attribute(node, "att");
										}
										if (!xml.has_attribute(node, "var"))
										{
											const Fir::XMLParser::Node *sub = xml.child(node, "var");
											if (sub)
											{
												_var = xml.node_value(sub);
											}
										}
										else
										{
											_var = xml.node_attribute(node, "var");
										}
									}

									const Fir::VarType &att() const { return _att; }
									const Fir::VarType &var() const { return _var; }

								private:
									Fir::VarType _att;
									Fir::VarType _var;
							};

						public:
							void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
							{
								if (!node)
								{
									return;
								}
								if (!xml.has_attribute(node, "ID"))
								{
									const Fir::XMLParser::Node *sub = xml.child(node, "ID");
									if (sub)
									{
										_ID = xml.node_value(sub);
									}
								}
								else
								{
									_ID = xml.node_attribute(node, "ID");
								}
								const Fir::XMLParser::Node *obj_pk_node = xml.child(node, "obj_pk");
								while (obj_pk_node)
								{
									_obj_pk.load(xml, obj_pk_node);
									obj_pk_node = xml.next(obj_pk_node, "obj_pk");
								}
								if (!xml.has_attribute(node, "sss0"))
								{
									const Fir::XMLParser::Node *sub = xml.child(node, "sss0");
									if (sub)
									{
										_sss0 = xml.node_value(sub);
									}
								}
								else
								{
									_sss0 = xml.node_attribute(node, "sss0");
								}
								if (!xml.has_attribute(node, "sss1"))
								{
									const Fir::XMLParser::Node *sub = xml.child(node, "sss1");
									if (sub)
									{
										_sss1 = xml.node_value(sub);
									}
								}
								else
								{
									_sss1 = xml.node_attribute(node, "sss1");
								}
								if (!xml.has_attribute(node, "sss2"))
								{
									const Fir::XMLParser::Node *sub = xml.child(node, "sss2");
									if (sub)
									{
										_sss2 = xml.node_value(sub);
									}
								}
								else
								{
									_sss2 = xml.node_attribute(node, "sss2");
								}
								if (!xml.has_attribute(node, "sss3"))
								{
									const Fir::XMLParser::Node *sub = xml.child(node, "sss3");
									if (sub)
									{
										_sss3 = xml.node_value(sub);
									}
								}
								else
								{
									_sss3 = xml.node_attribute(node, "sss3");
								}
								if (!xml.has_attribute(node, "var"))
								{
									const Fir::XMLParser::Node *sub = xml.child(node, "var");
									if (sub)
									{
										_var = xml.node_value(sub);
									}
								}
								else
								{
									_var = xml.node_attribute(node, "var");
								}
								load_vector< field2_t >("vecbase", "field2", _vecbase, xml, node);
							}

							const Fir::VarType &ID() const { return _ID; }
							const obj_pk_t &obj_pk() const { return _obj_pk; }
							const Fir::VarType &sss0() const { return _sss0; }
							const Fir::VarType &sss1() const { return _sss1; }
							const Fir::VarType &sss2() const { return _sss2; }
							const Fir::VarType &sss3() const { return _sss3; }
							const Fir::VarType &var() const { return _var; }
							const std::vector< field2_t > &vecbase() const { return _vecbase; }

						private:
							Fir::VarType _ID;
							obj_pk_t _obj_pk;
							Fir::VarType _sss0;
							Fir::VarType _sss1;
							Fir::VarType _sss2;
							Fir::VarType _sss3;
							Fir::VarType _var;
							std::vector< field2_t > _vecbase;
					};

				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						const Fir::XMLParser::Node *map_fields_node = xml.child(node, "map");
						while (map_fields_node)
						{
							if (xml.node_attribute(map_fields_node, "var") == "fields")
							{
								Fir::VarType keyname = xml.node_attribute(map_fields_node, "key");
								const Fir::XMLParser::Node *sub_node = xml.child(map_fields_node, "field");
								while (sub_node)
								{
									field_t temp_field;
									temp_field.load(xml,sub_node);
									_fields[xml.node_attribute(sub_node, keyname)] = temp_field;
									sub_node = xml.next(sub_node, "field");
								}
								break;
							}
							map_fields_node = xml.next(map_fields_node, "map");
						}
						if (!xml.has_attribute(node, "giftid"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "giftid");
							if (sub)
							{
								_giftid = xml.node_value(sub);
							}
						}
						else
						{
							_giftid = xml.node_attribute(node, "giftid");
						}
						if (!xml.has_attribute(node, "pro"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "pro");
							if (sub)
							{
								_pro = xml.node_value(sub);
							}
						}
						else
						{
							_pro = xml.node_attribute(node, "pro");
						}
						if (!xml.has_attribute(node, "var"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "var");
							if (sub)
							{
								_var = xml.node_value(sub);
							}
						}
						else
						{
							_var = xml.node_attribute(node, "var");
						}
						load_vector< field_t >("vecbase", "field", _vecbase, xml, node);
					}

					const std::map< Fir::VarType, field_t > &fields() const { return _fields; }
					const Fir::VarType &giftid() const { return _giftid; }
					const Fir::VarType &pro() const { return _pro; }
					const Fir::VarType &var() const { return _var; }
					const std::vector< field_t > &vecbase() const { return _vecbase; }

				private:
					std::map< Fir::VarType, field_t > _fields;
					Fir::VarType _giftid;
					Fir::VarType _pro;
					Fir::VarType _var;
					std::vector< field_t > _vecbase;
			};

			struct teee1_t
			{
				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						if (!xml.has_attribute(node, "var"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "var");
							if (sub)
							{
								_var = xml.node_value(sub);
							}
						}
						else
						{
							_var = xml.node_attribute(node, "var");
						}
					}

					const Fir::VarType &var() const { return _var; }

				private:
					Fir::VarType _var;
			};

			struct teee2_t
			{
				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						if (!xml.has_attribute(node, "var"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "var");
							if (sub)
							{
								_var = xml.node_value(sub);
							}
						}
						else
						{
							_var = xml.node_attribute(node, "var");
						}
					}

					const Fir::VarType &var() const { return _var; }

				private:
					Fir::VarType _var;
			};

			struct teee3_t
			{
				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						if (!xml.has_attribute(node, "var"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "var");
							if (sub)
							{
								_var = xml.node_value(sub);
							}
						}
						else
						{
							_var = xml.node_attribute(node, "var");
						}
					}

					const Fir::VarType &var() const { return _var; }

				private:
					Fir::VarType _var;
			};

		public:
			void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
			{
				if (!node)
				{
					return;
				}
				const Fir::XMLParser::Node *map_fields_node = xml.child(node, "map");
				while (map_fields_node)
				{
					if (xml.node_attribute(map_fields_node, "var") == "fields")
					{
						Fir::VarType keyname = xml.node_attribute(map_fields_node, "key");
						const Fir::XMLParser::Node *sub_node = xml.child(map_fields_node, "field");
						while (sub_node)
						{
							field_t temp_field;
							temp_field.load(xml,sub_node);
							_fields[xml.node_attribute(sub_node, keyname)] = temp_field;
							sub_node = xml.next(sub_node, "field");
						}
						break;
					}
					map_fields_node = xml.next(map_fields_node, "map");
				}
				const Fir::XMLParser::Node *obj_node = xml.child(node, "obj");
				while (obj_node)
				{
					_obj.load(xml, obj_node);
					obj_node = xml.next(obj_node, "obj");
				}
				const Fir::XMLParser::Node *obj1_node = xml.child(node, "obj1");
				while (obj1_node)
				{
					_obj1.load(xml, obj1_node);
					obj1_node = xml.next(obj1_node, "obj1");
				}
				const Fir::XMLParser::Node *obj2_node = xml.child(node, "obj2");
				while (obj2_node)
				{
					_obj2.load(xml, obj2_node);
					obj2_node = xml.next(obj2_node, "obj2");
				}
				const Fir::XMLParser::Node *obj3_node = xml.child(node, "obj3");
				while (obj3_node)
				{
					_obj3.load(xml, obj3_node);
					obj3_node = xml.next(obj3_node, "obj3");
				}
				const Fir::XMLParser::Node *obj4_node = xml.child(node, "obj4");
				while (obj4_node)
				{
					_obj4.load(xml, obj4_node);
					obj4_node = xml.next(obj4_node, "obj4");
				}
				const Fir::XMLParser::Node *st_obj_node = xml.child(node, "st_obj");
				while (st_obj_node)
				{
					_st_obj.load(xml, st_obj_node);
					st_obj_node = xml.next(st_obj_node, "st_obj");
				}
				const Fir::XMLParser::Node *st_obj_123_node = xml.child(node, "st_obj_123");
				while (st_obj_123_node)
				{
					_st_obj_123.load(xml, st_obj_123_node);
					st_obj_123_node = xml.next(st_obj_123_node, "st_obj_123");
				}
				const Fir::XMLParser::Node *table_node = xml.child(node, "table");
				while (table_node)
				{
					_table.load(xml, table_node);
					table_node = xml.next(table_node, "table");
				}
				const Fir::XMLParser::Node *teee1_node = xml.child(node, "teee1");
				while (teee1_node)
				{
					_teee1.load(xml, teee1_node);
					teee1_node = xml.next(teee1_node, "teee1");
				}
				const Fir::XMLParser::Node *teee2_node = xml.child(node, "teee2");
				while (teee2_node)
				{
					_teee2.load(xml, teee2_node);
					teee2_node = xml.next(teee2_node, "teee2");
				}
				const Fir::XMLParser::Node *teee3_node = xml.child(node, "teee3");
				while (teee3_node)
				{
					_teee3.load(xml, teee3_node);
					teee3_node = xml.next(teee3_node, "teee3");
				}
				load_vector< stvec_t >("test_stvec", "stvec", _test_stvec, xml, node);
				load_vartype_vector("vecbase", _vecbase, xml, node);
			}

			const std::map< Fir::VarType, field_t > &fields() const { return _fields; }
			const obj_t &obj() const { return _obj; }
			const obj1_t &obj1() const { return _obj1; }
			const obj2_t &obj2() const { return _obj2; }
			const obj3_t &obj3() const { return _obj3; }
			const obj4_t &obj4() const { return _obj4; }
			const st_obj_t &st_obj() const { return _st_obj; }
			const st_obj_123_t &st_obj_123() const { return _st_obj_123; }
			const table_t &table() const { return _table; }
			const teee1_t &teee1() const { return _teee1; }
			const teee2_t &teee2() const { return _teee2; }
			const teee3_t &teee3() const { return _teee3; }
			const std::vector< stvec_t > &test_stvec() const { return _test_stvec; }
			const std::vector< Fir::VarType > &vecbase() const { return _vecbase; }

		private:
			std::map< Fir::VarType, field_t > _fields;
			obj_t _obj;
			obj1_t _obj1;
			obj2_t _obj2;
			obj3_t _obj3;
			obj4_t _obj4;
			st_obj_t _st_obj;
			st_obj_123_t _st_obj_123;
			table_t _table;
			teee1_t _teee1;
			teee2_t _teee2;
			teee3_t _teee3;
			std::vector< stvec_t > _test_stvec;
			std::vector< Fir::VarType > _vecbase;
	};

}

#endif

