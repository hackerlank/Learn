/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SArenaFighter.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	import net.protocol.battleGS.SPlayerFeature;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 竞技场玩家信息
	 */
	public final class SArenaFighter
	{
		public var strName:String; //名字
		public var wLevel:uint; //(无符号16位整数)等级
		public var stAppear:SPlayerFeature; //外观

		/**
		 * 辅助创建函数
		 */
		public static function create(strName:String, wLevel:uint, stAppear:SPlayerFeature):SArenaFighter
		{
			var s_:SArenaFighter = new SArenaFighter();
			s_.strName = strName;
			s_.wLevel = wLevel;
			s_.stAppear = stAppear;
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
				topXml = <SArenaFighter _name_={name_} strName={strName} wLevel={wLevel}/>;
			else
				topXml = <SArenaFighter strName={strName} wLevel={wLevel}/>;
			if(stAppear != null)
				topXml.appendChild(stAppear.toXML("stAppear"));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.strName = strName;
			obj_.wLevel = wLevel;
			obj_.stAppear = stAppear;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SArenaFighter
		{
			var s_:SArenaFighter = new SArenaFighter();
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var wLevel:uint = bytes.readUnsignedShort();
			s_.wLevel = wLevel;
			var stAppear:SPlayerFeature = SPlayerFeature.fromByteArray(bytes);
			s_.stAppear = stAppear;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SArenaFighter>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SArenaFighter> = new Vector.<SArenaFighter>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SArenaFighter = SArenaFighter.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeString(bytes, strName);
			bytes.writeShort(wLevel);
			stAppear.toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SArenaFighter>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SArenaFighter in vec)
				s.toByteArray(bytes);
		}
	}
}
