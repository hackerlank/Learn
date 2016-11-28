/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SAttrGroup.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 属性加成
	 */
	public final class SAttrGroup
	{
		public var eType:uint; //(枚举类型：EAttrGroupType)属性加成类型
		public var vecFtAttrMod:Vector.<SFtAttrMod>; //属性变化结构

		/**
		 * 辅助创建函数
		 */
		public static function create(eType:uint, vecFtAttrMod:Vector.<SFtAttrMod>):SAttrGroup
		{
			var s_:SAttrGroup = new SAttrGroup();
			s_.eType = eType;
			s_.vecFtAttrMod = vecFtAttrMod;
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
				topXml = <SAttrGroup _name_={name_} eType={eType}/>;
			else
				topXml = <SAttrGroup eType={eType}/>;
			if(vecFtAttrMod != null)
			{
				var vecFtAttrModXml:XML = <Vec_SFtAttrMod _name_="vecFtAttrMod"/>;
				for each(var s1:SFtAttrMod in vecFtAttrMod)
					vecFtAttrModXml.appendChild(s1.toXML());
				topXml.appendChild(vecFtAttrModXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.eType = eType;
			obj_.vecFtAttrMod = vecFtAttrMod;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SAttrGroup
		{
			var s_:SAttrGroup = new SAttrGroup();
			var eType:uint = bytes.readUnsignedByte();
			s_.eType = eType;
			var vecFtAttrMod:Vector.<SFtAttrMod> = SFtAttrMod.vectorFromByteArray(bytes);
			s_.vecFtAttrMod = vecFtAttrMod;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SAttrGroup>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SAttrGroup> = new Vector.<SAttrGroup>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SAttrGroup = SAttrGroup.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eType);
			SFtAttrMod.vectorToByteArray(vecFtAttrMod, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SAttrGroup>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SAttrGroup in vec)
				s.toByteArray(bytes);
		}
	}
}
