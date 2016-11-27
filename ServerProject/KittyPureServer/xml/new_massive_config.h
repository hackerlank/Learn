#ifndef _XML_NEW_MASSIVE_CONFIG_H_
#define _XML_NEW_MASSIVE_CONFIG_H_
#include "xmlcommon.h"

namespace config
{
 	struct new_massive_config_t
	{
		public:
			struct septConfig_t
			{
				public:
					struct addLimitSeptNum_t
					{
						public:
							void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
							{
								if (!node)
								{
									return;
								}
								if (!xml.has_attribute(node, "cost"))
								{
									const Fir::XMLParser::Node *sub = xml.child(node, "cost");
									if (sub)
									{
										_cost = xml.node_value(sub);
									}
								}
								else
								{
									_cost = xml.node_attribute(node, "cost");
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
							}

							const Fir::VarType &cost() const { return _cost; }
							const Fir::VarType &times() const { return _times; }

						private:
							Fir::VarType _cost;
							Fir::VarType _times;
					};

				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						const Fir::XMLParser::Node *addLimitSeptNum_node = xml.child(node, "addLimitSeptNum");
						while (addLimitSeptNum_node)
						{
							_addLimitSeptNum.load(xml, addLimitSeptNum_node);
							addLimitSeptNum_node = xml.next(addLimitSeptNum_node, "addLimitSeptNum");
						}
						if (!xml.has_attribute(node, "addNums"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "addNums");
							if (sub)
							{
								_addNums = xml.node_value(sub);
							}
						}
						else
						{
							_addNums = xml.node_attribute(node, "addNums");
						}
						if (!xml.has_attribute(node, "createSeptNeedLevel"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "createSeptNeedLevel");
							if (sub)
							{
								_createSeptNeedLevel = xml.node_value(sub);
							}
						}
						else
						{
							_createSeptNeedLevel = xml.node_attribute(node, "createSeptNeedLevel");
						}
						if (!xml.has_attribute(node, "createSeptNeedMoney"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "createSeptNeedMoney");
							if (sub)
							{
								_createSeptNeedMoney = xml.node_value(sub);
							}
						}
						else
						{
							_createSeptNeedMoney = xml.node_attribute(node, "createSeptNeedMoney");
						}
						if (!xml.has_attribute(node, "iniMemberLimit"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "iniMemberLimit");
							if (sub)
							{
								_iniMemberLimit = xml.node_value(sub);
							}
						}
						else
						{
							_iniMemberLimit = xml.node_attribute(node, "iniMemberLimit");
						}
						if (!xml.has_attribute(node, "joinSeptLevel"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "joinSeptLevel");
							if (sub)
							{
								_joinSeptLevel = xml.node_value(sub);
							}
						}
						else
						{
							_joinSeptLevel = xml.node_attribute(node, "joinSeptLevel");
						}
						if (!xml.has_attribute(node, "secondSeptMasterNum"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "secondSeptMasterNum");
							if (sub)
							{
								_secondSeptMasterNum = xml.node_value(sub);
							}
						}
						else
						{
							_secondSeptMasterNum = xml.node_attribute(node, "secondSeptMasterNum");
						}
					}

					const addLimitSeptNum_t &addLimitSeptNum() const { return _addLimitSeptNum; }
					const Fir::VarType &addNums() const { return _addNums; }
					const Fir::VarType &createSeptNeedLevel() const { return _createSeptNeedLevel; }
					const Fir::VarType &createSeptNeedMoney() const { return _createSeptNeedMoney; }
					const Fir::VarType &iniMemberLimit() const { return _iniMemberLimit; }
					const Fir::VarType &joinSeptLevel() const { return _joinSeptLevel; }
					const Fir::VarType &secondSeptMasterNum() const { return _secondSeptMasterNum; }

				private:
					addLimitSeptNum_t _addLimitSeptNum;
					Fir::VarType _addNums;
					Fir::VarType _createSeptNeedLevel;
					Fir::VarType _createSeptNeedMoney;
					Fir::VarType _iniMemberLimit;
					Fir::VarType _joinSeptLevel;
					Fir::VarType _secondSeptMasterNum;
			};

			struct stFriendConfig_t
			{
				public:
					struct mapGivePower_t
					{
						public:
							struct stPower_t
							{
								public:
									void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
									{
										if (!node)
										{
											return;
										}
										if (!xml.has_attribute(node, "dwID"))
										{
											const Fir::XMLParser::Node *sub = xml.child(node, "dwID");
											if (sub)
											{
												_dwID = xml.node_value(sub);
											}
										}
										else
										{
											_dwID = xml.node_attribute(node, "dwID");
										}
										if (!xml.has_attribute(node, "dwMaxLevel"))
										{
											const Fir::XMLParser::Node *sub = xml.child(node, "dwMaxLevel");
											if (sub)
											{
												_dwMaxLevel = xml.node_value(sub);
											}
										}
										else
										{
											_dwMaxLevel = xml.node_attribute(node, "dwMaxLevel");
										}
										if (!xml.has_attribute(node, "dwNumber"))
										{
											const Fir::XMLParser::Node *sub = xml.child(node, "dwNumber");
											if (sub)
											{
												_dwNumber = xml.node_value(sub);
											}
										}
										else
										{
											_dwNumber = xml.node_attribute(node, "dwNumber");
										}
										if (!xml.has_attribute(node, "dwStrenthNum"))
										{
											const Fir::XMLParser::Node *sub = xml.child(node, "dwStrenthNum");
											if (sub)
											{
												_dwStrenthNum = xml.node_value(sub);
											}
										}
										else
										{
											_dwStrenthNum = xml.node_attribute(node, "dwStrenthNum");
										}
									}

									const Fir::VarType &dwID() const { return _dwID; }
									const Fir::VarType &dwMaxLevel() const { return _dwMaxLevel; }
									const Fir::VarType &dwNumber() const { return _dwNumber; }
									const Fir::VarType &dwStrenthNum() const { return _dwStrenthNum; }

								private:
									Fir::VarType _dwID;
									Fir::VarType _dwMaxLevel;
									Fir::VarType _dwNumber;
									Fir::VarType _dwStrenthNum;
							};

						public:
							void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
							{
								if (!node)
								{
									return;
								}
								const Fir::XMLParser::Node *stPower_node = xml.child(node, "stPower");
								while (stPower_node)
								{
									_stPower.load(xml, stPower_node);
									stPower_node = xml.next(stPower_node, "stPower");
								}
							}

							const stPower_t &stPower() const { return _stPower; }

						private:
							stPower_t _stPower;
					};

				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						if (!xml.has_attribute(node, "dwacceptPowerTimes"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "dwacceptPowerTimes");
							if (sub)
							{
								_dwacceptPowerTimes = xml.node_value(sub);
							}
						}
						else
						{
							_dwacceptPowerTimes = xml.node_attribute(node, "dwacceptPowerTimes");
						}
						if (!xml.has_attribute(node, "dwacceptStrengthPowerTimes"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "dwacceptStrengthPowerTimes");
							if (sub)
							{
								_dwacceptStrengthPowerTimes = xml.node_value(sub);
							}
						}
						else
						{
							_dwacceptStrengthPowerTimes = xml.node_attribute(node, "dwacceptStrengthPowerTimes");
						}
						if (!xml.has_attribute(node, "dwgivePowerTimes"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "dwgivePowerTimes");
							if (sub)
							{
								_dwgivePowerTimes = xml.node_value(sub);
							}
						}
						else
						{
							_dwgivePowerTimes = xml.node_attribute(node, "dwgivePowerTimes");
						}
						if (!xml.has_attribute(node, "dwgiveStrengthPowerTimes"))
						{
							const Fir::XMLParser::Node *sub = xml.child(node, "dwgiveStrengthPowerTimes");
							if (sub)
							{
								_dwgiveStrengthPowerTimes = xml.node_value(sub);
							}
						}
						else
						{
							_dwgiveStrengthPowerTimes = xml.node_attribute(node, "dwgiveStrengthPowerTimes");
						}
						const Fir::XMLParser::Node *mapGivePower_node = xml.child(node, "mapGivePower");
						while (mapGivePower_node)
						{
							_mapGivePower.load(xml, mapGivePower_node);
							mapGivePower_node = xml.next(mapGivePower_node, "mapGivePower");
						}
					}

					const Fir::VarType &dwacceptPowerTimes() const { return _dwacceptPowerTimes; }
					const Fir::VarType &dwacceptStrengthPowerTimes() const { return _dwacceptStrengthPowerTimes; }
					const Fir::VarType &dwgivePowerTimes() const { return _dwgivePowerTimes; }
					const Fir::VarType &dwgiveStrengthPowerTimes() const { return _dwgiveStrengthPowerTimes; }
					const mapGivePower_t &mapGivePower() const { return _mapGivePower; }

				private:
					Fir::VarType _dwacceptPowerTimes;
					Fir::VarType _dwacceptStrengthPowerTimes;
					Fir::VarType _dwgivePowerTimes;
					Fir::VarType _dwgiveStrengthPowerTimes;
					mapGivePower_t _mapGivePower;
			};

			struct stSignTaskConfig_t
			{
				public:
					struct vecSignList_t
					{
						public:
							struct stSign_t
							{
								public:
									struct vecItemList_t
									{
										public:
											struct stItem_t
											{
												public:
													void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
													{
														if (!node)
														{
															return;
														}
														if (!xml.has_attribute(node, "dwID"))
														{
															const Fir::XMLParser::Node *sub = xml.child(node, "dwID");
															if (sub)
															{
																_dwID = xml.node_value(sub);
															}
														}
														else
														{
															_dwID = xml.node_attribute(node, "dwID");
														}
														if (!xml.has_attribute(node, "dwNeedNum"))
														{
															const Fir::XMLParser::Node *sub = xml.child(node, "dwNeedNum");
															if (sub)
															{
																_dwNeedNum = xml.node_value(sub);
															}
														}
														else
														{
															_dwNeedNum = xml.node_attribute(node, "dwNeedNum");
														}
														if (!xml.has_attribute(node, "dwNum"))
														{
															const Fir::XMLParser::Node *sub = xml.child(node, "dwNum");
															if (sub)
															{
																_dwNum = xml.node_value(sub);
															}
														}
														else
														{
															_dwNum = xml.node_attribute(node, "dwNum");
														}
														if (!xml.has_attribute(node, "dwResType"))
														{
															const Fir::XMLParser::Node *sub = xml.child(node, "dwResType");
															if (sub)
															{
																_dwResType = xml.node_value(sub);
															}
														}
														else
														{
															_dwResType = xml.node_attribute(node, "dwResType");
														}
														if (!xml.has_attribute(node, "wdIndex"))
														{
															const Fir::XMLParser::Node *sub = xml.child(node, "wdIndex");
															if (sub)
															{
																_wdIndex = xml.node_value(sub);
															}
														}
														else
														{
															_wdIndex = xml.node_attribute(node, "wdIndex");
														}
													}

													const Fir::VarType &dwID() const { return _dwID; }
													const Fir::VarType &dwNeedNum() const { return _dwNeedNum; }
													const Fir::VarType &dwNum() const { return _dwNum; }
													const Fir::VarType &dwResType() const { return _dwResType; }
													const Fir::VarType &wdIndex() const { return _wdIndex; }

												private:
													Fir::VarType _dwID;
													Fir::VarType _dwNeedNum;
													Fir::VarType _dwNum;
													Fir::VarType _dwResType;
													Fir::VarType _wdIndex;
											};

										public:
											void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
											{
												if (!node)
												{
													return;
												}
												const Fir::XMLParser::Node *stItem_node = xml.child(node, "stItem");
												while (stItem_node)
												{
													_stItem.load(xml, stItem_node);
													stItem_node = xml.next(stItem_node, "stItem");
												}
											}

											const stItem_t &stItem() const { return _stItem; }

										private:
											stItem_t _stItem;
									};

								public:
									void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
									{
										if (!node)
										{
											return;
										}
										if (!xml.has_attribute(node, "tmEndTime"))
										{
											const Fir::XMLParser::Node *sub = xml.child(node, "tmEndTime");
											if (sub)
											{
												_tmEndTime = xml.node_value(sub);
											}
										}
										else
										{
											_tmEndTime = xml.node_attribute(node, "tmEndTime");
										}
										if (!xml.has_attribute(node, "tmStartTime"))
										{
											const Fir::XMLParser::Node *sub = xml.child(node, "tmStartTime");
											if (sub)
											{
												_tmStartTime = xml.node_value(sub);
											}
										}
										else
										{
											_tmStartTime = xml.node_attribute(node, "tmStartTime");
										}
										const Fir::XMLParser::Node *vecItemList_node = xml.child(node, "vecItemList");
										while (vecItemList_node)
										{
											_vecItemList.load(xml, vecItemList_node);
											vecItemList_node = xml.next(vecItemList_node, "vecItemList");
										}
									}

									const Fir::VarType &tmEndTime() const { return _tmEndTime; }
									const Fir::VarType &tmStartTime() const { return _tmStartTime; }
									const vecItemList_t &vecItemList() const { return _vecItemList; }

								private:
									Fir::VarType _tmEndTime;
									Fir::VarType _tmStartTime;
									vecItemList_t _vecItemList;
							};

						public:
							void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
							{
								if (!node)
								{
									return;
								}
								const Fir::XMLParser::Node *stSign_node = xml.child(node, "stSign");
								while (stSign_node)
								{
									_stSign.load(xml, stSign_node);
									stSign_node = xml.next(stSign_node, "stSign");
								}
							}

							const stSign_t &stSign() const { return _stSign; }

						private:
							stSign_t _stSign;
					};

				public:
					void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
					{
						if (!node)
						{
							return;
						}
						const Fir::XMLParser::Node *vecSignList_node = xml.child(node, "vecSignList");
						while (vecSignList_node)
						{
							_vecSignList.load(xml, vecSignList_node);
							vecSignList_node = xml.next(vecSignList_node, "vecSignList");
						}
					}

					const vecSignList_t &vecSignList() const { return _vecSignList; }

				private:
					vecSignList_t _vecSignList;
			};

		public:
			void load(const Fir::XMLParser &xml, const Fir::XMLParser::Node *node)
			{
				if (!node)
				{
					return;
				}
				const Fir::XMLParser::Node *septConfig_node = xml.child(node, "septConfig");
				while (septConfig_node)
				{
					_septConfig.load(xml, septConfig_node);
					septConfig_node = xml.next(septConfig_node, "septConfig");
				}
				const Fir::XMLParser::Node *stFriendConfig_node = xml.child(node, "stFriendConfig");
				while (stFriendConfig_node)
				{
					_stFriendConfig.load(xml, stFriendConfig_node);
					stFriendConfig_node = xml.next(stFriendConfig_node, "stFriendConfig");
				}
				const Fir::XMLParser::Node *stSignTaskConfig_node = xml.child(node, "stSignTaskConfig");
				while (stSignTaskConfig_node)
				{
					_stSignTaskConfig.load(xml, stSignTaskConfig_node);
					stSignTaskConfig_node = xml.next(stSignTaskConfig_node, "stSignTaskConfig");
				}
			}

			const septConfig_t &septConfig() const { return _septConfig; }
			const stFriendConfig_t &stFriendConfig() const { return _stFriendConfig; }
			const stSignTaskConfig_t &stSignTaskConfig() const { return _stSignTaskConfig; }

		private:
			septConfig_t _septConfig;
			stFriendConfig_t _stFriendConfig;
			stSignTaskConfig_t _stSignTaskConfig;
	};

}

#endif

