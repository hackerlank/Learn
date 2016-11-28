/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetDayPackAward.as
//  Purpose:      领取VIP特权每日礼包
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.vIPProt
{
	/**
	 * 领取VIP特权每日礼包的返回的参数组成的结构体
	 */
	public final class SRetParam_GetDayPackAward
	{
		public var eResult:uint; //(枚举类型：EVIPResult)操作结果
		public var dwDayPack:uint; //(无符号32位整数)VIP特权每日礼包领取状态(低15位,按位取)

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetDayPackAward _name_={name_} eResult={eResult} dwDayPack={dwDayPack}/>;
			else
				topXml = <SRetParam_GetDayPackAward eResult={eResult} dwDayPack={dwDayPack}/>;
			return topXml;
		}
	}
}
