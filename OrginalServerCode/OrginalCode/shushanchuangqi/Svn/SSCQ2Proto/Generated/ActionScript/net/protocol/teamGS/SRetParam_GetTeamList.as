/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetTeamList.as
//  Purpose:      根据模板查询可加入房间
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
{
	/**
	 * 根据模板查询可加入房间的返回的参数组成的结构体
	 */
	public final class SRetParam_GetTeamList
	{
		public var vecReturn:Vector.<TeamInfoForList>; //返回的房间列表

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetTeamList _name_={name_}/>;
			else
				topXml = <SRetParam_GetTeamList/>;
			if(vecReturn != null)
			{
				var vecReturnXml:XML = <Vec_TeamInfoForList _name_="vecReturn"/>;
				for each(var s1:TeamInfoForList in vecReturn)
					vecReturnXml.appendChild(s1.toXML());
				topXml.appendChild(vecReturnXml);
			}
			return topXml;
		}
	}
}
