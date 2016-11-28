/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SOrigParam_MergeStackItem.as
//  Purpose:      合并包裹或仓库中的堆叠类道具
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import com.hurlant.math.BigInteger;

	/**
	 * 合并包裹或仓库中的堆叠类道具的原来的参数组成的结构体
	 */
	public final class SOrigParam_MergeStackItem
	{
		public var eStoreType:uint; //(枚举类型：EStoreType)存储类型
		public var qwFromInstID:BigInteger; //(无符号64位整数)源道具的实例ID
		public var qwToInstID:BigInteger; //(无符号64位整数)目的道具的实例ID
		public var callback:Function;

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SOrigParam_MergeStackItem _name_={name_} eStoreType={eStoreType} qwFromInstID={qwFromInstID} qwToInstID={qwToInstID}/>;
			else
				topXml = <SOrigParam_MergeStackItem eStoreType={eStoreType} qwFromInstID={qwFromInstID} qwToInstID={qwToInstID}/>;
			return topXml;
		}
	}
}
