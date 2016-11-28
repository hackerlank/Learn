/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetPlayerAppear.as
//  Purpose:      获取玩家的外观信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	/**
	 * 获取玩家的外观信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetPlayerAppear
	{
		public var byRet:uint; //(无符号8位整数)0 成功 1失败
		public var rPlayerAppear:SPlayerAppear; //玩家的外观

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetPlayerAppear _name_={name_} byRet={byRet}/>;
			else
				topXml = <SRetParam_GetPlayerAppear byRet={byRet}/>;
			if(rPlayerAppear != null)
				topXml.appendChild(rPlayerAppear.toXML("rPlayerAppear"));
			return topXml;
		}
	}
}
