/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_MergeEquipTrump.as
//  Purpose:      请求合成装备法宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.equipTrumpProt
{
	import net.protocol.itemProt.SItem;

	/**
	 * 请求合成装备法宝的返回的参数组成的结构体
	 */
	public final class SRetParam_MergeEquipTrump
	{
		public var eResult:uint; //(枚举类型：EEquipTrumpMergeResult)结果
		public var vecItem:Vector.<SItem>; //新增的道具

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_MergeEquipTrump _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_MergeEquipTrump eResult={eResult}/>;
			if(vecItem != null)
			{
				var vecItemXml:XML = <Vec_SItem _name_="vecItem"/>;
				for each(var s1:SItem in vecItem)
					vecItemXml.appendChild(s1.toXML());
				topXml.appendChild(vecItemXml);
			}
			return topXml;
		}
	}
}
