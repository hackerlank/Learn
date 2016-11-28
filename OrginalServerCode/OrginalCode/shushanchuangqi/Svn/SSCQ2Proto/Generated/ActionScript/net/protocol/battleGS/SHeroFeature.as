/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SHeroFeature.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 散仙
	 */
	public final class SHeroFeature extends SFeatureBase
	{
		public var wHeroID:uint; //(无符号16位整数)散仙类型
		public var byQuality:uint; //(无符号8位整数)品质
		public var byDujieLevel:uint; //(无符号8位整数)散仙渡劫等级

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SFeatureBase.eType_SHeroFeature;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SHeroFeature _name_={name_} wHeroID={wHeroID} byQuality={byQuality} byDujieLevel={byDujieLevel}/>;
			else
				topXml = <SHeroFeature wHeroID={wHeroID} byQuality={byQuality} byDujieLevel={byDujieLevel}/>;
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public override function copyTo(obj_:*):void
		{
			super.copyTo(obj_);
			obj_.wHeroID = wHeroID;
			obj_.byQuality = byQuality;
			obj_.byDujieLevel = byDujieLevel;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SHeroFeature
		{
			var s_:SHeroFeature = new SHeroFeature();
			var base_:SFeatureBase = SFeatureBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var wHeroID:uint = bytes.readUnsignedShort();
			s_.wHeroID = wHeroID;
			var byQuality:uint = bytes.readUnsignedByte();
			s_.byQuality = byQuality;
			var byDujieLevel:uint = bytes.readUnsignedByte();
			s_.byDujieLevel = byDujieLevel;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SHeroFeature>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SHeroFeature> = new Vector.<SHeroFeature>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SHeroFeature = SHeroFeature.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wHeroID);
			bytes.writeByte(byQuality);
			bytes.writeByte(byDujieLevel);
		}

		public static function vectorToByteArray(vec:Vector.<SHeroFeature>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SHeroFeature in vec)
				s.toByteArray(bytes);
		}
	}
}
