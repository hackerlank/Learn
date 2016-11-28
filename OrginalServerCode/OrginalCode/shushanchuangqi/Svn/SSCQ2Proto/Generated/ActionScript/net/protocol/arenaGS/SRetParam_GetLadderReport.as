/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetLadderReport.as
//  Purpose:      清求战报
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	/**
	 * 清求战报的返回的参数组成的结构体
	 */
	public final class SRetParam_GetLadderReport
	{
		public var eResult:uint; //(枚举类型：EArenaResult)请求刷将返回
		public var vecReport:Vector.<SLadderReport>; //请求刷将返回

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetLadderReport _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_GetLadderReport eResult={eResult}/>;
			if(vecReport != null)
			{
				var vecReportXml:XML = <Vec_SLadderReport _name_="vecReport"/>;
				for each(var s1:SLadderReport in vecReport)
					vecReportXml.appendChild(s1.toXML());
				topXml.appendChild(vecReportXml);
			}
			return topXml;
		}
	}
}
