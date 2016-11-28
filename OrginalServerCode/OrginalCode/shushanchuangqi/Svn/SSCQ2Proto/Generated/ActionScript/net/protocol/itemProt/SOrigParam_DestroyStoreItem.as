/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SOrigParam_DestroyStoreItem.as
//  Purpose:      销毁包裹或仓库中的道具
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import com.hurlant.math.BigInteger;

	/**
	 * 销毁包裹或仓库中的道具的原来的参数组成的结构体
	 */
	public final class SOrigParam_DestroyStoreItem
	{
		public var eStoreType:uint; //(枚举类型：EStoreType)存储类型
		public var qwInstID:BigInteger; //(无符号64位整数)道具的实例ID
		public var callback:Function;

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SOrigParam_DestroyStoreItem _name_={name_} eStoreType={eStoreType} qwInstID={qwInstID}/>;
			else
				topXml = <SOrigParam_DestroyStoreItem eStoreType={eStoreType} qwInstID={qwInstID}/>;
			return topXml;
		}
	}
}
