/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ReqUseBuff.as
//  Purpose:      请求使用Buff
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.treasureHuntProt
{
	/**
	 * 请求使用Buff的返回的参数组成的结构体
	 */
	public final class SRetParam_ReqUseBuff
	{
		public var eTHOptResult:int; //(枚举类型：ETHOptResult)操作结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ReqUseBuff _name_={name_} eTHOptResult={eTHOptResult}/>;
			else
				topXml = <SRetParam_ReqUseBuff eTHOptResult={eTHOptResult}/>;
			return topXml;
		}
	}
}
