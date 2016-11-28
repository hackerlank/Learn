/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SCollectionData.as
//  Purpose:      查看信息协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.viewInfoProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 收集信息
	 */
	public final class SCollectionData
	{
		public var byCollectionLevel:uint; //(无符号8位整数)收藏等级
		public var dwAP:uint; //(无符号32位整数)收藏点

		/**
		 * 辅助创建函数
		 */
		public static function create(byCollectionLevel:uint, dwAP:uint):SCollectionData
		{
			var s_:SCollectionData = new SCollectionData();
			s_.byCollectionLevel = byCollectionLevel;
			s_.dwAP = dwAP;
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
				topXml = <SCollectionData _name_={name_} byCollectionLevel={byCollectionLevel} dwAP={dwAP}/>;
			else
				topXml = <SCollectionData byCollectionLevel={byCollectionLevel} dwAP={dwAP}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byCollectionLevel = byCollectionLevel;
			obj_.dwAP = dwAP;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SCollectionData
		{
			var s_:SCollectionData = new SCollectionData();
			var byCollectionLevel:uint = bytes.readUnsignedByte();
			s_.byCollectionLevel = byCollectionLevel;
			var dwAP:uint = bytes.readUnsignedInt();
			s_.dwAP = dwAP;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SCollectionData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SCollectionData> = new Vector.<SCollectionData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SCollectionData = SCollectionData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byCollectionLevel);
			bytes.writeUnsignedInt(dwAP);
		}

		public static function vectorToByteArray(vec:Vector.<SCollectionData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SCollectionData in vec)
				s.toByteArray(bytes);
		}
	}
}
