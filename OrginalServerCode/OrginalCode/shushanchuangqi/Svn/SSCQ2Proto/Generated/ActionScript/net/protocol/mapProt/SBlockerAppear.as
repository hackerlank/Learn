/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBlockerAppear.as
//  Purpose:      地图相关功能的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 阻挡物外观
	 */
	public final class SBlockerAppear
	{
		public var dwBlockerID:uint; //(无符号32位整数)阻挡物类型ID,表格数据
		public var vecPos:Vector.<SPosition>; //阻挡物阻挡坐标点

		/**
		 * 辅助创建函数
		 */
		public static function create(dwBlockerID:uint, vecPos:Vector.<SPosition>):SBlockerAppear
		{
			var s_:SBlockerAppear = new SBlockerAppear();
			s_.dwBlockerID = dwBlockerID;
			s_.vecPos = vecPos;
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
				topXml = <SBlockerAppear _name_={name_} dwBlockerID={dwBlockerID}/>;
			else
				topXml = <SBlockerAppear dwBlockerID={dwBlockerID}/>;
			if(vecPos != null)
			{
				var vecPosXml:XML = <Vec_SPosition _name_="vecPos"/>;
				for each(var s1:SPosition in vecPos)
					vecPosXml.appendChild(s1.toXML());
				topXml.appendChild(vecPosXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwBlockerID = dwBlockerID;
			obj_.vecPos = vecPos;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBlockerAppear
		{
			var s_:SBlockerAppear = new SBlockerAppear();
			var dwBlockerID:uint = bytes.readUnsignedInt();
			s_.dwBlockerID = dwBlockerID;
			var vecPos:Vector.<SPosition> = SPosition.vectorFromByteArray(bytes);
			s_.vecPos = vecPos;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBlockerAppear>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBlockerAppear> = new Vector.<SBlockerAppear>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBlockerAppear = SBlockerAppear.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwBlockerID);
			SPosition.vectorToByteArray(vecPos, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SBlockerAppear>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBlockerAppear in vec)
				s.toByteArray(bytes);
		}
	}
}
