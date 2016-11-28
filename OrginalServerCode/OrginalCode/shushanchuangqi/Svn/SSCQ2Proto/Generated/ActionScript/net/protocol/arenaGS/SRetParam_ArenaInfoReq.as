/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ArenaInfoReq.as
//  Purpose:      请求自己竞技场信息,同时开启竞技场
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	/**
	 * 请求自己竞技场信息,同时开启竞技场的返回的参数组成的结构体
	 */
	public final class SRetParam_ArenaInfoReq
	{
		public var eResult:uint; //(枚举类型：EArenaResult)结果提示
		public var stReturn:SArenaPlayerBaseData2Client; //返回的自己信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ArenaInfoReq _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_ArenaInfoReq eResult={eResult}/>;
			if(stReturn != null)
				topXml.appendChild(stReturn.toXML("stReturn"));
			return topXml;
		}
	}
}
