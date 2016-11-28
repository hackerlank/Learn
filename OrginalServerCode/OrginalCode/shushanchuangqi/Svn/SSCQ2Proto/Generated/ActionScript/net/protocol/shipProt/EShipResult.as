/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EShipResult.as
//  Purpose:      元江金船协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shipProt
 {
	import net.protocol.Message.ProtocolMessageProt84;
	/**
	 * 金船操作结果
	 */
	public final class EShipResult
	{
		public static const EShip_Suc:uint = 0; //成功
		public static const EShip_NoShip:uint = 1; //船不存在
		public static const EShip_NoFlushShip:uint = 2; //你没有刷船
		public static const EShip_NoFlushShip2:uint = 3; //邀请你的人没有刷船
		public static const EShip_DeFenseIsAgree:uint = 4; //已经有人同意帮你护送
		public static const EShip_DeFenseIsAgree2:uint = 5; //已经有人同意帮船主护送
		public static const EShip_DriveHasShip:uint = 6; //你的船已开
		public static const EShip_DriveHasShip2:uint = 7; //邀请你的人的船已开
		public static const EShip_InviteDeFenseOffLine:uint = 8; //你邀请的人不在线
		public static const EShip_InviteDeFenseOffLine2:uint = 9; //船主不在线
		public static const EShip_DeFenseAgreeOther:uint = 10; //你邀请的人答应护送其他船
		public static const EShip_DeFenseAgreeOther2:uint = 11; //你已答应护送其他船
		public static const EShip_DeFenseOtherShip:uint = 12; //你邀请的人在护送其他船
		public static const EShip_DeFenseOtherShip2:uint = 13; //你在护送其他船
		public static const EShip_OtherDeFenseTimesOut:uint = 14; //你邀请的人护送次数用完
		public static const EShip_OtherDeFenseTimesOut2:uint = 15; //你的护送次数用完
		public static const EShip_DeFenseDisAgree:uint = 16; //邀请的人不同意帮你护送
		public static const EShip_DeFenseDisAgree2:uint = 17; //邀请的人不同意帮你护送
		public static const EShip_DeFenseErrFriend:uint = 18; //他不是你的护卫
		public static const EShip_BuyOpenGoldLimit:uint = 19; //购买运船仙石不足
		public static const EShip_BuyRobGoldLimit:uint = 20; //购买抢劫仙石不足
		public static const EShip_RelushGoldLimit:uint = 21; //购买刷新次数仙石不足
		public static const EShip_RelushShipUpLimit:uint = 22; //刷新次数用完
		public static const EShip_DriveOverLimit:uint = 23; //今日开船到达上限
		public static const EShip_DriveGoldLimit:uint = 24; //开船金币不足
		public static const EShip_ROBOverLimit:uint = 25; //今日抢劫次数到达上限
		public static const EShip_ROBOverShip:uint = 26; //这条船被抢劫次数到达上限
		public static const EShip_ROBDone:uint = 27; //这条船你已经打劫
		public static const EShip_ROBSelf:uint = 28; //这条船被你护卫或者是你的，不可抢劫
		public static const EShip_GRABErrOwer:uint = 29; //这条船不是你的或者你不是护卫，不可返抢
		public static const EShip_GRABErr:uint = 30; //返抢对手错误
		public static const EShip_BattleCool:uint = 31; //战斗冷却
		public static const EShip_FinishOneKeyNoGold:uint = 32; //一键完成运船金币不足
		public static const EShip_GetShipOneKeyNoGold:uint = 33; //一键召唤Vip金币不足
		public static const EShip_GetShipOneKeyNoVip:uint = 34; //一键召唤Vip等级不足
		public static const EShip_OtherErr:uint = 35; //其他错误
		public static const end:uint = EShip_OtherErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EShip_Suc:
					return ProtocolMessageProt84.EShip_Suc;
				case EShip_NoShip:
					return ProtocolMessageProt84.EShip_NoShip;
				case EShip_NoFlushShip:
					return ProtocolMessageProt84.EShip_NoFlushShip;
				case EShip_NoFlushShip2:
					return ProtocolMessageProt84.EShip_NoFlushShip2;
				case EShip_DeFenseIsAgree:
					return ProtocolMessageProt84.EShip_DeFenseIsAgree;
				case EShip_DeFenseIsAgree2:
					return ProtocolMessageProt84.EShip_DeFenseIsAgree2;
				case EShip_DriveHasShip:
					return ProtocolMessageProt84.EShip_DriveHasShip;
				case EShip_DriveHasShip2:
					return ProtocolMessageProt84.EShip_DriveHasShip2;
				case EShip_InviteDeFenseOffLine:
					return ProtocolMessageProt84.EShip_InviteDeFenseOffLine;
				case EShip_InviteDeFenseOffLine2:
					return ProtocolMessageProt84.EShip_InviteDeFenseOffLine2;
				case EShip_DeFenseAgreeOther:
					return ProtocolMessageProt84.EShip_DeFenseAgreeOther;
				case EShip_DeFenseAgreeOther2:
					return ProtocolMessageProt84.EShip_DeFenseAgreeOther2;
				case EShip_DeFenseOtherShip:
					return ProtocolMessageProt84.EShip_DeFenseOtherShip;
				case EShip_DeFenseOtherShip2:
					return ProtocolMessageProt84.EShip_DeFenseOtherShip2;
				case EShip_OtherDeFenseTimesOut:
					return ProtocolMessageProt84.EShip_OtherDeFenseTimesOut;
				case EShip_OtherDeFenseTimesOut2:
					return ProtocolMessageProt84.EShip_OtherDeFenseTimesOut2;
				case EShip_DeFenseDisAgree:
					return ProtocolMessageProt84.EShip_DeFenseDisAgree;
				case EShip_DeFenseDisAgree2:
					return ProtocolMessageProt84.EShip_DeFenseDisAgree2;
				case EShip_DeFenseErrFriend:
					return ProtocolMessageProt84.EShip_DeFenseErrFriend;
				case EShip_BuyOpenGoldLimit:
					return ProtocolMessageProt84.EShip_BuyOpenGoldLimit;
				case EShip_BuyRobGoldLimit:
					return ProtocolMessageProt84.EShip_BuyRobGoldLimit;
				case EShip_RelushGoldLimit:
					return ProtocolMessageProt84.EShip_RelushGoldLimit;
				case EShip_RelushShipUpLimit:
					return ProtocolMessageProt84.EShip_RelushShipUpLimit;
				case EShip_DriveOverLimit:
					return ProtocolMessageProt84.EShip_DriveOverLimit;
				case EShip_DriveGoldLimit:
					return ProtocolMessageProt84.EShip_DriveGoldLimit;
				case EShip_ROBOverLimit:
					return ProtocolMessageProt84.EShip_ROBOverLimit;
				case EShip_ROBOverShip:
					return ProtocolMessageProt84.EShip_ROBOverShip;
				case EShip_ROBDone:
					return ProtocolMessageProt84.EShip_ROBDone;
				case EShip_ROBSelf:
					return ProtocolMessageProt84.EShip_ROBSelf;
				case EShip_GRABErrOwer:
					return ProtocolMessageProt84.EShip_GRABErrOwer;
				case EShip_GRABErr:
					return ProtocolMessageProt84.EShip_GRABErr;
				case EShip_BattleCool:
					return ProtocolMessageProt84.EShip_BattleCool;
				case EShip_FinishOneKeyNoGold:
					return ProtocolMessageProt84.EShip_FinishOneKeyNoGold;
				case EShip_GetShipOneKeyNoGold:
					return ProtocolMessageProt84.EShip_GetShipOneKeyNoGold;
				case EShip_GetShipOneKeyNoVip:
					return ProtocolMessageProt84.EShip_GetShipOneKeyNoVip;
				case EShip_OtherErr:
					return ProtocolMessageProt84.EShip_OtherErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
