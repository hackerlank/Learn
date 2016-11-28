/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_Buy.as
//  Purpose:      购买
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
{
	/**
	 * 购买的返回的参数组成的结构体
	 */
	public final class SRetParam_Buy
	{
		public var eBuyTypeRet:uint; //(枚举类型：EBuyType)返回购买类型
		public var byBuy:uint; //(无符号8位整数)返回购买次数
		public var byBuyToday:uint; //(无符号8位整数)返回今日购买次数
		public var byUse:uint; //(无符号8位整数)返回当日使用次数
		public var eResult:uint; //(枚举类型：EShengLingResult)操作结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_Buy _name_={name_} eBuyTypeRet={eBuyTypeRet} byBuy={byBuy} byBuyToday={byBuyToday} byUse={byUse} eResult={eResult}/>;
			else
				topXml = <SRetParam_Buy eBuyTypeRet={eBuyTypeRet} byBuy={byBuy} byBuyToday={byBuyToday} byUse={byUse} eResult={eResult}/>;
			return topXml;
		}
	}
}
