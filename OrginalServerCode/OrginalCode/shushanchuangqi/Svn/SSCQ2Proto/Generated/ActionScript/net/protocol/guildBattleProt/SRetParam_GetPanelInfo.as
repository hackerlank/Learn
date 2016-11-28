/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetPanelInfo.as
//  Purpose:      获取帮派战小面板信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	/**
	 * 获取帮派战小面板信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetPanelInfo
	{
		public var dwSelfScore:uint; //(无符号32位整数)我的积分
		public var dwGuildScore:uint; //(无符号32位整数)帮派积分
		public var dwGuildRank:uint; //(无符号32位整数)帮派排名

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetPanelInfo _name_={name_} dwSelfScore={dwSelfScore} dwGuildScore={dwGuildScore} dwGuildRank={dwGuildRank}/>;
			else
				topXml = <SRetParam_GetPanelInfo dwSelfScore={dwSelfScore} dwGuildScore={dwGuildScore} dwGuildRank={dwGuildRank}/>;
			return topXml;
		}
	}
}
