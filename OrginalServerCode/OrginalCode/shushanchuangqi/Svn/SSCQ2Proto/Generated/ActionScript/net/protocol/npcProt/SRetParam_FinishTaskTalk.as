/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_FinishTaskTalk.as
//  Purpose:      完成一任务对话
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.npcProt
{
	/**
	 * 完成一任务对话的返回的参数组成的结构体
	 */
	public final class SRetParam_FinishTaskTalk
	{
		public var strContent:String; //对话内容

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_FinishTaskTalk _name_={name_} strContent={strContent}/>;
			else
				topXml = <SRetParam_FinishTaskTalk strContent={strContent}/>;
			return topXml;
		}
	}
}
