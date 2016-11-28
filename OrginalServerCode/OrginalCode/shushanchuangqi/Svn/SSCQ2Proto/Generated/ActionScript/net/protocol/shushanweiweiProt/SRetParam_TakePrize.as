/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_TakePrize.as
//  Purpose:      获取礼包
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanweiweiProt
{
	/**
	 * 获取礼包的返回的参数组成的结构体
	 */
	public final class SRetParam_TakePrize
	{
		public var eRetType:uint; //(枚举类型：EPkgType)活动类型返回
		public var wRetIndex:uint; //(无符号16位整数)领奖类型返回：0表示个人奖励，1..16 表示领取全服第几个奖励
		public var eRet:uint; //(枚举类型：EPkgResult)操作结果返回

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_TakePrize _name_={name_} eRetType={eRetType} wRetIndex={wRetIndex} eRet={eRet}/>;
			else
				topXml = <SRetParam_TakePrize eRetType={eRetType} wRetIndex={wRetIndex} eRet={eRet}/>;
			return topXml;
		}
	}
}
