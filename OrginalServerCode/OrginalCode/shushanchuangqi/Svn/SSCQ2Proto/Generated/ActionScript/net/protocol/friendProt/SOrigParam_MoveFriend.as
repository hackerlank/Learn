/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SOrigParam_MoveFriend.as
//  Purpose:      移动好友
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.friendProt
{
	import com.hurlant.math.BigInteger;

	/**
	 * 移动好友的原来的参数组成的结构体
	 */
	public final class SOrigParam_MoveFriend
	{
		public var qwUserID:BigInteger; //(无符号64位整数)帐号ID
		public var eGroupType:uint; //(枚举类型：EFriendGroupType)分组ID
		public var callback:Function;

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SOrigParam_MoveFriend _name_={name_} qwUserID={qwUserID} eGroupType={eGroupType}/>;
			else
				topXml = <SOrigParam_MoveFriend qwUserID={qwUserID} eGroupType={eGroupType}/>;
			return topXml;
		}
	}
}
