/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetPkgInfo.as
//  Purpose:      登入礼包信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.loginPkgProt
{
	/**
	 * 登入礼包信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetPkgInfo
	{
		public var wDays:uint; //(无符号16位整数)连续登入的天数
		public var wResult:uint; //(无符号16位整数)操作结果:从地位向高位，1表示领取，0表示没有领

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetPkgInfo _name_={name_} wDays={wDays} wResult={wResult}/>;
			else
				topXml = <SRetParam_GetPkgInfo wDays={wDays} wResult={wResult}/>;
			return topXml;
		}
	}
}
