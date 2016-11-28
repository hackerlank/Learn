/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_SetHorseStatus.as
//  Purpose:      骑乘状态修改
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.horse
{
	/**
	 * 骑乘状态修改的返回的参数组成的结构体
	 */
	public final class SRetParam_SetHorseStatus
	{
		public var bRet:Boolean; //结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_SetHorseStatus _name_={name_} bRet={bRet}/>;
			else
				topXml = <SRetParam_SetHorseStatus bRet={bRet}/>;
			return topXml;
		}
	}
}
