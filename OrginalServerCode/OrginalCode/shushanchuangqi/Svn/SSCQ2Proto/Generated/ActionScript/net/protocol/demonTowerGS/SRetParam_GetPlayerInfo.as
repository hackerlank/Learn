/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetPlayerInfo.as
//  Purpose:      获取玩家镇守信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	/**
	 * 获取玩家镇守信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetPlayerInfo
	{
		public var bRet:uint; //(无符号8位整数)0 成功 1玩家不存在
		public var oDemonFloorPlayer:SDemonFloorPlayer; //玩家镇守信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetPlayerInfo _name_={name_} bRet={bRet}/>;
			else
				topXml = <SRetParam_GetPlayerInfo bRet={bRet}/>;
			if(oDemonFloorPlayer != null)
				topXml.appendChild(oDemonFloorPlayer.toXML("oDemonFloorPlayer"));
			return topXml;
		}
	}
}
