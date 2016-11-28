/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_Draw.as
//  Purpose:      求签
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import net.protocol.itemProt.SItemCount;

	/**
	 * 求签的返回的参数组成的结构体
	 */
	public final class SRetParam_Draw
	{
		public var eResult:uint; //(枚举类型：EDrawResult)返回结果
		public var vecItemGet:Vector.<SItemCount>; //求签获得物品

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_Draw _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_Draw eResult={eResult}/>;
			if(vecItemGet != null)
			{
				var vecItemGetXml:XML = <Vec_SItemCount _name_="vecItemGet"/>;
				for each(var s1:SItemCount in vecItemGet)
					vecItemGetXml.appendChild(s1.toXML());
				topXml.appendChild(vecItemGetXml);
			}
			return topXml;
		}
	}
}
