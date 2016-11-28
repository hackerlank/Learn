/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetSignInfo.as
//  Purpose:      请求签到信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.signProt
{
	/**
	 * 请求签到信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetSignInfo
	{
		public var dwSignData:uint; //(无符号32位整数)按位计数，从右到左，一位表示1天，1表示该日已签到
		public var byReSignTimes:uint; //(无符号8位整数)该月补签天数
		public var dwAward:uint; //(无符号32位整数)签到奖励包获取状态

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetSignInfo _name_={name_} dwSignData={dwSignData} byReSignTimes={byReSignTimes} dwAward={dwAward}/>;
			else
				topXml = <SRetParam_GetSignInfo dwSignData={dwSignData} byReSignTimes={byReSignTimes} dwAward={dwAward}/>;
			return topXml;
		}
	}
}
