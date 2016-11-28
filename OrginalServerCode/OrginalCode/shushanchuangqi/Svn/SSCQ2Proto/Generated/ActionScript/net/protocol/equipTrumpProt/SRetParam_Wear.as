/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_Wear.as
//  Purpose:      请求穿上装备法宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.equipTrumpProt
{
	/**
	 * 请求穿上装备法宝的返回的参数组成的结构体
	 */
	public final class SRetParam_Wear
	{
		public var eResult:uint; //(枚举类型：EEquipTrumpResult)穿上装备法宝的结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_Wear _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_Wear eResult={eResult}/>;
			return topXml;
		}
	}
}
