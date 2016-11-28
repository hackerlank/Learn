/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EItemSubType.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
 {
	import net.protocol.Message.ProtocolMessageProt18;
	/**
	 * 物品子类型
	 */
	public final class EItemSubType
	{
		public static const eItemSubNone:uint = 0; //无类型
		public static const eItemSubResource:uint = 1; //资源
		public static const eItemSubNormal:uint = 2; //普通
		public static const eItemSubFasionMaterial:uint = 10; //时装激活材料
		public static const eItemSubZTMaterial:uint = 20; //本命法宝温养材料
		public static const eItemSubWepaon:uint = 21; //武器
		public static const eItemSubRing:uint = 22; //戒指
		public static const eItemSubNeck:uint = 23; //项链
		public static const eItemSubHead:uint = 24; //头盔
		public static const eItemSubChest:uint = 25; //胸甲
		public static const eItemSubLegging:uint = 26; //护腿
		public static const eItemSubMounts:uint = 30; //坐骑
		public static const eItemSubActiveTrump:uint = 32; //主动法宝
		public static const eItemSubPassiveTrump:uint = 33; //被动法宝
		public static const eItemSubFashion:uint = 51; //时装-神器
		public static const eItemSubFashion2:uint = 52; //时装-神衣
		public static const eItemSubSpirit:uint = 141; //注灵
		public static const eItemSubPetSoul:uint = 151; //兽魂
		public static const eItemSubEquipTrumpInnate:uint = 205; //先天
		public static const eItemSubEquipTrumpPassive:uint = 206; //被动
		public static const eItemSubEquipTrumpTransform:uint = 207; //光环
		public static const eItemSubEquipTrumpHalo:uint = 208; //变身
		public static const end:uint = eItemSubEquipTrumpHalo;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eItemSubNone:
					return ProtocolMessageProt18.eItemSubNone;
				case eItemSubResource:
					return ProtocolMessageProt18.eItemSubResource;
				case eItemSubNormal:
					return ProtocolMessageProt18.eItemSubNormal;
				case eItemSubFasionMaterial:
					return ProtocolMessageProt18.eItemSubFasionMaterial;
				case eItemSubZTMaterial:
					return ProtocolMessageProt18.eItemSubZTMaterial;
				case eItemSubWepaon:
					return ProtocolMessageProt18.eItemSubWepaon;
				case eItemSubRing:
					return ProtocolMessageProt18.eItemSubRing;
				case eItemSubNeck:
					return ProtocolMessageProt18.eItemSubNeck;
				case eItemSubHead:
					return ProtocolMessageProt18.eItemSubHead;
				case eItemSubChest:
					return ProtocolMessageProt18.eItemSubChest;
				case eItemSubLegging:
					return ProtocolMessageProt18.eItemSubLegging;
				case eItemSubMounts:
					return ProtocolMessageProt18.eItemSubMounts;
				case eItemSubActiveTrump:
					return ProtocolMessageProt18.eItemSubActiveTrump;
				case eItemSubPassiveTrump:
					return ProtocolMessageProt18.eItemSubPassiveTrump;
				case eItemSubFashion:
					return ProtocolMessageProt18.eItemSubFashion;
				case eItemSubFashion2:
					return ProtocolMessageProt18.eItemSubFashion2;
				case eItemSubSpirit:
					return ProtocolMessageProt18.eItemSubSpirit;
				case eItemSubPetSoul:
					return ProtocolMessageProt18.eItemSubPetSoul;
				case eItemSubEquipTrumpInnate:
					return ProtocolMessageProt18.eItemSubEquipTrumpInnate;
				case eItemSubEquipTrumpPassive:
					return ProtocolMessageProt18.eItemSubEquipTrumpPassive;
				case eItemSubEquipTrumpTransform:
					return ProtocolMessageProt18.eItemSubEquipTrumpTransform;
				case eItemSubEquipTrumpHalo:
					return ProtocolMessageProt18.eItemSubEquipTrumpHalo;
				default:
					return "Unknown Error";
			}
		}
	}
}
