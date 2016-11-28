/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetInvitedFriendList.as
//  Purpose:      获取被邀请好友列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.inviteGS
{
	/**
	 * 获取被邀请好友列表的返回的参数组成的结构体
	 */
	public final class SRetParam_GetInvitedFriendList
	{
		public var vecInvitedFriend:Vector.<SInvitedFriend>; //被邀请好友列表

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetInvitedFriendList _name_={name_}/>;
			else
				topXml = <SRetParam_GetInvitedFriendList/>;
			if(vecInvitedFriend != null)
			{
				var vecInvitedFriendXml:XML = <Vec_SInvitedFriend _name_="vecInvitedFriend"/>;
				for each(var s1:SInvitedFriend in vecInvitedFriend)
					vecInvitedFriendXml.appendChild(s1.toXML());
				topXml.appendChild(vecInvitedFriendXml);
			}
			return topXml;
		}
	}
}
