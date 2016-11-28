/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBeautyData.as
//  Purpose:      查看信息协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.viewInfoProt
{
	import net.protocol.protoCommon.SFtAttrMod;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 出战美女信息
	 */
	public final class SBeautyData
	{
		public var wBeautyID:uint; //(无符号16位整数)美女ID
		public var byLevel:uint; //(无符号8位整数)美女等级
		public var vecAttr:Vector.<SFtAttrMod>; //美女属性

		/**
		 * 辅助创建函数
		 */
		public static function create(wBeautyID:uint, byLevel:uint, vecAttr:Vector.<SFtAttrMod>):SBeautyData
		{
			var s_:SBeautyData = new SBeautyData();
			s_.wBeautyID = wBeautyID;
			s_.byLevel = byLevel;
			s_.vecAttr = vecAttr;
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
				topXml = <SBeautyData _name_={name_} wBeautyID={wBeautyID} byLevel={byLevel}/>;
			else
				topXml = <SBeautyData wBeautyID={wBeautyID} byLevel={byLevel}/>;
			if(vecAttr != null)
			{
				var vecAttrXml:XML = <Vec_SFtAttrMod _name_="vecAttr"/>;
				for each(var s1:SFtAttrMod in vecAttr)
					vecAttrXml.appendChild(s1.toXML());
				topXml.appendChild(vecAttrXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wBeautyID = wBeautyID;
			obj_.byLevel = byLevel;
			obj_.vecAttr = vecAttr;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBeautyData
		{
			var s_:SBeautyData = new SBeautyData();
			var wBeautyID:uint = bytes.readUnsignedShort();
			s_.wBeautyID = wBeautyID;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var vecAttr:Vector.<SFtAttrMod> = SFtAttrMod.vectorFromByteArray(bytes);
			s_.vecAttr = vecAttr;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBeautyData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBeautyData> = new Vector.<SBeautyData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBeautyData = SBeautyData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wBeautyID);
			bytes.writeByte(byLevel);
			SFtAttrMod.vectorToByteArray(vecAttr, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SBeautyData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBeautyData in vec)
				s.toByteArray(bytes);
		}
	}
}
