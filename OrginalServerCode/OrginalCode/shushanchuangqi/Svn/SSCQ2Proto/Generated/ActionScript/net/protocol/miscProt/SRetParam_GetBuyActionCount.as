/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetBuyActionCount.as
//  Purpose:      获取购买体力次数
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
{
	/**
	 * 获取购买体力次数的返回的参数组成的结构体
	 */
	public final class SRetParam_GetBuyActionCount
	{
		public var dwCount:uint; //(无符号32位整数)购买体力次数
		public var dwPrice:uint; //(无符号32位整数)购买体力价格
		public var dwAction:uint; //(无符号32位整数)体力

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetBuyActionCount _name_={name_} dwCount={dwCount} dwPrice={dwPrice} dwAction={dwAction}/>;
			else
				topXml = <SRetParam_GetBuyActionCount dwCount={dwCount} dwPrice={dwPrice} dwAction={dwAction}/>;
			return topXml;
		}
	}
}
