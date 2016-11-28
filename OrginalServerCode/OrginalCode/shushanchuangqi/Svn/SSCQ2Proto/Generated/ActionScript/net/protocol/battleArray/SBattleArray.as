/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattleArray.as
//  Purpose:      破阵
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleArray
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 阵信息
	 */
	public final class SBattleArray
	{
		public var wBattleArrayID:uint; //(无符号16位整数)阵id
		public var dwBattleArrayLevelID:uint; //(无符号32位整数)破阵进度(阵图id)
		public var eBattleArrayStatus:uint; //(枚举类型：EBattleArrayStatus)阵状态

		/**
		 * 辅助创建函数
		 */
		public static function create(wBattleArrayID:uint, dwBattleArrayLevelID:uint, eBattleArrayStatus:uint):SBattleArray
		{
			var s_:SBattleArray = new SBattleArray();
			s_.wBattleArrayID = wBattleArrayID;
			s_.dwBattleArrayLevelID = dwBattleArrayLevelID;
			s_.eBattleArrayStatus = eBattleArrayStatus;
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
				topXml = <SBattleArray _name_={name_} wBattleArrayID={wBattleArrayID} dwBattleArrayLevelID={dwBattleArrayLevelID} eBattleArrayStatus={eBattleArrayStatus}/>;
			else
				topXml = <SBattleArray wBattleArrayID={wBattleArrayID} dwBattleArrayLevelID={dwBattleArrayLevelID} eBattleArrayStatus={eBattleArrayStatus}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wBattleArrayID = wBattleArrayID;
			obj_.dwBattleArrayLevelID = dwBattleArrayLevelID;
			obj_.eBattleArrayStatus = eBattleArrayStatus;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattleArray
		{
			var s_:SBattleArray = new SBattleArray();
			var wBattleArrayID:uint = bytes.readUnsignedShort();
			s_.wBattleArrayID = wBattleArrayID;
			var dwBattleArrayLevelID:uint = bytes.readUnsignedInt();
			s_.dwBattleArrayLevelID = dwBattleArrayLevelID;
			var eBattleArrayStatus:uint = bytes.readUnsignedByte();
			s_.eBattleArrayStatus = eBattleArrayStatus;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattleArray>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleArray> = new Vector.<SBattleArray>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleArray = SBattleArray.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wBattleArrayID);
			bytes.writeUnsignedInt(dwBattleArrayLevelID);
			bytes.writeByte(eBattleArrayStatus);
		}

		public static function vectorToByteArray(vec:Vector.<SBattleArray>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleArray in vec)
				s.toByteArray(bytes);
		}
	}
}
