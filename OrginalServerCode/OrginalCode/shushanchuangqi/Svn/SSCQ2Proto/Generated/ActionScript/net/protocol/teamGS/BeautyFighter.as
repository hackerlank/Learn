/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    BeautyFighter.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 阵灵
	 */
	public final class BeautyFighter extends TeamFighter
	{
		public var wFighterID:uint; //(无符号16位整数)阵灵ID

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_TeamFighter.eType_BeautyFighter;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <BeautyFighter _name_={name_} wFighterID={wFighterID}/>;
			else
				topXml = <BeautyFighter wFighterID={wFighterID}/>;
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
			obj_.wFighterID = wFighterID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):BeautyFighter
		{
			var s_:BeautyFighter = new BeautyFighter();
			var base_:TeamFighter = TeamFighter.fromByteArray(bytes);
			base_.copyTo(s_);
			var wFighterID:uint = bytes.readUnsignedShort();
			s_.wFighterID = wFighterID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<BeautyFighter>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<BeautyFighter> = new Vector.<BeautyFighter>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:BeautyFighter = BeautyFighter.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wFighterID);
		}

		public static function vectorToByteArray(vec:Vector.<BeautyFighter>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:BeautyFighter in vec)
				s.toByteArray(bytes);
		}
	}
}
