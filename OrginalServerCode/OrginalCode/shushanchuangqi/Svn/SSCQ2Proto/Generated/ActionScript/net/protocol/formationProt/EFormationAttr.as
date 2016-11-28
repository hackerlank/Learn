/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EFormationAttr.as
//  Purpose:      阵灵相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.formationProt
 {
	import net.protocol.Message.ProtocolMessageProt22;
	/**
	 * 阵型解锁属性
	 */
	public final class EFormationAttr
	{
		public static const eFormAttrNone:uint = 0; //无加成
		public static const eFormAttrSpeed:uint = 1; //身法
		public static const eFormAttrHit:uint = 2; //命中
		public static const eFormAttrEva:uint = 3; //闪避
		public static const eFormAttrCrit:uint = 4; //暴击
		public static const eFormAttrAntiCrit:uint = 5; //抗暴
		public static const eFormAttrCount:uint = 6; //反击
		public static const eFormAttrAntiCount:uint = 7; //抵抗
		public static const eFormAttrAp:uint = 8; //破击
		public static const eFormAttrMax:uint = 9; //最大
		public static const end:uint = eFormAttrMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eFormAttrNone:
					return ProtocolMessageProt22.eFormAttrNone;
				case eFormAttrSpeed:
					return ProtocolMessageProt22.eFormAttrSpeed;
				case eFormAttrHit:
					return ProtocolMessageProt22.eFormAttrHit;
				case eFormAttrEva:
					return ProtocolMessageProt22.eFormAttrEva;
				case eFormAttrCrit:
					return ProtocolMessageProt22.eFormAttrCrit;
				case eFormAttrAntiCrit:
					return ProtocolMessageProt22.eFormAttrAntiCrit;
				case eFormAttrCount:
					return ProtocolMessageProt22.eFormAttrCount;
				case eFormAttrAntiCount:
					return ProtocolMessageProt22.eFormAttrAntiCount;
				case eFormAttrAp:
					return ProtocolMessageProt22.eFormAttrAp;
				case eFormAttrMax:
					return ProtocolMessageProt22.eFormAttrMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
