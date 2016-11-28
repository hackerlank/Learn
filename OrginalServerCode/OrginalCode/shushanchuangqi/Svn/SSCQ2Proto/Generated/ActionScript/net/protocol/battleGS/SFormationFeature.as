/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFormationFeature.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 阵灵
	 */
	public final class SFormationFeature extends SFeatureBase
	{
		public var wFormationID:uint; //(无符号16位整数)阵灵配置表ID，同monster

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SFeatureBase.eType_SFormationFeature;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SFormationFeature _name_={name_} wFormationID={wFormationID}/>;
			else
				topXml = <SFormationFeature wFormationID={wFormationID}/>;
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
			obj_.wFormationID = wFormationID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFormationFeature
		{
			var s_:SFormationFeature = new SFormationFeature();
			var base_:SFeatureBase = SFeatureBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var wFormationID:uint = bytes.readUnsignedShort();
			s_.wFormationID = wFormationID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFormationFeature>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFormationFeature> = new Vector.<SFormationFeature>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFormationFeature = SFormationFeature.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wFormationID);
		}

		public static function vectorToByteArray(vec:Vector.<SFormationFeature>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFormationFeature in vec)
				s.toByteArray(bytes);
		}
	}
}
