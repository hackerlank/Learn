/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetActInfo.as
//  Purpose:      获取活动信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	/**
	 * 获取活动信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetActInfo
	{
		public var eRet:uint; //(枚举类型：ELingShanOP)结果
		public var dwBeginTime:uint; //(无符号32位整数)比赛开启时间
		public var dwEndTime:uint; //(无符号32位整数)比赛结束时间

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetActInfo _name_={name_} eRet={eRet} dwBeginTime={dwBeginTime} dwEndTime={dwEndTime}/>;
			else
				topXml = <SRetParam_GetActInfo eRet={eRet} dwBeginTime={dwBeginTime} dwEndTime={dwEndTime}/>;
			return topXml;
		}
	}
}
