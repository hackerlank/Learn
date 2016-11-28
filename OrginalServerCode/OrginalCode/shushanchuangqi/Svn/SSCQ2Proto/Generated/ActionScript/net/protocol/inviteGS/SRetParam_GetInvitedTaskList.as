/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetInvitedTaskList.as
//  Purpose:      邀请任务列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.inviteGS
{
	/**
	 * 邀请任务列表的返回的参数组成的结构体
	 */
	public final class SRetParam_GetInvitedTaskList
	{
		public var vecInvitedTask:Vector.<SInvitedTask>; //邀请任务状态信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetInvitedTaskList _name_={name_}/>;
			else
				topXml = <SRetParam_GetInvitedTaskList/>;
			if(vecInvitedTask != null)
			{
				var vecInvitedTaskXml:XML = <Vec_SInvitedTask _name_="vecInvitedTask"/>;
				for each(var s1:SInvitedTask in vecInvitedTask)
					vecInvitedTaskXml.appendChild(s1.toXML());
				topXml.appendChild(vecInvitedTaskXml);
			}
			return topXml;
		}
	}
}
