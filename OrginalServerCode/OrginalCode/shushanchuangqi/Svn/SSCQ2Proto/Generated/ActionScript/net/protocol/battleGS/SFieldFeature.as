/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFieldFeature.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 场景
	 */
	public final class SFieldFeature extends SFeatureBase
	{
		public var wSceneID:uint; //(无符号16位整数)场景ID

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SFeatureBase.eType_SFieldFeature;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SFieldFeature _name_={name_} wSceneID={wSceneID}/>;
			else
				topXml = <SFieldFeature wSceneID={wSceneID}/>;
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
			obj_.wSceneID = wSceneID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFieldFeature
		{
			var s_:SFieldFeature = new SFieldFeature();
			var base_:SFeatureBase = SFeatureBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var wSceneID:uint = bytes.readUnsignedShort();
			s_.wSceneID = wSceneID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFieldFeature>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFieldFeature> = new Vector.<SFieldFeature>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFieldFeature = SFieldFeature.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wSceneID);
		}

		public static function vectorToByteArray(vec:Vector.<SFieldFeature>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFieldFeature in vec)
				s.toByteArray(bytes);
		}
	}
}
