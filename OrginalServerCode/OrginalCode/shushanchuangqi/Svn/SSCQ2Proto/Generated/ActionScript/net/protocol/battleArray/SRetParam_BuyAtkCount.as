/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_BuyAtkCount.as
//  Purpose:      购买攻击阵图次数
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleArray
{
	/**
	 * 购买攻击阵图次数的返回的参数组成的结构体
	 */
	public final class SRetParam_BuyAtkCount
	{
		public var eRet:uint; //(枚举类型：EBattleArrayRet)结果
		public var dwBuyCount:uint; //(无符号32位整数)已购买次数
		public var dwDayBuyCnt:uint; //(无符号32位整数)当天购买次数

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_BuyAtkCount _name_={name_} eRet={eRet} dwBuyCount={dwBuyCount} dwDayBuyCnt={dwDayBuyCnt}/>;
			else
				topXml = <SRetParam_BuyAtkCount eRet={eRet} dwBuyCount={dwBuyCount} dwDayBuyCnt={dwDayBuyCnt}/>;
			return topXml;
		}
	}
}
