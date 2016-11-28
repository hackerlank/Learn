/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetDgnStarAwardInfo.as
//  Purpose:      查询副本星级领奖状态
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	/**
	 * 查询副本星级领奖状态的返回的参数组成的结构体
	 */
	public final class SRetParam_GetDgnStarAwardInfo
	{
		public var vecAward:Vector.<uint>; //(无符号16位整数)副本星级已领奖ID

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetDgnStarAwardInfo _name_={name_}/>;
			else
				topXml = <SRetParam_GetDgnStarAwardInfo/>;
			if(vecAward != null)
			{
				var vecAwardXml:XML = <Vec_UINT16 _name_="vecAward"/>;
				var text1:String = "";
				for each(var value1:uint in vecAward)
					text1 += "[" + value1 + "]";
				vecAwardXml.appendChild(text1);
				topXml.appendChild(vecAwardXml);
			}
			return topXml;
		}
	}
}
