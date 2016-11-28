/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetActList.as
//  Purpose:      获得活动列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	/**
	 * 获得活动列表的返回的参数组成的结构体
	 */
	public final class SRetParam_GetActList
	{
		public var vecTimes:Vector.<STime>; //奖励信息
		public var eRet:uint; //(枚举类型：EWActResult)操作结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetActList _name_={name_} eRet={eRet}/>;
			else
				topXml = <SRetParam_GetActList eRet={eRet}/>;
			if(vecTimes != null)
			{
				var vecTimesXml:XML = <Vec_STime _name_="vecTimes"/>;
				for each(var s1:STime in vecTimes)
					vecTimesXml.appendChild(s1.toXML());
				topXml.appendChild(vecTimesXml);
			}
			return topXml;
		}
	}
}
