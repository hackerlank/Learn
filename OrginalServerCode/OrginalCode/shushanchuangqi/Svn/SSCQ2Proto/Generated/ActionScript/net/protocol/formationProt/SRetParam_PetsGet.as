/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_PetsGet.as
//  Purpose:      取得所有阵灵信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.formationProt
{
	import net.protocol.roleInfoDefine.SPetDataInfo;

	/**
	 * 取得所有阵灵信息的返回的参数组成的结构体
	 */
	public final class SRetParam_PetsGet
	{
		public var vecPets:Vector.<SPetDataInfo>; //阵灵信息列表

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_PetsGet _name_={name_}/>;
			else
				topXml = <SRetParam_PetsGet/>;
			if(vecPets != null)
			{
				var vecPetsXml:XML = <Vec_SPetDataInfo _name_="vecPets"/>;
				for each(var s1:SPetDataInfo in vecPets)
					vecPetsXml.appendChild(s1.toXML());
				topXml.appendChild(vecPetsXml);
			}
			return topXml;
		}
	}
}
