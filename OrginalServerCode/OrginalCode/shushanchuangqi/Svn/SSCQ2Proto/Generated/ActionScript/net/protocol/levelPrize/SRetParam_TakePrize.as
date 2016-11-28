/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_TakePrize.as
//  Purpose:      获取奖励
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.levelPrize
{
	/**
	 * 获取奖励的返回的参数组成的结构体
	 */
	public final class SRetParam_TakePrize
	{
		public var wActID:uint; //(无符号16位整数)活动Id
		public var byIndex:uint; //(无符号8位整数)活动Id
		public var eRet:uint; //(枚举类型：ELevelActStatus)领取结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_TakePrize _name_={name_} wActID={wActID} byIndex={byIndex} eRet={eRet}/>;
			else
				topXml = <SRetParam_TakePrize wActID={wActID} byIndex={byIndex} eRet={eRet}/>;
			return topXml;
		}
	}
}
