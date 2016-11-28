/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_OnOpen.as
//  Purpose:      玩家打开活动面板
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
{
	/**
	 * 玩家打开活动面板的返回的参数组成的结构体
	 */
	public final class SRetParam_OnOpen
	{
		public var byUseEnter:uint; //(无符号8位整数)玩家当日使用进入次数
		public var byBuyEnter:uint; //(无符号8位整数)玩家购买进入次数
		public var byBuyEnterToday:uint; //(无符号8位整数)玩家今天购买进入次数
		public var bContinue:Boolean; //是否继续

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_OnOpen _name_={name_} byUseEnter={byUseEnter} byBuyEnter={byBuyEnter} byBuyEnterToday={byBuyEnterToday} bContinue={bContinue}/>;
			else
				topXml = <SRetParam_OnOpen byUseEnter={byUseEnter} byBuyEnter={byBuyEnter} byBuyEnterToday={byBuyEnterToday} bContinue={bContinue}/>;
			return topXml;
		}
	}
}
