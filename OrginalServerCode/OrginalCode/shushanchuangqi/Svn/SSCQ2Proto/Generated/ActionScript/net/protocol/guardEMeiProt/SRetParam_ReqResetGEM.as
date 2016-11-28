/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ReqResetGEM.as
//  Purpose:      请求重置关卡
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guardEMeiProt
{
	/**
	 * 请求重置关卡的返回的参数组成的结构体
	 */
	public final class SRetParam_ReqResetGEM
	{
		public var eGEMOptResult:int; //(枚举类型：EGEMOptResult)操作结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ReqResetGEM _name_={name_} eGEMOptResult={eGEMOptResult}/>;
			else
				topXml = <SRetParam_ReqResetGEM eGEMOptResult={eGEMOptResult}/>;
			return topXml;
		}
	}
}
