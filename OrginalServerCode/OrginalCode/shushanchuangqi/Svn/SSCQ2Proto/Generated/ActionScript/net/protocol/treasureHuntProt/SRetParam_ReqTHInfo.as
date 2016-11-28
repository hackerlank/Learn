/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ReqTHInfo.as
//  Purpose:      请求寻宝信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.treasureHuntProt
{
	/**
	 * 请求寻宝信息的返回的参数组成的结构体
	 */
	public final class SRetParam_ReqTHInfo
	{
		public var byCopyID:uint; //(无符号8位整数)0:没有副本进行中；非0:正在进行该副本
		public var eTHStatus:int; //(枚举类型：ETHStatus)寻宝状态
		public var byKillNum:uint; //(无符号8位整数)剩余击杀次数
		public var byCurrentID:uint; //(无符号8位整数)当前通关到副本ID

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ReqTHInfo _name_={name_} byCopyID={byCopyID} eTHStatus={eTHStatus} byKillNum={byKillNum} byCurrentID={byCurrentID}/>;
			else
				topXml = <SRetParam_ReqTHInfo byCopyID={byCopyID} eTHStatus={eTHStatus} byKillNum={byKillNum} byCurrentID={byCurrentID}/>;
			return topXml;
		}
	}
}
