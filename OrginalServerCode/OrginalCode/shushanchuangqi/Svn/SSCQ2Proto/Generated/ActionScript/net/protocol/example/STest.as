/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STest.as
//  Purpose:      通信协议示例
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.example
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 前置声明测试
	 */
	public final class STest
	{
		public var pBase:SExBase; //父类指针
		public var vecBase:Vector.<SExBase>; //父类指针列表

		/**
		 * 辅助创建函数
		 */
		public static function create(pBase:SExBase, vecBase:Vector.<SExBase>):STest
		{
			var s_:STest = new STest();
			s_.pBase = pBase;
			s_.vecBase = vecBase;
			return s_;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <STest _name_={name_}/>;
			else
				topXml = <STest/>;
			if(pBase != null)
				topXml.appendChild(pBase.toXML("pBase"));
			if(vecBase != null)
			{
				var vecBaseXml:XML = <Vec_SExBase _name_="vecBase"/>;
				for each(var s2:SExBase in vecBase)
					vecBaseXml.appendChild(s2.toXML());
				topXml.appendChild(vecBaseXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.pBase = pBase;
			obj_.vecBase = vecBase;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STest
		{
			var s_:STest = new STest();
			var pBase:SExBase = SExBase.superFromByteArray(bytes);
			s_.pBase = pBase;
			var vecBase:Vector.<SExBase> = SExBase.superVectorFromByteArray(bytes);
			s_.vecBase = vecBase;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STest>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STest> = new Vector.<STest>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STest = STest.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			pBase.superToByteArray(bytes);
			SExBase.superVectorToByteArray(vecBase, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<STest>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STest in vec)
				s.toByteArray(bytes);
		}
	}
}
