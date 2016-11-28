/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetBeatyInfo.as
//  Purpose:      获取美女信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.beauty
{
	/**
	 * 获取美女信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetBeatyInfo
	{
		public var vecBeauty:Vector.<SBeauty>; //美女信息列表
		public var dwLoveCnt:uint; //(无符号32位整数)爱心个数
		public var dwNextChatTime:uint; //(无符号32位整数)下次聊天冷却时间
		public var dwNextGoldLotteryTime:uint; //(无符号32位整数)下次免费金币抽奖冷却时间
		public var dwNextSilverLotterTime:uint; //(无符号32位整数)下次免费银币冷却时间
		public var wBeautyID:uint; //(无符号16位整数)出战美女ID

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetBeatyInfo _name_={name_} dwLoveCnt={dwLoveCnt} dwNextChatTime={dwNextChatTime} dwNextGoldLotteryTime={dwNextGoldLotteryTime} dwNextSilverLotterTime={dwNextSilverLotterTime}
				 wBeautyID={wBeautyID}/>;
			else
				topXml = <SRetParam_GetBeatyInfo dwLoveCnt={dwLoveCnt} dwNextChatTime={dwNextChatTime} dwNextGoldLotteryTime={dwNextGoldLotteryTime} dwNextSilverLotterTime={dwNextSilverLotterTime}
				 wBeautyID={wBeautyID}/>;
			if(vecBeauty != null)
			{
				var vecBeautyXml:XML = <Vec_SBeauty _name_="vecBeauty"/>;
				for each(var s1:SBeauty in vecBeauty)
					vecBeautyXml.appendChild(s1.toXML());
				topXml.appendChild(vecBeautyXml);
			}
			return topXml;
		}
	}
}
