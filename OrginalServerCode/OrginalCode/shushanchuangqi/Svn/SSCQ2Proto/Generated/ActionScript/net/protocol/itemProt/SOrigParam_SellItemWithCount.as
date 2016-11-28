/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SOrigParam_SellItemWithCount.as
//  Purpose:      请求按个数出售包裹中的道具-出售给系统
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import com.hurlant.math.BigInteger;

	/**
	 * 请求按个数出售包裹中的道具-出售给系统的原来的参数组成的结构体
	 */
	public final class SOrigParam_SellItemWithCount
	{
		public var eStoreType:uint; //(枚举类型：EStoreType)存储类型
		public var qwInstID:BigInteger; //(无符号64位整数)优先卖出的物品实例ID
		public var wStack:uint; //(无符号16位整数)卖出个数
		public var callback:Function;

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SOrigParam_SellItemWithCount _name_={name_} eStoreType={eStoreType} qwInstID={qwInstID} wStack={wStack}/>;
			else
				topXml = <SOrigParam_SellItemWithCount eStoreType={eStoreType} qwInstID={qwInstID} wStack={wStack}/>;
			return topXml;
		}
	}
}
