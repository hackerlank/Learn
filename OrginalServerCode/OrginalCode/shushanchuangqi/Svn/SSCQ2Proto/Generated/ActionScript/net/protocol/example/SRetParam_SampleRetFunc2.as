/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_SampleRetFunc2.as
//  Purpose:      C->S有返回值的示例函数
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.example
{
	/**
	 * C->S有返回值的示例函数的返回的参数组成的结构体
	 */
	public final class SRetParam_SampleRetFunc2
	{
		public var vecExDescend:Vector.<SExDescend3>; //结构体列表，返回值
		public var strRet:String; //字符串，返回值

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_SampleRetFunc2 _name_={name_} strRet={strRet}/>;
			else
				topXml = <SRetParam_SampleRetFunc2 strRet={strRet}/>;
			if(vecExDescend != null)
			{
				var vecExDescendXml:XML = <Vec_SExDescend3 _name_="vecExDescend"/>;
				for each(var s1:SExDescend3 in vecExDescend)
					vecExDescendXml.appendChild(s1.toXML());
				topXml.appendChild(vecExDescendXml);
			}
			return topXml;
		}
	}
}
