/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGemstoneResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
 {
	import net.protocol.Message.ProtocolMessageProt18;
	/**
	 * 宝石操作
	 */
	public final class EGemstoneResult
	{
		public static const eGemstoneSuccess:uint = 0; //宝石操作成功
		public static const eGemstoneFailed:uint = 1; //宝石操作失败
		public static const eGemstoneSlotNotEmpty:uint = 2; //宝石位置非空
		public static const eGemstoneSlotEmpty:uint = 3; //宝石位置空
		public static const eGemstonePackFull:uint = 4; //包裹满
		public static const eGemstoneHeroErr:uint = 5; //将错误
		public static const eGemstoneNoStone:uint = 6; //没有找到宝石
		public static const eGemstoneErrStone:uint = 7; //宝石合成目标不存在
		public static const eGemstoneMaterialLack:uint = 8; //宝石材料不足
		public static const eGemstoneHasSameType:uint = 9; //已经装备相同类型宝石
		public static const end:uint = eGemstoneHasSameType;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGemstoneSuccess:
					return ProtocolMessageProt18.eGemstoneSuccess;
				case eGemstoneFailed:
					return ProtocolMessageProt18.eGemstoneFailed;
				case eGemstoneSlotNotEmpty:
					return ProtocolMessageProt18.eGemstoneSlotNotEmpty;
				case eGemstoneSlotEmpty:
					return ProtocolMessageProt18.eGemstoneSlotEmpty;
				case eGemstonePackFull:
					return ProtocolMessageProt18.eGemstonePackFull;
				case eGemstoneHeroErr:
					return ProtocolMessageProt18.eGemstoneHeroErr;
				case eGemstoneNoStone:
					return ProtocolMessageProt18.eGemstoneNoStone;
				case eGemstoneErrStone:
					return ProtocolMessageProt18.eGemstoneErrStone;
				case eGemstoneMaterialLack:
					return ProtocolMessageProt18.eGemstoneMaterialLack;
				case eGemstoneHasSameType:
					return ProtocolMessageProt18.eGemstoneHasSameType;
				default:
					return "Unknown Error";
			}
		}
	}
}
