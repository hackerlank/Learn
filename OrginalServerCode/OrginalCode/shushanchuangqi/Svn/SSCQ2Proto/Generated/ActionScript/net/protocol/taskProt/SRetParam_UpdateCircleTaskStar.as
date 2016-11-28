/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_UpdateCircleTaskStar.as
//  Purpose:      提升环任务星级
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	/**
	 * 提升环任务星级的返回的参数组成的结构体
	 */
	public final class SRetParam_UpdateCircleTaskStar
	{
		public var eResult:uint; //(枚举类型：ETaskResult)完成任务的结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_UpdateCircleTaskStar _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_UpdateCircleTaskStar eResult={eResult}/>;
			return topXml;
		}
	}
}
