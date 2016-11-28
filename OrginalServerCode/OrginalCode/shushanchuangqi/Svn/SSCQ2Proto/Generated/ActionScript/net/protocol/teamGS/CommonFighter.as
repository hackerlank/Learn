/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    CommonFighter.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 普通将
	 */
	public final class CommonFighter extends TeamFighter
	{
		public var qwInstID:BigInteger; //(无符号64位整数)将唯一ID
		public var wFighterID:uint; //(无符号16位整数)将类型ID
		public var byLevel:uint; //(无符号8位整数)等级
		public var byMain:uint; //(无符号8位整数)是否主将

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_TeamFighter.eType_CommonFighter;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <CommonFighter _name_={name_} qwInstID={qwInstID} wFighterID={wFighterID} byLevel={byLevel} byMain={byMain}/>;
			else
				topXml = <CommonFighter qwInstID={qwInstID} wFighterID={wFighterID} byLevel={byLevel} byMain={byMain}/>;
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
			obj_.qwInstID = qwInstID;
			obj_.wFighterID = wFighterID;
			obj_.byLevel = byLevel;
			obj_.byMain = byMain;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):CommonFighter
		{
			var s_:CommonFighter = new CommonFighter();
			var base_:TeamFighter = TeamFighter.fromByteArray(bytes);
			base_.copyTo(s_);
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInstID = qwInstID;
			var wFighterID:uint = bytes.readUnsignedShort();
			s_.wFighterID = wFighterID;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var byMain:uint = bytes.readUnsignedByte();
			s_.byMain = byMain;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<CommonFighter>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<CommonFighter> = new Vector.<CommonFighter>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:CommonFighter = CommonFighter.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			BytesUtil.writeUInt64(bytes, qwInstID);
			bytes.writeShort(wFighterID);
			bytes.writeByte(byLevel);
			bytes.writeByte(byMain);
		}

		public static function vectorToByteArray(vec:Vector.<CommonFighter>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:CommonFighter in vec)
				s.toByteArray(bytes);
		}
	}
}
