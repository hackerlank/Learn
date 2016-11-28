/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBeastSoulType.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
 {
	import net.protocol.Message.ProtocolMessageProt10;
	/**
	 * 兽魂种类
	 */
	public final class EBeastSoulType
	{
		public static const eBeastSoulNone:uint = 0; //无加成
		public static const eBeastSoulAtttack:uint = 1; //攻击之魂
		public static const eBeastSoulHP:uint = 2; //生命之魂
		public static const eBeastSoulCritical:uint = 3; //暴击之魂
		public static const eBeastSoulCounter:uint = 4; //反击之魂
		public static const eBeastSoulSpeed:uint = 5; //身法之魂
		public static const eBeastSoulDefence:uint = 6; //防御之魂
		public static const eBeastSoulHit:uint = 7; //命中之魂
		public static const eBeastSoulDodge:uint = 8; //闪避之魂
		public static const eBeastSoulMax:uint = 9; //最大
		public static const end:uint = eBeastSoulMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eBeastSoulNone:
					return ProtocolMessageProt10.eBeastSoulNone;
				case eBeastSoulAtttack:
					return ProtocolMessageProt10.eBeastSoulAtttack;
				case eBeastSoulHP:
					return ProtocolMessageProt10.eBeastSoulHP;
				case eBeastSoulCritical:
					return ProtocolMessageProt10.eBeastSoulCritical;
				case eBeastSoulCounter:
					return ProtocolMessageProt10.eBeastSoulCounter;
				case eBeastSoulSpeed:
					return ProtocolMessageProt10.eBeastSoulSpeed;
				case eBeastSoulDefence:
					return ProtocolMessageProt10.eBeastSoulDefence;
				case eBeastSoulHit:
					return ProtocolMessageProt10.eBeastSoulHit;
				case eBeastSoulDodge:
					return ProtocolMessageProt10.eBeastSoulDodge;
				case eBeastSoulMax:
					return ProtocolMessageProt10.eBeastSoulMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
