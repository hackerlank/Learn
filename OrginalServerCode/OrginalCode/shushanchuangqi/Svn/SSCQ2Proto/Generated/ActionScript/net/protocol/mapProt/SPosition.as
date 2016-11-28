/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPosition.as
//  Purpose:      地图相关功能的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 地图上物体的位置
	 */
	public final class SPosition
	{
		public var fX:Number; //(Float)X坐标
		public var fY:Number; //(Float)Y坐标

		/**
		 * 辅助创建函数
		 */
		public static function create(fX:Number, fY:Number):SPosition
		{
			var s_:SPosition = new SPosition();
			s_.fX = fX;
			s_.fY = fY;
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
				topXml = <SPosition _name_={name_} fX={fX} fY={fY}/>;
			else
				topXml = <SPosition fX={fX} fY={fY}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.fX = fX;
			obj_.fY = fY;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPosition
		{
			var s_:SPosition = new SPosition();
			var fX:Number = bytes.readFloat();
			s_.fX = fX;
			var fY:Number = bytes.readFloat();
			s_.fY = fY;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPosition>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPosition> = new Vector.<SPosition>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPosition = SPosition.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeFloat(fX);
			bytes.writeFloat(fY);
		}

		public static function vectorToByteArray(vec:Vector.<SPosition>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPosition in vec)
				s.toByteArray(bytes);
		}
	}
}
