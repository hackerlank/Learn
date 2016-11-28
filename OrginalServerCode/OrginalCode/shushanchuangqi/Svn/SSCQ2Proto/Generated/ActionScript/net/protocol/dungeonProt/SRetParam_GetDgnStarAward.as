/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetDgnStarAward.as
//  Purpose:      领取副本星级奖励
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	/**
	 * 领取副本星级奖励的返回的参数组成的结构体
	 */
	public final class SRetParam_GetDgnStarAward
	{
		public var eResult:uint; //(枚举类型：EDungeonResult)服务器返回结果
		public var vecAward:Vector.<uint>; //(无符号16位整数)副本星级已领奖ID

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetDgnStarAward _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_GetDgnStarAward eResult={eResult}/>;
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
