/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetTripodStatus.as
//  Purpose:      请求玩家九疑鼎的能被扇火、协助信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.tripodProt
{
	/**
	 * 请求玩家九疑鼎的能被扇火、协助信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetTripodStatus
	{
		public var vecStatus:Vector.<STripodStatus>; //玩家九疑鼎的扇火、协助状态

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetTripodStatus _name_={name_}/>;
			else
				topXml = <SRetParam_GetTripodStatus/>;
			if(vecStatus != null)
			{
				var vecStatusXml:XML = <Vec_STripodStatus _name_="vecStatus"/>;
				for each(var s1:STripodStatus in vecStatus)
					vecStatusXml.appendChild(s1.toXML());
				topXml.appendChild(vecStatusXml);
			}
			return topXml;
		}
	}
}
