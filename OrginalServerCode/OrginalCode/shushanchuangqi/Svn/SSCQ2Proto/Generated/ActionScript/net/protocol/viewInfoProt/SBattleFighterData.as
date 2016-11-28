/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattleFighterData.as
//  Purpose:      查看信息协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.viewInfoProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 出战散仙信息
	 */
	public final class SBattleFighterData
	{
		public var qwInstID:BigInteger; //(无符号64位整数)散仙唯一ID
		public var wFighterID:uint; //(无符号16位整数)散仙模版
		public var byFighterLevel:uint; //(无符号8位整数)散仙等级
		public var byTemplateID:uint; //(无符号8位整数)渡劫模版Id
		public var byLevel:uint; //(无符号8位整数)渡劫等级

		/**
		 * 辅助创建函数
		 */
		public static function create(qwInstID:BigInteger, wFighterID:uint, byFighterLevel:uint, byTemplateID:uint, byLevel:uint):SBattleFighterData
		{
			var s_:SBattleFighterData = new SBattleFighterData();
			s_.qwInstID = qwInstID;
			s_.wFighterID = wFighterID;
			s_.byFighterLevel = byFighterLevel;
			s_.byTemplateID = byTemplateID;
			s_.byLevel = byLevel;
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
				topXml = <SBattleFighterData _name_={name_} qwInstID={qwInstID} wFighterID={wFighterID} byFighterLevel={byFighterLevel} byTemplateID={byTemplateID} byLevel={byLevel}/>;
			else
				topXml = <SBattleFighterData qwInstID={qwInstID} wFighterID={wFighterID} byFighterLevel={byFighterLevel} byTemplateID={byTemplateID} byLevel={byLevel}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwInstID = qwInstID;
			obj_.wFighterID = wFighterID;
			obj_.byFighterLevel = byFighterLevel;
			obj_.byTemplateID = byTemplateID;
			obj_.byLevel = byLevel;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattleFighterData
		{
			var s_:SBattleFighterData = new SBattleFighterData();
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInstID = qwInstID;
			var wFighterID:uint = bytes.readUnsignedShort();
			s_.wFighterID = wFighterID;
			var byFighterLevel:uint = bytes.readUnsignedByte();
			s_.byFighterLevel = byFighterLevel;
			var byTemplateID:uint = bytes.readUnsignedByte();
			s_.byTemplateID = byTemplateID;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattleFighterData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleFighterData> = new Vector.<SBattleFighterData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleFighterData = SBattleFighterData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwInstID);
			bytes.writeShort(wFighterID);
			bytes.writeByte(byFighterLevel);
			bytes.writeByte(byTemplateID);
			bytes.writeByte(byLevel);
		}

		public static function vectorToByteArray(vec:Vector.<SBattleFighterData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleFighterData in vec)
				s.toByteArray(bytes);
		}
	}
}
