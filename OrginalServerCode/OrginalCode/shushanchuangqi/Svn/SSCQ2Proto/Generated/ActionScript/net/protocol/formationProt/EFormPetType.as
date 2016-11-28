/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EFormPetType.as
//  Purpose:      阵灵相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.formationProt
 {
	import net.protocol.Message.ProtocolMessageProt22;
	/**
	 * 阵形、阵灵、兽魂操作结果
	 */
	public final class EFormPetType
	{
		public static const eFormPetSucc:uint = 0; //成功
		public static const eFormPetFalied:uint = 1; //失败
		public static const eFormPetMainFighterErr:uint = 2; //主将不能下阵
		public static const eFormPetItemErr:uint = 3; //解锁道具不足
		public static const eFormPetPetLevelItemErr:uint = 4; //阵灵升级道具不足
		public static const end:uint = eFormPetPetLevelItemErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eFormPetSucc:
					return ProtocolMessageProt22.eFormPetSucc;
				case eFormPetFalied:
					return ProtocolMessageProt22.eFormPetFalied;
				case eFormPetMainFighterErr:
					return ProtocolMessageProt22.eFormPetMainFighterErr;
				case eFormPetItemErr:
					return ProtocolMessageProt22.eFormPetItemErr;
				case eFormPetPetLevelItemErr:
					return ProtocolMessageProt22.eFormPetPetLevelItemErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
