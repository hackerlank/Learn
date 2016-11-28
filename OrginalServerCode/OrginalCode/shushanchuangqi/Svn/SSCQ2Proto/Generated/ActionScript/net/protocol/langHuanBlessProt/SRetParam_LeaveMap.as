/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_LeaveMap.as
//  Purpose:      离开LangHuanBless地图
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.langHuanBlessProt
{
	/**
	 * 离开LangHuanBless地图的返回的参数组成的结构体
	 */
	public final class SRetParam_LeaveMap
	{
		public var eLHBResult:uint; //(枚举类型：ELHBResult)结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_LeaveMap _name_={name_} eLHBResult={eLHBResult}/>;
			else
				topXml = <SRetParam_LeaveMap eLHBResult={eLHBResult}/>;
			return topXml;
		}
	}
}
