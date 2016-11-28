/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetTopPrizeLayer.as
//  Purpose:      获取最高已领奖层
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTower
{
	/**
	 * 获取最高已领奖层的返回的参数组成的结构体
	 */
	public final class SRetParam_GetTopPrizeLayer
	{
		public var dwFloorID:uint; //(无符号32位整数)层数

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetTopPrizeLayer _name_={name_} dwFloorID={dwFloorID}/>;
			else
				topXml = <SRetParam_GetTopPrizeLayer dwFloorID={dwFloorID}/>;
			return topXml;
		}
	}
}
