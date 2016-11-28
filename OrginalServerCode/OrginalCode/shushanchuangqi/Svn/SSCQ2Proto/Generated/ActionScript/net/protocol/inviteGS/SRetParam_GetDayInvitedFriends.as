/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetDayInvitedFriends.as
//  Purpose:      每日邀请好友数量
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.inviteGS
{
	/**
	 * 每日邀请好友数量的返回的参数组成的结构体
	 */
	public final class SRetParam_GetDayInvitedFriends
	{
		public var dwInviteCnt:uint; //(无符号32位整数)邀请数量

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetDayInvitedFriends _name_={name_} dwInviteCnt={dwInviteCnt}/>;
			else
				topXml = <SRetParam_GetDayInvitedFriends dwInviteCnt={dwInviteCnt}/>;
			return topXml;
		}
	}
}
