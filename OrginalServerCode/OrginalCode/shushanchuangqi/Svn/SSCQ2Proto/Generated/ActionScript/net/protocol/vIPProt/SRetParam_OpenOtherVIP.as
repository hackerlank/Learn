/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_OpenOtherVIP.as
//  Purpose:      请求开启好友VIP特权
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.vIPProt
{
	import com.hurlant.math.BigInteger;

	/**
	 * 请求开启好友VIP特权的返回的参数组成的结构体
	 */
	public final class SRetParam_OpenOtherVIP
	{
		public var eResult:uint; //(枚举类型：EVIPResult)操作结果
		public var qwRoleID:BigInteger; //(无符号64位整数)好友玩家ID

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_OpenOtherVIP _name_={name_} eResult={eResult} qwRoleID={qwRoleID}/>;
			else
				topXml = <SRetParam_OpenOtherVIP eResult={eResult} qwRoleID={qwRoleID}/>;
			return topXml;
		}
	}
}
