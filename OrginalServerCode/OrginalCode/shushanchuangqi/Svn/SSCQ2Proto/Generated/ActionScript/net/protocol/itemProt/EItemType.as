/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EItemType.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
 {
	import net.protocol.Message.ProtocolMessageProt18;
	/**
	 * 类型大类型
	 */
	public final class EItemType
	{
		public static const eItemNone:uint = 0; //无类型
		public static const eItemResource:uint = 1; //资源道具
		public static const eItemNormal:uint = 2; //普通道具
		public static const eItemTrump:uint = 3; //法宝
		public static const eItemEquipTrump:uint = 4; //装备法宝
		public static const eItemFashion:uint = 5; //时装
		public static const eItemFormation:uint = 6; //阵法
		public static const eItemCitta:uint = 7; //心法
		public static const eItemIntensify:uint = 8; //强化
		public static const eItemSkillBook:uint = 9; //技能书
		public static const eItemStone:uint = 10; //宝石
		public static const eItemStuff:uint = 11; //材料
		public static const eItemTask:uint = 12; //任务
		public static const eItemSpirit:uint = 13; //注灵
		public static const eItemSoul:uint = 14; //元神
		public static const eItemNeidan:uint = 15; //灵宠内丹
		public static const eItemVigour:uint = 16; //灵宠精魄
		public static const eItemOther:uint = 17; //其他
		public static const eItemEnd:uint = 18;
		public static const end:uint = eItemEnd;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eItemNone:
					return ProtocolMessageProt18.eItemNone;
				case eItemResource:
					return ProtocolMessageProt18.eItemResource;
				case eItemNormal:
					return ProtocolMessageProt18.eItemNormal;
				case eItemTrump:
					return ProtocolMessageProt18.eItemTrump;
				case eItemEquipTrump:
					return ProtocolMessageProt18.eItemEquipTrump;
				case eItemFashion:
					return ProtocolMessageProt18.eItemFashion;
				case eItemFormation:
					return ProtocolMessageProt18.eItemFormation;
				case eItemCitta:
					return ProtocolMessageProt18.eItemCitta;
				case eItemIntensify:
					return ProtocolMessageProt18.eItemIntensify;
				case eItemSkillBook:
					return ProtocolMessageProt18.eItemSkillBook;
				case eItemStone:
					return ProtocolMessageProt18.eItemStone;
				case eItemStuff:
					return ProtocolMessageProt18.eItemStuff;
				case eItemTask:
					return ProtocolMessageProt18.eItemTask;
				case eItemSpirit:
					return ProtocolMessageProt18.eItemSpirit;
				case eItemSoul:
					return ProtocolMessageProt18.eItemSoul;
				case eItemNeidan:
					return ProtocolMessageProt18.eItemNeidan;
				case eItemVigour:
					return ProtocolMessageProt18.eItemVigour;
				case eItemOther:
					return ProtocolMessageProt18.eItemOther;
				case eItemEnd:
					return ProtocolMessageProt18.eItemEnd;
				default:
					return "Unknown Error";
			}
		}
	}
}
