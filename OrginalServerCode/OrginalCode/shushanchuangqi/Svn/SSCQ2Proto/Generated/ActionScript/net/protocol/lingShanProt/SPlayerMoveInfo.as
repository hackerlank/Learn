/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPlayerMoveInfo.as
//  Purpose:      灵山（改名秘境）寻宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家移动信息
	 */
	public final class SPlayerMoveInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家id
		public var wSrcPos:uint; //(无符号16位整数)当前位置
		public var wDstPos:uint; //(无符号16位整数)目标位置

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, wSrcPos:uint, wDstPos:uint):SPlayerMoveInfo
		{
			var s_:SPlayerMoveInfo = new SPlayerMoveInfo();
			s_.qwRoleID = qwRoleID;
			s_.wSrcPos = wSrcPos;
			s_.wDstPos = wDstPos;
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
				topXml = <SPlayerMoveInfo _name_={name_} qwRoleID={qwRoleID} wSrcPos={wSrcPos} wDstPos={wDstPos}/>;
			else
				topXml = <SPlayerMoveInfo qwRoleID={qwRoleID} wSrcPos={wSrcPos} wDstPos={wDstPos}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.wSrcPos = wSrcPos;
			obj_.wDstPos = wDstPos;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPlayerMoveInfo
		{
			var s_:SPlayerMoveInfo = new SPlayerMoveInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var wSrcPos:uint = bytes.readUnsignedShort();
			s_.wSrcPos = wSrcPos;
			var wDstPos:uint = bytes.readUnsignedShort();
			s_.wDstPos = wDstPos;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPlayerMoveInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPlayerMoveInfo> = new Vector.<SPlayerMoveInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPlayerMoveInfo = SPlayerMoveInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeShort(wSrcPos);
			bytes.writeShort(wDstPos);
		}

		public static function vectorToByteArray(vec:Vector.<SPlayerMoveInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPlayerMoveInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
