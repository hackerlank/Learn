/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMallResult.as
//  Purpose:      商城相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mallProt
 {
	import net.protocol.Message.ProtocolMessageProt27;
	/**
	 * 商城操作结果
	 */
	public final class EMallResult
	{
		public static const eMallResultSucc:int = 0; //成功
		public static const eMallResultFailed:int = 1; //失败
		public static const eMallResultStore:int = 2; //背包空间不足
		public static const eMallResultStoreAdd:int = 3; //物品加入背包出错
		public static const eMallResultMoney:int = 4; //购买时相应货币不足
		public static const eMallResultNoItem:int = 5; //所购买的物品已下架
		public static const eMallResultFashionErr:int = 6; //所购买的时装不能加入背包
		public static const eMallResultFashionAlready:int = 7; //所购买的时装已存在
		public static const eMallPresentSucc:int = 8; //赠送成功
		public static const eMallPresentNoTarget:int = 9; //赠送的玩家不存在
		public static const eMallResultDiscountOverTime:int = 10; //限购活动已过期
		public static const eMallResultDiscountFull:int = 11; //超出限购数量限制
		public static const eMallResultDiscountRechargeErr:int = 12; //未达到限购充值仙石数量
		public static const eMallResultDiscountConsumeErr:int = 13; //未达到限购消耗仙石数量
		public static const eMallResultItemCount:int = 14; //没有购买次数
		public static const end:int = eMallResultItemCount;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:int):String
		{
			switch(value)
			{
				case eMallResultSucc:
					return ProtocolMessageProt27.eMallResultSucc;
				case eMallResultFailed:
					return ProtocolMessageProt27.eMallResultFailed;
				case eMallResultStore:
					return ProtocolMessageProt27.eMallResultStore;
				case eMallResultStoreAdd:
					return ProtocolMessageProt27.eMallResultStoreAdd;
				case eMallResultMoney:
					return ProtocolMessageProt27.eMallResultMoney;
				case eMallResultNoItem:
					return ProtocolMessageProt27.eMallResultNoItem;
				case eMallResultFashionErr:
					return ProtocolMessageProt27.eMallResultFashionErr;
				case eMallResultFashionAlready:
					return ProtocolMessageProt27.eMallResultFashionAlready;
				case eMallPresentSucc:
					return ProtocolMessageProt27.eMallPresentSucc;
				case eMallPresentNoTarget:
					return ProtocolMessageProt27.eMallPresentNoTarget;
				case eMallResultDiscountOverTime:
					return ProtocolMessageProt27.eMallResultDiscountOverTime;
				case eMallResultDiscountFull:
					return ProtocolMessageProt27.eMallResultDiscountFull;
				case eMallResultDiscountRechargeErr:
					return ProtocolMessageProt27.eMallResultDiscountRechargeErr;
				case eMallResultDiscountConsumeErr:
					return ProtocolMessageProt27.eMallResultDiscountConsumeErr;
				case eMallResultItemCount:
					return ProtocolMessageProt27.eMallResultItemCount;
				default:
					return "Unknown Error";
			}
		}
	}
}
