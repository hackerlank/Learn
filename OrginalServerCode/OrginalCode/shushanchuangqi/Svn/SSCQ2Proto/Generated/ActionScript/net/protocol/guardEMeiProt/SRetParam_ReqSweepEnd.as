/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ReqSweepEnd.as
//  Purpose:      请求获取守卫峨眉扫荡结束(放弃扫荡)
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guardEMeiProt
{
	/**
	 * 请求获取守卫峨眉扫荡结束(放弃扫荡)的返回的参数组成的结构体
	 */
	public final class SRetParam_ReqSweepEnd
	{
		public var wCurProgress:uint; //(无符号16位整数)当前进度

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ReqSweepEnd _name_={name_} wCurProgress={wCurProgress}/>;
			else
				topXml = <SRetParam_ReqSweepEnd wCurProgress={wCurProgress}/>;
			return topXml;
		}
	}
}
