/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    MapOverLoad.as
//  Purpose:      地图相关功能的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 地图负载情况
	 */
	public final class MapOverLoad
	{
		public var byIndex:uint; //(无符号8位整数)地图序号
		public var eLoadState:uint; //(枚举类型：EMapOverLoad)负载状况

		/**
		 * 辅助创建函数
		 */
		public static function create(byIndex:uint, eLoadState:uint):MapOverLoad
		{
			var s_:MapOverLoad = new MapOverLoad();
			s_.byIndex = byIndex;
			s_.eLoadState = eLoadState;
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
				topXml = <MapOverLoad _name_={name_} byIndex={byIndex} eLoadState={eLoadState}/>;
			else
				topXml = <MapOverLoad byIndex={byIndex} eLoadState={eLoadState}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byIndex = byIndex;
			obj_.eLoadState = eLoadState;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):MapOverLoad
		{
			var s_:MapOverLoad = new MapOverLoad();
			var byIndex:uint = bytes.readUnsignedByte();
			s_.byIndex = byIndex;
			var eLoadState:uint = bytes.readUnsignedByte();
			s_.eLoadState = eLoadState;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<MapOverLoad>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<MapOverLoad> = new Vector.<MapOverLoad>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:MapOverLoad = MapOverLoad.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byIndex);
			bytes.writeByte(eLoadState);
		}

		public static function vectorToByteArray(vec:Vector.<MapOverLoad>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:MapOverLoad in vec)
				s.toByteArray(bytes);
		}
	}
}
