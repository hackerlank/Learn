/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SOrigParam_UseItem.as
//  Purpose:      请求使用包裹中的道具
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import com.hurlant.math.BigInteger;

	/**
	 * 请求使用包裹中的道具的原来的参数组成的结构体
	 */
	public final class SOrigParam_UseItem
	{
		public var eStoreType:uint; //(枚举类型：EStoreType)存储类型
		public var qwRoleID:BigInteger; //(无符号64位整数)针对的角色ID
		public var qwMercenID:BigInteger; //(无符号64位整数)针对的佣兵ID
		public var qwInstID:BigInteger; //(无符号64位整数)优先使用的物品实例ID
		public var wStack:uint; //(无符号16位整数)使用个数(只针对堆叠道具)
		public var callback:Function;

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SOrigParam_UseItem _name_={name_} eStoreType={eStoreType} qwRoleID={qwRoleID} qwMercenID={qwMercenID} qwInstID={qwInstID} wStack={wStack}/>;
			else
				topXml = <SOrigParam_UseItem eStoreType={eStoreType} qwRoleID={qwRoleID} qwMercenID={qwMercenID} qwInstID={qwInstID} wStack={wStack}/>;
			return topXml;
		}
	}
}
