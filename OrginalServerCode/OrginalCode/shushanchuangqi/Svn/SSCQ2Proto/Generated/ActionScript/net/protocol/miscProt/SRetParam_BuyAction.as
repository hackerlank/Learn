/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_BuyAction.as
//  Purpose:      购买体力
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
{
	/**
	 * 购买体力的返回的参数组成的结构体
	 */
	public final class SRetParam_BuyAction
	{
		public var dwRet:uint; //(无符号32位整数)结果
		public var dwCount:uint; //(无符号32位整数)购买体力次数
		public var dwPrice:uint; //(无符号32位整数)购买体力价格

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_BuyAction _name_={name_} dwRet={dwRet} dwCount={dwCount} dwPrice={dwPrice}/>;
			else
				topXml = <SRetParam_BuyAction dwRet={dwRet} dwCount={dwCount} dwPrice={dwPrice}/>;
			return topXml;
		}
	}
}
