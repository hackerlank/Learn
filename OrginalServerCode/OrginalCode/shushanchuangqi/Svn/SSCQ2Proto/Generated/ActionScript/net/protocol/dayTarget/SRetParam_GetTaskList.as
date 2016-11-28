/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetTaskList.as
//  Purpose:      获取任务列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dayTarget
{
	/**
	 * 获取任务列表的返回的参数组成的结构体
	 */
	public final class SRetParam_GetTaskList
	{
		public var vecDayTargetTask:Vector.<SDayTargetTask>; //任务列表

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetTaskList _name_={name_}/>;
			else
				topXml = <SRetParam_GetTaskList/>;
			if(vecDayTargetTask != null)
			{
				var vecDayTargetTaskXml:XML = <Vec_SDayTargetTask _name_="vecDayTargetTask"/>;
				for each(var s1:SDayTargetTask in vecDayTargetTask)
					vecDayTargetTaskXml.appendChild(s1.toXML());
				topXml.appendChild(vecDayTargetTaskXml);
			}
			return topXml;
		}
	}
}
