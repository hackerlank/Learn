/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_CompareOtherBPByName.as
//  Purpose:      战斗力对比
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.compareBattlePoint
{
	/**
	 * 战斗力对比的返回的参数组成的结构体
	 */
	public final class SRetParam_CompareOtherBPByName
	{
		public var vecCompareData:Vector.<SCompareData>; //玩家的对比数据信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_CompareOtherBPByName _name_={name_}/>;
			else
				topXml = <SRetParam_CompareOtherBPByName/>;
			if(vecCompareData != null)
			{
				var vecCompareDataXml:XML = <Vec_SCompareData _name_="vecCompareData"/>;
				for each(var s1:SCompareData in vecCompareData)
					vecCompareDataXml.appendChild(s1.toXML());
				topXml.appendChild(vecCompareDataXml);
			}
			return topXml;
		}
	}
}
