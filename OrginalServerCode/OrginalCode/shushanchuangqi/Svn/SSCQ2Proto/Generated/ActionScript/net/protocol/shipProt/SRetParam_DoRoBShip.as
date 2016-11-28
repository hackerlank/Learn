/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_DoRoBShip.as
//  Purpose:      打劫船只
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shipProt
{
	/**
	 * 打劫船只的返回的参数组成的结构体
	 */
	public final class SRetParam_DoRoBShip
	{
		public var eResult:uint; //(枚举类型：EShipResult)操作结果
		public var bySuc:uint; //(无符号8位整数)0,失败，1胜利

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_DoRoBShip _name_={name_} eResult={eResult} bySuc={bySuc}/>;
			else
				topXml = <SRetParam_DoRoBShip eResult={eResult} bySuc={bySuc}/>;
			return topXml;
		}
	}
}
