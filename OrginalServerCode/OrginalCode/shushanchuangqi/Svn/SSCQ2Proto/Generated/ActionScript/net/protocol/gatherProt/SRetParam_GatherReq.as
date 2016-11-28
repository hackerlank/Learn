/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GatherReq.as
//  Purpose:      采集请求
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.gatherProt
{
	/**
	 * 采集请求的返回的参数组成的结构体
	 */
	public final class SRetParam_GatherReq
	{
		public var eResult:uint; //(枚举类型：EGatherResult)采集结果
		public var dwGatherTimer:uint; //(无符号32位整数)采集剩余时间

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GatherReq _name_={name_} eResult={eResult} dwGatherTimer={dwGatherTimer}/>;
			else
				topXml = <SRetParam_GatherReq eResult={eResult} dwGatherTimer={dwGatherTimer}/>;
			return topXml;
		}
	}
}
