/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetAllFires.as
//  Purpose:      取得玩家所有九疑鼎的火种信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.tripodProt
{
	/**
	 * 取得玩家所有九疑鼎的火种信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetAllFires
	{
		public var vecFires:Vector.<SFireInfo>; //九疑鼎信息列表

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetAllFires _name_={name_}/>;
			else
				topXml = <SRetParam_GetAllFires/>;
			if(vecFires != null)
			{
				var vecFiresXml:XML = <Vec_SFireInfo _name_="vecFires"/>;
				for each(var s1:SFireInfo in vecFires)
					vecFiresXml.appendChild(s1.toXML());
				topXml.appendChild(vecFiresXml);
			}
			return topXml;
		}
	}
}
