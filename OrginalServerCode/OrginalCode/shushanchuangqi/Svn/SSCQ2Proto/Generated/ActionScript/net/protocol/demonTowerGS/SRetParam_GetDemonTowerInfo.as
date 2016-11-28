/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetDemonTowerInfo.as
//  Purpose:      获取本人镇妖塔相关信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	/**
	 * 获取本人镇妖塔相关信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetDemonTowerInfo
	{
		public var dwRet:uint; //(无符号32位整数)结果 0成功 1-失败（非错误，没有进过镇妖塔）
		public var oDemonTowerPlayer:SDemonTowerPlayer; //玩家镇守信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetDemonTowerInfo _name_={name_} dwRet={dwRet}/>;
			else
				topXml = <SRetParam_GetDemonTowerInfo dwRet={dwRet}/>;
			if(oDemonTowerPlayer != null)
				topXml.appendChild(oDemonTowerPlayer.toXML("oDemonTowerPlayer"));
			return topXml;
		}
	}
}
