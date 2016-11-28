/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_FindReferFriendReq.as
//  Purpose:      获取推荐好友
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.friendProt
{
	/**
	 * 获取推荐好友的返回的参数组成的结构体
	 */
	public final class SRetParam_FindReferFriendReq
	{
		public var vecReferFriend:Vector.<SreferFriend>; //推荐好友

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_FindReferFriendReq _name_={name_}/>;
			else
				topXml = <SRetParam_FindReferFriendReq/>;
			if(vecReferFriend != null)
			{
				var vecReferFriendXml:XML = <Vec_SreferFriend _name_="vecReferFriend"/>;
				for each(var s1:SreferFriend in vecReferFriend)
					vecReferFriendXml.appendChild(s1.toXML());
				topXml.appendChild(vecReferFriendXml);
			}
			return topXml;
		}
	}
}
