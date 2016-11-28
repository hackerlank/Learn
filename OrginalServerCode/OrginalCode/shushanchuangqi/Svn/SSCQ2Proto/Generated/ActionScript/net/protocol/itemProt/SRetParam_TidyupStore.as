/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_TidyupStore.as
//  Purpose:      整理包裹或仓库
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	/**
	 * 整理包裹或仓库的返回的参数组成的结构体
	 */
	public final class SRetParam_TidyupStore
	{
		public var eResult:uint; //(枚举类型：EItemResult)整理的结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_TidyupStore _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_TidyupStore eResult={eResult}/>;
			return topXml;
		}
	}
}
