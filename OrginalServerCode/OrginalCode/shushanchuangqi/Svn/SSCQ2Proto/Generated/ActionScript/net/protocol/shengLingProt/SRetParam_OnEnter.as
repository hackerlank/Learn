/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_OnEnter.as
//  Purpose:      玩家进入圣陵
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
{
	/**
	 * 玩家进入圣陵的返回的参数组成的结构体
	 */
	public final class SRetParam_OnEnter
	{
		public var byBuyEnterToday:uint; //(无符号8位整数)玩家今天购买进入次数
		public var sInfo:SShengLingInfo; //玩家数据
		public var eResult:uint; //(枚举类型：EShengLingResult)操作结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_OnEnter _name_={name_} byBuyEnterToday={byBuyEnterToday} eResult={eResult}/>;
			else
				topXml = <SRetParam_OnEnter byBuyEnterToday={byBuyEnterToday} eResult={eResult}/>;
			if(sInfo != null)
				topXml.appendChild(sInfo.toXML("sInfo"));
			return topXml;
		}
	}
}
