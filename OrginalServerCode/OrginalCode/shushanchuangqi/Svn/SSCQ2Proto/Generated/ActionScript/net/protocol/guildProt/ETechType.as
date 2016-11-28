/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ETechType.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 帮派建筑类型
	 */
	public final class ETechType
	{
		public static const eTechNone:uint = 0; //无效科技
		public static const eTechAttack:uint = 1; //攻击之魂
		public static const eTechPhyDef:uint = 2; //物防之魂
		public static const eTechMgcDef:uint = 3; //魔防之魂
		public static const eTechHP:uint = 4; //生命之魂
		public static const eTechSpeed:uint = 5; //身法之魂
		public static const eTechHit:uint = 6; //命中之魂
		public static const eTechDodge:uint = 7; //闪避之魂
		public static const eTechCritial:uint = 8; //暴击之魂
		public static const eTechAntiCritial:uint = 9; //稳固之魂
		public static const eTechPierce:uint = 10; //穿透之魂
		public static const eTechCounter:uint = 11; //反击之魂
		public static const eTechResist:uint = 12; //压制之魂
		public static const eTechMax:uint = 13; //最高科技
		public static const end:uint = eTechMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eTechNone:
					return ProtocolMessageProt16.eTechNone;
				case eTechAttack:
					return ProtocolMessageProt16.eTechAttack;
				case eTechPhyDef:
					return ProtocolMessageProt16.eTechPhyDef;
				case eTechMgcDef:
					return ProtocolMessageProt16.eTechMgcDef;
				case eTechHP:
					return ProtocolMessageProt16.eTechHP;
				case eTechSpeed:
					return ProtocolMessageProt16.eTechSpeed;
				case eTechHit:
					return ProtocolMessageProt16.eTechHit;
				case eTechDodge:
					return ProtocolMessageProt16.eTechDodge;
				case eTechCritial:
					return ProtocolMessageProt16.eTechCritial;
				case eTechAntiCritial:
					return ProtocolMessageProt16.eTechAntiCritial;
				case eTechPierce:
					return ProtocolMessageProt16.eTechPierce;
				case eTechCounter:
					return ProtocolMessageProt16.eTechCounter;
				case eTechResist:
					return ProtocolMessageProt16.eTechResist;
				case eTechMax:
					return ProtocolMessageProt16.eTechMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
