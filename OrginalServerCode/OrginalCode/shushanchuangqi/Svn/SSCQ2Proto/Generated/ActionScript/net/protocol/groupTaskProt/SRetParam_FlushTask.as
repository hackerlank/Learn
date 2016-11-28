/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_FlushTask.as
//  Purpose:      刷新师门任务列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.groupTaskProt
{
	/**
	 * 刷新师门任务列表的返回的参数组成的结构体
	 */
	public final class SRetParam_FlushTask
	{
		public var eResult:uint; //(枚举类型：EGroupTaskResult)操作结果
		public var vecTask:Vector.<SGroupTask>; //推的任务列表
		public var byFlushTask:uint; //(无符号8位整数)今日刷新任务列表次数

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_FlushTask _name_={name_} eResult={eResult} byFlushTask={byFlushTask}/>;
			else
				topXml = <SRetParam_FlushTask eResult={eResult} byFlushTask={byFlushTask}/>;
			if(vecTask != null)
			{
				var vecTaskXml:XML = <Vec_SGroupTask _name_="vecTask"/>;
				for each(var s1:SGroupTask in vecTask)
					vecTaskXml.appendChild(s1.toXML());
				topXml.appendChild(vecTaskXml);
			}
			return topXml;
		}
	}
}
