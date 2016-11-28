/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGridCollideInfo.as
//  Purpose:      灵山（改名秘境）寻宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家格子碰撞信息
	 */
	public final class SGridCollideInfo
	{
		public var wPos:uint; //(无符号16位整数)碰撞位置
		public var qwWinPlayer:BigInteger; //(无符号64位整数)胜利玩家
		public var dwWinKillCnt:uint; //(无符号32位整数)击杀数目
		public var vecFailPlayer:Vector.<BigInteger>; //(无符号64位整数)失败玩家列表

		/**
		 * 辅助创建函数
		 */
		public static function create(wPos:uint, qwWinPlayer:BigInteger, dwWinKillCnt:uint, vecFailPlayer:Vector.<BigInteger>):SGridCollideInfo
		{
			var s_:SGridCollideInfo = new SGridCollideInfo();
			s_.wPos = wPos;
			s_.qwWinPlayer = qwWinPlayer;
			s_.dwWinKillCnt = dwWinKillCnt;
			s_.vecFailPlayer = vecFailPlayer;
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
				topXml = <SGridCollideInfo _name_={name_} wPos={wPos} qwWinPlayer={qwWinPlayer} dwWinKillCnt={dwWinKillCnt}/>;
			else
				topXml = <SGridCollideInfo wPos={wPos} qwWinPlayer={qwWinPlayer} dwWinKillCnt={dwWinKillCnt}/>;
			if(vecFailPlayer != null)
			{
				var vecFailPlayerXml:XML = <Vec_UINT64 _name_="vecFailPlayer"/>;
				var text1:String = "";
				for each(var value1:BigInteger in vecFailPlayer)
					text1 += "[" + value1 + "]";
				vecFailPlayerXml.appendChild(text1);
				topXml.appendChild(vecFailPlayerXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wPos = wPos;
			obj_.qwWinPlayer = qwWinPlayer;
			obj_.dwWinKillCnt = dwWinKillCnt;
			obj_.vecFailPlayer = vecFailPlayer;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGridCollideInfo
		{
			var s_:SGridCollideInfo = new SGridCollideInfo();
			var wPos:uint = bytes.readUnsignedShort();
			s_.wPos = wPos;
			var qwWinPlayer:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwWinPlayer = qwWinPlayer;
			var dwWinKillCnt:uint = bytes.readUnsignedInt();
			s_.dwWinKillCnt = dwWinKillCnt;
			var vecFailPlayer:Vector.<BigInteger> = BytesUtil.readVecUInt64(bytes);
			s_.vecFailPlayer = vecFailPlayer;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGridCollideInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGridCollideInfo> = new Vector.<SGridCollideInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGridCollideInfo = SGridCollideInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wPos);
			BytesUtil.writeUInt64(bytes, qwWinPlayer);
			bytes.writeUnsignedInt(dwWinKillCnt);
			BytesUtil.writeVecUInt64(bytes, vecFailPlayer);
		}

		public static function vectorToByteArray(vec:Vector.<SGridCollideInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGridCollideInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
