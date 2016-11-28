/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPathCollideInfo.as
//  Purpose:      灵山（改名秘境）寻宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家路径碰撞信息
	 */
	public final class SPathCollideInfo
	{
		public var wMinPos:uint; //(无符号16位整数)小编号位置
		public var wMaxtPos:uint; //(无符号16位整数)大编号位置
		public var qwWinPlayer:BigInteger; //(无符号64位整数)胜利玩家
		public var dwWinKillCnt:uint; //(无符号32位整数)胜利击杀数目
		public var qwFailPlayer:BigInteger; //(无符号64位整数)失败玩家

		/**
		 * 辅助创建函数
		 */
		public static function create(wMinPos:uint, wMaxtPos:uint, qwWinPlayer:BigInteger, dwWinKillCnt:uint, qwFailPlayer:BigInteger):SPathCollideInfo
		{
			var s_:SPathCollideInfo = new SPathCollideInfo();
			s_.wMinPos = wMinPos;
			s_.wMaxtPos = wMaxtPos;
			s_.qwWinPlayer = qwWinPlayer;
			s_.dwWinKillCnt = dwWinKillCnt;
			s_.qwFailPlayer = qwFailPlayer;
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
				topXml = <SPathCollideInfo _name_={name_} wMinPos={wMinPos} wMaxtPos={wMaxtPos} qwWinPlayer={qwWinPlayer} dwWinKillCnt={dwWinKillCnt} qwFailPlayer={qwFailPlayer}/>;
			else
				topXml = <SPathCollideInfo wMinPos={wMinPos} wMaxtPos={wMaxtPos} qwWinPlayer={qwWinPlayer} dwWinKillCnt={dwWinKillCnt} qwFailPlayer={qwFailPlayer}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wMinPos = wMinPos;
			obj_.wMaxtPos = wMaxtPos;
			obj_.qwWinPlayer = qwWinPlayer;
			obj_.dwWinKillCnt = dwWinKillCnt;
			obj_.qwFailPlayer = qwFailPlayer;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPathCollideInfo
		{
			var s_:SPathCollideInfo = new SPathCollideInfo();
			var wMinPos:uint = bytes.readUnsignedShort();
			s_.wMinPos = wMinPos;
			var wMaxtPos:uint = bytes.readUnsignedShort();
			s_.wMaxtPos = wMaxtPos;
			var qwWinPlayer:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwWinPlayer = qwWinPlayer;
			var dwWinKillCnt:uint = bytes.readUnsignedInt();
			s_.dwWinKillCnt = dwWinKillCnt;
			var qwFailPlayer:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwFailPlayer = qwFailPlayer;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPathCollideInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPathCollideInfo> = new Vector.<SPathCollideInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPathCollideInfo = SPathCollideInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wMinPos);
			bytes.writeShort(wMaxtPos);
			BytesUtil.writeUInt64(bytes, qwWinPlayer);
			bytes.writeUnsignedInt(dwWinKillCnt);
			BytesUtil.writeUInt64(bytes, qwFailPlayer);
		}

		public static function vectorToByteArray(vec:Vector.<SPathCollideInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPathCollideInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
