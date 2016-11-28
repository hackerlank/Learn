/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBeautyRet.as
//  Purpose:      美女系统
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.beauty
 {
	import net.protocol.Message.ProtocolMessageProt131;
	/**
	 * 美女系统操作结果
	 */
	public final class EBeautyRet
	{
		public static const eBeautyRet_Sucess:uint = 0; //成功
		public static const eBeautyRet_LevelLimit:uint = 1; //等级不够
		public static const eBeautyRet_ErrorCFG:uint = 2; //配置错误
		public static const eBeautyRet_PackError:uint = 3; //背包格子不够
		public static const eBeautyRet_MoneyError:uint = 4; //钱不够
		public static const eBeautyRet_HeartError:uint = 5; //爱心不够
		public static const eBeautyRet_ErrorID:uint = 6; //美女ID错误
		public static const eBeautyRet_ChatCd:uint = 7; //聊天cd限制
		public static const eBeautyRet_LackItem:uint = 8; //物品不够
		public static const eBeautyRet_ExistBeauty:uint = 9; //已结识美女
		public static const eBeautyRet_GondError:uint = 10; //激活条件不满足
		public static const eBeautyRet_LotterTypeError:uint = 11; //抽奖类型错误
		public static const end:uint = eBeautyRet_LotterTypeError;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eBeautyRet_Sucess:
					return ProtocolMessageProt131.eBeautyRet_Sucess;
				case eBeautyRet_LevelLimit:
					return ProtocolMessageProt131.eBeautyRet_LevelLimit;
				case eBeautyRet_ErrorCFG:
					return ProtocolMessageProt131.eBeautyRet_ErrorCFG;
				case eBeautyRet_PackError:
					return ProtocolMessageProt131.eBeautyRet_PackError;
				case eBeautyRet_MoneyError:
					return ProtocolMessageProt131.eBeautyRet_MoneyError;
				case eBeautyRet_HeartError:
					return ProtocolMessageProt131.eBeautyRet_HeartError;
				case eBeautyRet_ErrorID:
					return ProtocolMessageProt131.eBeautyRet_ErrorID;
				case eBeautyRet_ChatCd:
					return ProtocolMessageProt131.eBeautyRet_ChatCd;
				case eBeautyRet_LackItem:
					return ProtocolMessageProt131.eBeautyRet_LackItem;
				case eBeautyRet_ExistBeauty:
					return ProtocolMessageProt131.eBeautyRet_ExistBeauty;
				case eBeautyRet_GondError:
					return ProtocolMessageProt131.eBeautyRet_GondError;
				case eBeautyRet_LotterTypeError:
					return ProtocolMessageProt131.eBeautyRet_LotterTypeError;
				default:
					return "Unknown Error";
			}
		}
	}
}
