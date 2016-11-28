/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetBeautyLog.as
//  Purpose:      获取美女log信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.beautyLogGS
{
	/**
	 * 获取美女log信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetBeautyLog
	{
		public var vecBeautyLog:Vector.<SBeautyLog>; //美女log信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetBeautyLog _name_={name_}/>;
			else
				topXml = <SRetParam_GetBeautyLog/>;
			if(vecBeautyLog != null)
			{
				var vecBeautyLogXml:XML = <Vec_SBeautyLog _name_="vecBeautyLog"/>;
				for each(var s1:SBeautyLog in vecBeautyLog)
					vecBeautyLogXml.appendChild(s1.toXML());
				topXml.appendChild(vecBeautyLogXml);
			}
			return topXml;
		}
	}
}
