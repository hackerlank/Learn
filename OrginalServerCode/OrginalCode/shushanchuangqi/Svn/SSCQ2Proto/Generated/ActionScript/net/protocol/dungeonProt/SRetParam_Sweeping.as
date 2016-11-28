/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_Sweeping.as
//  Purpose:      扫荡
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	/**
	 * 扫荡的返回的参数组成的结构体
	 */
	public final class SRetParam_Sweeping
	{
		public var eResult:uint; //(枚举类型：EDungeonResult)扫荡结果
		public var dwSweepEndTime:uint; //(无符号32位整数)扫荡结束时间

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_Sweeping _name_={name_} eResult={eResult} dwSweepEndTime={dwSweepEndTime}/>;
			else
				topXml = <SRetParam_Sweeping eResult={eResult} dwSweepEndTime={dwSweepEndTime}/>;
			return topXml;
		}
	}
}
