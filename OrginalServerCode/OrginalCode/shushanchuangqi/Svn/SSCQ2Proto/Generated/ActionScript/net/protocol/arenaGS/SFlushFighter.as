/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFlushFighter.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家刷对手信息
	 */
	public final class SFlushFighter
	{
		public var bySuc:uint; //(无符号8位整数)0,表示未战胜；1，表示已击败
		public var qwFighterID:BigInteger; //(无符号64位整数)对手ID,小于65535为怪物

		/**
		 * 辅助创建函数
		 */
		public static function create(bySuc:uint, qwFighterID:BigInteger):SFlushFighter
		{
			var s_:SFlushFighter = new SFlushFighter();
			s_.bySuc = bySuc;
			s_.qwFighterID = qwFighterID;
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
				topXml = <SFlushFighter _name_={name_} bySuc={bySuc} qwFighterID={qwFighterID}/>;
			else
				topXml = <SFlushFighter bySuc={bySuc} qwFighterID={qwFighterID}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.bySuc = bySuc;
			obj_.qwFighterID = qwFighterID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFlushFighter
		{
			var s_:SFlushFighter = new SFlushFighter();
			var bySuc:uint = bytes.readUnsignedByte();
			s_.bySuc = bySuc;
			var qwFighterID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwFighterID = qwFighterID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFlushFighter>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFlushFighter> = new Vector.<SFlushFighter>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFlushFighter = SFlushFighter.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(bySuc);
			BytesUtil.writeUInt64(bytes, qwFighterID);
		}

		public static function vectorToByteArray(vec:Vector.<SFlushFighter>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFlushFighter in vec)
				s.toByteArray(bytes);
		}
	}
}
