/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetShowInfo.as
//  Purpose:      获取炫耀信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.globalChatProt
{
	import flash.utils.ByteArray;
	import net.util.BytesUtil;

	/**
	 * 获取炫耀信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetShowInfo
	{
		public var rSenderInfo:SSenderInfo; //发送者信息
		public var strShowInfo:ByteArray; //展示信息序列化

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetShowInfo _name_={name_} strShowInfo={BytesUtil.bytes2String(strShowInfo)}/>;
			else
				topXml = <SRetParam_GetShowInfo strShowInfo={BytesUtil.bytes2String(strShowInfo)}/>;
			if(rSenderInfo != null)
				topXml.appendChild(rSenderInfo.toXML("rSenderInfo"));
			return topXml;
		}
	}
}
