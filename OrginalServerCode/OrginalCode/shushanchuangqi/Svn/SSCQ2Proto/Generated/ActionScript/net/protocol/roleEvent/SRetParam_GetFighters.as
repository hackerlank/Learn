/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetFighters.as
//  Purpose:      取得散仙列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEvent
{
	/**
	 * 取得散仙列表的返回的参数组成的结构体
	 */
	public final class SRetParam_GetFighters
	{
		public var vecFighters:Vector.<SFighterSpecInfo>; //散仙信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetFighters _name_={name_}/>;
			else
				topXml = <SRetParam_GetFighters/>;
			if(vecFighters != null)
			{
				var vecFightersXml:XML = <Vec_SFighterSpecInfo _name_="vecFighters"/>;
				for each(var s1:SFighterSpecInfo in vecFighters)
					vecFightersXml.appendChild(s1.toXML());
				topXml.appendChild(vecFightersXml);
			}
			return topXml;
		}
	}
}
