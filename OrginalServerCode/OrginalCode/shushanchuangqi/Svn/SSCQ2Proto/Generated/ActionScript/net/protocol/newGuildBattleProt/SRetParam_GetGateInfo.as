/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetGateInfo.as
//  Purpose:      获取城门战信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	/**
	 * 获取城门战信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetGateInfo
	{
		public var eResult:uint; //(枚举类型：ENGBResult)返回结果
		public var sInfo:SMountainGateInfo; //城门信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetGateInfo _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_GetGateInfo eResult={eResult}/>;
			if(sInfo != null)
				topXml.appendChild(sInfo.toXML("sInfo"));
			return topXml;
		}
	}
}
