/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetLayerPrized.as
//  Purpose:      获取已领奖励层数
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTower
{
	/**
	 * 获取已领奖励层数的返回的参数组成的结构体
	 */
	public final class SRetParam_GetLayerPrized
	{
		public var vecFloorID:Vector.<uint>; //(无符号32位整数)已领奖励层数

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetLayerPrized _name_={name_}/>;
			else
				topXml = <SRetParam_GetLayerPrized/>;
			if(vecFloorID != null)
			{
				var vecFloorIDXml:XML = <Vec_UINT32 _name_="vecFloorID"/>;
				var text1:String = "";
				for each(var value1:uint in vecFloorID)
					text1 += "[" + value1 + "]";
				vecFloorIDXml.appendChild(text1);
				topXml.appendChild(vecFloorIDXml);
			}
			return topXml;
		}
	}
}
