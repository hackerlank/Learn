/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetPrizeInfo.as
//  Purpose:      获取奖励
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.levelPrize
{
	/**
	 * 获取奖励的返回的参数组成的结构体
	 */
	public final class SRetParam_GetPrizeInfo
	{
		public var wActID:uint; //(无符号16位整数)活动ID
		public var vecPrize:Vector.<SPrize>; //结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetPrizeInfo _name_={name_} wActID={wActID}/>;
			else
				topXml = <SRetParam_GetPrizeInfo wActID={wActID}/>;
			if(vecPrize != null)
			{
				var vecPrizeXml:XML = <Vec_SPrize _name_="vecPrize"/>;
				for each(var s1:SPrize in vecPrize)
					vecPrizeXml.appendChild(s1.toXML());
				topXml.appendChild(vecPrizeXml);
			}
			return topXml;
		}
	}
}
