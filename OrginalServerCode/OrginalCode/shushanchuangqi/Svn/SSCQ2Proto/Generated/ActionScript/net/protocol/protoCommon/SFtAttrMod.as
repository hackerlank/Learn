/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFtAttrMod.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 属性变化结构
	 */
	public final class SFtAttrMod
	{
		public var _eAttr:uint; //(枚举类型：EFighterAttr)属性类型
		public var _fValue:Number; //(Float)改变的值

		/**
		 * 辅助创建函数
		 */
		public static function create(_eAttr:uint, _fValue:Number):SFtAttrMod
		{
			var s_:SFtAttrMod = new SFtAttrMod();
			s_._eAttr = _eAttr;
			s_._fValue = _fValue;
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
				topXml = <SFtAttrMod _name_={name_} _eAttr={_eAttr} _fValue={_fValue}/>;
			else
				topXml = <SFtAttrMod _eAttr={_eAttr} _fValue={_fValue}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_._eAttr = _eAttr;
			obj_._fValue = _fValue;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFtAttrMod
		{
			var s_:SFtAttrMod = new SFtAttrMod();
			var _eAttr:uint = bytes.readUnsignedByte();
			s_._eAttr = _eAttr;
			var _fValue:Number = bytes.readFloat();
			s_._fValue = _fValue;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFtAttrMod>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFtAttrMod> = new Vector.<SFtAttrMod>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFtAttrMod = SFtAttrMod.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(_eAttr);
			bytes.writeFloat(_fValue);
		}

		public static function vectorToByteArray(vec:Vector.<SFtAttrMod>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFtAttrMod in vec)
				s.toByteArray(bytes);
		}
	}
}
