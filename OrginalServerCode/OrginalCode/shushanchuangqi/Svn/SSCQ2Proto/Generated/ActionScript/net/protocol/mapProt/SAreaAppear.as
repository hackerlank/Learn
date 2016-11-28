/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SAreaAppear.as
//  Purpose:      地图相关功能的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 区域外观
	 */
	public final class SAreaAppear
	{
		public var wAreaID:uint; //(无符号16位整数)区域类型ID，表格数据

		/**
		 * 辅助创建函数
		 */
		public static function create(wAreaID:uint):SAreaAppear
		{
			var s_:SAreaAppear = new SAreaAppear();
			s_.wAreaID = wAreaID;
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
				topXml = <SAreaAppear _name_={name_} wAreaID={wAreaID}/>;
			else
				topXml = <SAreaAppear wAreaID={wAreaID}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wAreaID = wAreaID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SAreaAppear
		{
			var s_:SAreaAppear = new SAreaAppear();
			var wAreaID:uint = bytes.readUnsignedShort();
			s_.wAreaID = wAreaID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SAreaAppear>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SAreaAppear> = new Vector.<SAreaAppear>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SAreaAppear = SAreaAppear.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wAreaID);
		}

		public static function vectorToByteArray(vec:Vector.<SAreaAppear>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SAreaAppear in vec)
				s.toByteArray(bytes);
		}
	}
}
