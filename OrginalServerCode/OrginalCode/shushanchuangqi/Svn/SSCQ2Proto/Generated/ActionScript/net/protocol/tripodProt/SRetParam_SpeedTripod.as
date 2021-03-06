/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_SpeedTripod.as
//  Purpose:      加速九疑鼎炼丹(道具入鼎)
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.tripodProt
{
	/**
	 * 加速九疑鼎炼丹(道具入鼎)的返回的参数组成的结构体
	 */
	public final class SRetParam_SpeedTripod
	{
		public var vecTripods:Vector.<STripodInfo>; //九疑鼎信息列表
		public var eResult:uint; //(枚举类型：ETripodType)结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_SpeedTripod _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_SpeedTripod eResult={eResult}/>;
			if(vecTripods != null)
			{
				var vecTripodsXml:XML = <Vec_STripodInfo _name_="vecTripods"/>;
				for each(var s1:STripodInfo in vecTripods)
					vecTripodsXml.appendChild(s1.toXML());
				topXml.appendChild(vecTripodsXml);
			}
			return topXml;
		}
	}
}
