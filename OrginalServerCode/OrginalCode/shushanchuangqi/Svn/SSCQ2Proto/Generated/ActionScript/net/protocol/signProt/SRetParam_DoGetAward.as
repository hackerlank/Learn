/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_DoGetAward.as
//  Purpose:      请求领取奖励
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.signProt
{
	/**
	 * 请求领取奖励的返回的参数组成的结构体
	 */
	public final class SRetParam_DoGetAward
	{
		public var eResult:uint; //(枚举类型：ESignResult)处理结果
		public var dwAward:uint; //(无符号32位整数)签到奖励包获取状态

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_DoGetAward _name_={name_} eResult={eResult} dwAward={dwAward}/>;
			else
				topXml = <SRetParam_DoGetAward eResult={eResult} dwAward={dwAward}/>;
			return topXml;
		}
	}
}
