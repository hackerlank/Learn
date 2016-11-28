/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SOrigParam_SampleRetFunc2.as
//  Purpose:      C->S有返回值的示例函数
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.example
{
	import com.hurlant.math.BigInteger;

	/**
	 * C->S有返回值的示例函数的原来的参数组成的结构体
	 */
	public final class SOrigParam_SampleRetFunc2
	{
		public var qwParam2:BigInteger; //(无符号64位整数)参数2，保存
		public var loc_derived:SExDerived2; //结构体，本地保存
		public var callback:Function;

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SOrigParam_SampleRetFunc2 _name_={name_} qwParam2={qwParam2}/>;
			else
				topXml = <SOrigParam_SampleRetFunc2 qwParam2={qwParam2}/>;
			if(loc_derived != null)
				topXml.appendChild(loc_derived.toXML("loc_derived"));
			return topXml;
		}
	}
}
