/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_FinishTask.as
//  Purpose:      完成任务请求(领取奖励)
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	/**
	 * 完成任务请求(领取奖励)的返回的参数组成的结构体
	 */
	public final class SRetParam_FinishTask
	{
		public var eResult:uint; //(枚举类型：ETaskResult)完成任务的结果
		public var byCost:uint; //(无符号8位整数)参数回传
		public var wTaskID:uint; //(无符号16位整数)任务ID

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_FinishTask _name_={name_} eResult={eResult} byCost={byCost} wTaskID={wTaskID}/>;
			else
				topXml = <SRetParam_FinishTask eResult={eResult} byCost={byCost} wTaskID={wTaskID}/>;
			return topXml;
		}
	}
}
