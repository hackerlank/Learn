/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_EnterTeam.as
//  Purpose:      请求加入房间
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
{
	/**
	 * 请求加入房间的返回的参数组成的结构体
	 */
	public final class SRetParam_EnterTeam
	{
		public var dwTeamID:uint; //(无符号32位整数)房间ID
		public var eResult:uint; //(枚举类型：ETEAMResult)请求加入房间

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_EnterTeam _name_={name_} dwTeamID={dwTeamID} eResult={eResult}/>;
			else
				topXml = <SRetParam_EnterTeam dwTeamID={dwTeamID} eResult={eResult}/>;
			return topXml;
		}
	}
}
