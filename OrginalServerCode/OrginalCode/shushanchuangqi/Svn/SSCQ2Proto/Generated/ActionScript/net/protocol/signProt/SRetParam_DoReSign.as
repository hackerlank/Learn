/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_DoReSign.as
//  Purpose:      请求补签
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.signProt
{
	/**
	 * 请求补签的返回的参数组成的结构体
	 */
	public final class SRetParam_DoReSign
	{
		public var eResult:uint; //(枚举类型：ESignResult)处理结果
		public var dwSignData:uint; //(无符号32位整数)按位计数，从右到左，一位表示1天，1表示该日已签到
		public var byReSignTimes:uint; //(无符号8位整数)该月补签天数

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_DoReSign _name_={name_} eResult={eResult} dwSignData={dwSignData} byReSignTimes={byReSignTimes}/>;
			else
				topXml = <SRetParam_DoReSign eResult={eResult} dwSignData={dwSignData} byReSignTimes={byReSignTimes}/>;
			return topXml;
		}
	}
}
