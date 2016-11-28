/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_OnEnter.as
//  Purpose:      打开活动面板
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.godMonsterProt
{
	/**
	 * 打开活动面板的返回的参数组成的结构体
	 */
	public final class SRetParam_OnEnter
	{
		public var sInfo:SyncInfoToClient; //客户端数据

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_OnEnter _name_={name_}/>;
			else
				topXml = <SRetParam_OnEnter/>;
			if(sInfo != null)
				topXml.appendChild(sInfo.toXML("sInfo"));
			return topXml;
		}
	}
}
