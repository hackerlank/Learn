/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ArenaWorship.as
//  Purpose:      膜拜请求
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	/**
	 * 膜拜请求的返回的参数组成的结构体
	 */
	public final class SRetParam_ArenaWorship
	{
		public var eResult:uint; //(枚举类型：EArenaResult)膜拜请求返回

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ArenaWorship _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_ArenaWorship eResult={eResult}/>;
			return topXml;
		}
	}
}
