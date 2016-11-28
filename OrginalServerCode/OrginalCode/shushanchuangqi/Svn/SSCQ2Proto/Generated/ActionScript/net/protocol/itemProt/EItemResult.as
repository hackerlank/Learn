/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EItemResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
 {
	import net.protocol.Message.ProtocolMessageProt18;
	/**
	 * 使用道具结果
	 */
	public final class EItemResult
	{
		public static const eItemSucceed:uint = 0; //成功
		public static const eItemFailed:uint = 1; //失败
		public static const eItemNotEnougth:uint = 2; //道具使用个数不足
		public static const eItemNotExist:uint = 3; //道具不存在
		public static const eItemErrBind:uint = 4; //道具为绑定
		public static const eItemErrUse:uint = 5; //道具无法使用
		public static const eItemStoreFull:uint = 6; //包裹或仓库满
		public static const eItemStoreErr:uint = 7; //包裹或仓库错误
		public static const eItemRangeErr:uint = 8; //道具距离过远
		public static const eItemNoStack:uint = 9; //道具为非堆叠的
		public static const eItemNoCoin:uint = 10; //游戏币不足
		public static const eItemCoinFull:uint = 11; //游戏币超出上限
		public static const eItemNoMoney:uint = 12; //仙石不足
		public static const eItemMoneyFull:uint = 13; //充值货币超出上限
		public static const eItemErrOper:uint = 14; //操作非法
		public static const eItemErrCD:uint = 15; //CD时间未到
		public static const eItemErrSlot:uint = 16; //装备位错误
		public static const eItemNotNeed:uint = 17; //无需此操作
		public static const eItemErrName:uint = 18; //名字太长
		public static const eItemExpired:uint = 19; //道具使用时间过期
		public static const eItemErrSell:uint = 20; //道具无法出售
		public static const eItemErrDrop:uint = 21; //道具无法丢弃
		public static const eItemErrLevel:uint = 22; //使用等级不够
		public static const eItemErrJob:uint = 23; //使用职业限制
		public static const eItemNoStuff:uint = 24; //材料不足
		public static const eItemErrDungeon:uint = 25; //副本中无法使用传送卷轴
		public static const eItemErrTransfMap:uint = 26; //该地图中无法使用传送卷轴
		public static const eItemMountExist:uint = 27; //已存在该坐骑
		public static const eItemMutualEquip:uint = 28; //属性类型
		public static const eItemMutual:uint = 29; //属性类型
		public static const eItemNoTakeOff:uint = 30; //无法脱下
		public static const eItemSkillExist:uint = 31; //该技能已存在
		public static const eItemFashionExist:uint = 32; //该时装已存在
		public static const eItemStoreMax:uint = 33; //背包已达上限
		public static const eItemDepotMax:uint = 34; //仓库已达上限
		public static const eItemErrOther:uint = 35; //其它错误
		public static const end:uint = eItemErrOther;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eItemSucceed:
					return ProtocolMessageProt18.eItemSucceed;
				case eItemFailed:
					return ProtocolMessageProt18.eItemFailed;
				case eItemNotEnougth:
					return ProtocolMessageProt18.eItemNotEnougth;
				case eItemNotExist:
					return ProtocolMessageProt18.eItemNotExist;
				case eItemErrBind:
					return ProtocolMessageProt18.eItemErrBind;
				case eItemErrUse:
					return ProtocolMessageProt18.eItemErrUse;
				case eItemStoreFull:
					return ProtocolMessageProt18.eItemStoreFull;
				case eItemStoreErr:
					return ProtocolMessageProt18.eItemStoreErr;
				case eItemRangeErr:
					return ProtocolMessageProt18.eItemRangeErr;
				case eItemNoStack:
					return ProtocolMessageProt18.eItemNoStack;
				case eItemNoCoin:
					return ProtocolMessageProt18.eItemNoCoin;
				case eItemCoinFull:
					return ProtocolMessageProt18.eItemCoinFull;
				case eItemNoMoney:
					return ProtocolMessageProt18.eItemNoMoney;
				case eItemMoneyFull:
					return ProtocolMessageProt18.eItemMoneyFull;
				case eItemErrOper:
					return ProtocolMessageProt18.eItemErrOper;
				case eItemErrCD:
					return ProtocolMessageProt18.eItemErrCD;
				case eItemErrSlot:
					return ProtocolMessageProt18.eItemErrSlot;
				case eItemNotNeed:
					return ProtocolMessageProt18.eItemNotNeed;
				case eItemErrName:
					return ProtocolMessageProt18.eItemErrName;
				case eItemExpired:
					return ProtocolMessageProt18.eItemExpired;
				case eItemErrSell:
					return ProtocolMessageProt18.eItemErrSell;
				case eItemErrDrop:
					return ProtocolMessageProt18.eItemErrDrop;
				case eItemErrLevel:
					return ProtocolMessageProt18.eItemErrLevel;
				case eItemErrJob:
					return ProtocolMessageProt18.eItemErrJob;
				case eItemNoStuff:
					return ProtocolMessageProt18.eItemNoStuff;
				case eItemErrDungeon:
					return ProtocolMessageProt18.eItemErrDungeon;
				case eItemErrTransfMap:
					return ProtocolMessageProt18.eItemErrTransfMap;
				case eItemMountExist:
					return ProtocolMessageProt18.eItemMountExist;
				case eItemMutualEquip:
					return ProtocolMessageProt18.eItemMutualEquip;
				case eItemMutual:
					return ProtocolMessageProt18.eItemMutual;
				case eItemNoTakeOff:
					return ProtocolMessageProt18.eItemNoTakeOff;
				case eItemSkillExist:
					return ProtocolMessageProt18.eItemSkillExist;
				case eItemFashionExist:
					return ProtocolMessageProt18.eItemFashionExist;
				case eItemStoreMax:
					return ProtocolMessageProt18.eItemStoreMax;
				case eItemDepotMax:
					return ProtocolMessageProt18.eItemDepotMax;
				case eItemErrOther:
					return ProtocolMessageProt18.eItemErrOther;
				default:
					return "Unknown Error";
			}
		}
	}
}
