/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GiveUpTask.as
//  Purpose:      放弃任务请求
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	/**
	 * 放弃任务请求的返回的参数组成的结构体
	 */
	public final class SRetParam_GiveUpTask
	{
		public var eResult:uint; //(枚举类型：ETaskResult)放弃任务的结果
		public var wTaskID:uint; //(无符号16位整数)任务ID

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GiveUpTask _name_={name_} eResult={eResult} wTaskID={wTaskID}/>;
			else
				topXml = <SRetParam_GiveUpTask eResult={eResult} wTaskID={wTaskID}/>;
			return topXml;
		}
	}
}
