/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ETrumpResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
 {
	import net.protocol.Message.ProtocolMessageProt18;
	/**
	 * 装备养成结果
	 */
	public final class ETrumpResult
	{
		public static const eTrumpSuccess:uint = 0; //法宝养成成功
		public static const eTrumpFailed:uint = 1; //法宝养成失败
		public static const eTrumpExist:uint = 2; //法宝已经存在
		public static const eTrumpNotifyFailed:uint = 3; //法宝通知失败
		public static const eTrumpNotActived:uint = 4; //法宝未激活
		public static const eTrumpNotExist:uint = 5; //法宝不存在
		public static const eTrumpUpgradeMaterialLack:uint = 6; //法宝强化材料不足
		public static const eTrumpEvolveMaterialLack:uint = 7; //法宝升阶材料不足
		public static const eTrumpFull:uint = 8; //法宝位已满
		public static const eTrumpIsEquiped:uint = 9; //法宝已装备
		public static const eTrumpNotEquiped:uint = 10; //法宝未装备
		public static const eTrumpActiveFailed:uint = 11; //法宝解锁失败
		public static const end:uint = eTrumpActiveFailed;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eTrumpSuccess:
					return ProtocolMessageProt18.eTrumpSuccess;
				case eTrumpFailed:
					return ProtocolMessageProt18.eTrumpFailed;
				case eTrumpExist:
					return ProtocolMessageProt18.eTrumpExist;
				case eTrumpNotifyFailed:
					return ProtocolMessageProt18.eTrumpNotifyFailed;
				case eTrumpNotActived:
					return ProtocolMessageProt18.eTrumpNotActived;
				case eTrumpNotExist:
					return ProtocolMessageProt18.eTrumpNotExist;
				case eTrumpUpgradeMaterialLack:
					return ProtocolMessageProt18.eTrumpUpgradeMaterialLack;
				case eTrumpEvolveMaterialLack:
					return ProtocolMessageProt18.eTrumpEvolveMaterialLack;
				case eTrumpFull:
					return ProtocolMessageProt18.eTrumpFull;
				case eTrumpIsEquiped:
					return ProtocolMessageProt18.eTrumpIsEquiped;
				case eTrumpNotEquiped:
					return ProtocolMessageProt18.eTrumpNotEquiped;
				case eTrumpActiveFailed:
					return ProtocolMessageProt18.eTrumpActiveFailed;
				default:
					return "Unknown Error";
			}
		}
	}
}
