/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetStore.as
//  Purpose:      请求包裹信息(整个包裹)
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	/**
	 * 请求包裹信息(整个包裹)的返回的参数组成的结构体
	 */
	public final class SRetParam_GetStore
	{
		public var stStoreStream:SStoreStream; //背包信息
		public var dwNextUnlockTime:uint; //(无符号32位整数)下一个解锁背包空间的时间 0-表示可解锁 0xFFFFFFFF-表示没有可解锁的了 其他为秒

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetStore _name_={name_} dwNextUnlockTime={dwNextUnlockTime}/>;
			else
				topXml = <SRetParam_GetStore dwNextUnlockTime={dwNextUnlockTime}/>;
			if(stStoreStream != null)
				topXml.appendChild(stStoreStream.toXML("stStoreStream"));
			return topXml;
		}
	}
}
