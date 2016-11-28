/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetRoomList.as
//  Purpose:      获取房间信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	/**
	 * 获取房间信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetRoomList
	{
		public var eRet:uint; //(枚举类型：ELingShanOP)结果
		public var vecRoomInfo:Vector.<SRoomInfo>; //房间信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetRoomList _name_={name_} eRet={eRet}/>;
			else
				topXml = <SRetParam_GetRoomList eRet={eRet}/>;
			if(vecRoomInfo != null)
			{
				var vecRoomInfoXml:XML = <Vec_SRoomInfo _name_="vecRoomInfo"/>;
				for each(var s1:SRoomInfo in vecRoomInfo)
					vecRoomInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecRoomInfoXml);
			}
			return topXml;
		}
	}
}
