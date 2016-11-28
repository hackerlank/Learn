/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetLoginPkg.as
//  Purpose:      获取礼包
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.loginPkgProt
{
	/**
	 * 获取礼包的返回的参数组成的结构体
	 */
	public final class SRetParam_GetLoginPkg
	{
		public var wResult:uint; //(无符号16位整数)操作结果:从地位向高位，1表示领取，0表示没有领
		public var eResult:uint; //(枚举类型：EResultInLoginProt)操作结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetLoginPkg _name_={name_} wResult={wResult} eResult={eResult}/>;
			else
				topXml = <SRetParam_GetLoginPkg wResult={wResult} eResult={eResult}/>;
			return topXml;
		}
	}
}
