/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetTargetInfoByDayID.as
//  Purpose:      通过dwDayID获取目标信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.registerSevenDaysProt
{
	import com.hurlant.math.BigInteger;

	/**
	 * 通过dwDayID获取目标信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetTargetInfoByDayID
	{
		public var qwTargetInfo:BigInteger; //(无符号64位整数)目标信息(注：每2位代表一个目标奖励的状态0：不能领取；1：能够领取；2：已领取)

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetTargetInfoByDayID _name_={name_} qwTargetInfo={qwTargetInfo}/>;
			else
				topXml = <SRetParam_GetTargetInfoByDayID qwTargetInfo={qwTargetInfo}/>;
			return topXml;
		}
	}
}
