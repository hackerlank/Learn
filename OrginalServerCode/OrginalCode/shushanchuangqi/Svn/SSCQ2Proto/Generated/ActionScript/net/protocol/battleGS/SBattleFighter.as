/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattleFighter.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * Fighter信息
	 */
	public final class SBattleFighter
	{
		public var byFighterID:uint; //(无符号8位整数)战场开始之后分配的唯一ID，groupID*5*5+pos
		public var oFgtInfo:SBattleFighterInfo; //FighterInfo

		/**
		 * 辅助创建函数
		 */
		public static function create(byFighterID:uint, oFgtInfo:SBattleFighterInfo):SBattleFighter
		{
			var s_:SBattleFighter = new SBattleFighter();
			s_.byFighterID = byFighterID;
			s_.oFgtInfo = oFgtInfo;
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
				topXml = <SBattleFighter _name_={name_} byFighterID={byFighterID}/>;
			else
				topXml = <SBattleFighter byFighterID={byFighterID}/>;
			if(oFgtInfo != null)
				topXml.appendChild(oFgtInfo.toXML("oFgtInfo"));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byFighterID = byFighterID;
			obj_.oFgtInfo = oFgtInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattleFighter
		{
			var s_:SBattleFighter = new SBattleFighter();
			var byFighterID:uint = bytes.readUnsignedByte();
			s_.byFighterID = byFighterID;
			var oFgtInfo:SBattleFighterInfo = SBattleFighterInfo.fromByteArray(bytes);
			s_.oFgtInfo = oFgtInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattleFighter>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleFighter> = new Vector.<SBattleFighter>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleFighter = SBattleFighter.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byFighterID);
			oFgtInfo.toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SBattleFighter>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleFighter in vec)
				s.toByteArray(bytes);
		}
	}
}
