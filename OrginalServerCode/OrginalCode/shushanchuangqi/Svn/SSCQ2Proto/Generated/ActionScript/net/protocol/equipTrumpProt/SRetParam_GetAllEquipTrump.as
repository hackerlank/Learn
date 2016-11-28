/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetAllEquipTrump.as
//  Purpose:      获得所有装备法宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.equipTrumpProt
{
	import net.protocol.itemProt.SEquipTrump;

	/**
	 * 获得所有装备法宝的返回的参数组成的结构体
	 */
	public final class SRetParam_GetAllEquipTrump
	{
		public var vecEquipTrump:Vector.<SEquipTrump>; //当前装备法宝的列表

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetAllEquipTrump _name_={name_}/>;
			else
				topXml = <SRetParam_GetAllEquipTrump/>;
			if(vecEquipTrump != null)
			{
				var vecEquipTrumpXml:XML = <Vec_SEquipTrump _name_="vecEquipTrump"/>;
				for each(var s1:SEquipTrump in vecEquipTrump)
					vecEquipTrumpXml.appendChild(s1.toXML());
				topXml.appendChild(vecEquipTrumpXml);
			}
			return topXml;
		}
	}
}
