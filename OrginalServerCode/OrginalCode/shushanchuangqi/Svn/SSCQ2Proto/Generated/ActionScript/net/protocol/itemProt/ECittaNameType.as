/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ECittaNameType.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
 {
	import net.protocol.Message.ProtocolMessageProt18;
	/**
	 * 心法姓名前缀类型
	 */
	public final class ECittaNameType
	{
		public static const eNameNone:uint = 0; //破烂之
		public static const eNameAttack:uint = 1; //力量之
		public static const eNameDefence:uint = 2; //坚固的
		public static const eNameMgcDefence:uint = 3; //道心之
		public static const eNameHP:uint = 4; //长生的
		public static const eNameHit:uint = 5; //神佑的
		public static const eNameDodge:uint = 6; //灵猴的
		public static const eNameCritical:uint = 7; //刺客的
		public static const eNameAntiCri:uint = 8; //平衡的
		public static const eNamePiece:uint = 9; //破击之
		public static const eNameCounter:uint = 10; //反击之
		public static const eNameResist:uint = 11; //压制的
		public static const end:uint = eNameResist;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eNameNone:
					return ProtocolMessageProt18.eNameNone;
				case eNameAttack:
					return ProtocolMessageProt18.eNameAttack;
				case eNameDefence:
					return ProtocolMessageProt18.eNameDefence;
				case eNameMgcDefence:
					return ProtocolMessageProt18.eNameMgcDefence;
				case eNameHP:
					return ProtocolMessageProt18.eNameHP;
				case eNameHit:
					return ProtocolMessageProt18.eNameHit;
				case eNameDodge:
					return ProtocolMessageProt18.eNameDodge;
				case eNameCritical:
					return ProtocolMessageProt18.eNameCritical;
				case eNameAntiCri:
					return ProtocolMessageProt18.eNameAntiCri;
				case eNamePiece:
					return ProtocolMessageProt18.eNamePiece;
				case eNameCounter:
					return ProtocolMessageProt18.eNameCounter;
				case eNameResist:
					return ProtocolMessageProt18.eNameResist;
				default:
					return "Unknown Error";
			}
		}
	}
}
