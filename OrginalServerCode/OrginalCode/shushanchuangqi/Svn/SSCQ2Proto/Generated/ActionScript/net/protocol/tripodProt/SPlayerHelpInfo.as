/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPlayerHelpInfo.as
//  Purpose:      九疑鼎相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.tripodProt
{
	import com.hurlant.math.BigInteger;
	import net.protocol.arenaGS.SArenaFighter;
	import net.protocol.protoCommon.SPlatformParam;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 九疑鼎玩家协助
	 */
	public final class SPlayerHelpInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)协助者(玩家)ID
		public var byPos:uint; //(无符号8位整数)协助位置(0,1,2)
		public var byLevel:uint; //(无符号8位整数)玩家协助时的等级
		public var dwStartTime:uint; //(无符号32位整数)开始协助的时间
		public var stPlayer:SArenaFighter; //玩家的基础信息(外观)
		public var vecPlatforms:Vector.<SPlatformParam>; //平台信息

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, byPos:uint, byLevel:uint, dwStartTime:uint, stPlayer:SArenaFighter, 
			vecPlatforms:Vector.<SPlatformParam>):SPlayerHelpInfo
		{
			var s_:SPlayerHelpInfo = new SPlayerHelpInfo();
			s_.qwRoleID = qwRoleID;
			s_.byPos = byPos;
			s_.byLevel = byLevel;
			s_.dwStartTime = dwStartTime;
			s_.stPlayer = stPlayer;
			s_.vecPlatforms = vecPlatforms;
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
				topXml = <SPlayerHelpInfo _name_={name_} qwRoleID={qwRoleID} byPos={byPos} byLevel={byLevel} dwStartTime={dwStartTime}/>;
			else
				topXml = <SPlayerHelpInfo qwRoleID={qwRoleID} byPos={byPos} byLevel={byLevel} dwStartTime={dwStartTime}/>;
			if(stPlayer != null)
				topXml.appendChild(stPlayer.toXML("stPlayer"));
			if(vecPlatforms != null)
			{
				var vecPlatformsXml:XML = <Vec_SPlatformParam _name_="vecPlatforms"/>;
				for each(var s2:SPlatformParam in vecPlatforms)
					vecPlatformsXml.appendChild(s2.toXML());
				topXml.appendChild(vecPlatformsXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.byPos = byPos;
			obj_.byLevel = byLevel;
			obj_.dwStartTime = dwStartTime;
			obj_.stPlayer = stPlayer;
			obj_.vecPlatforms = vecPlatforms;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPlayerHelpInfo
		{
			var s_:SPlayerHelpInfo = new SPlayerHelpInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var byPos:uint = bytes.readUnsignedByte();
			s_.byPos = byPos;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var dwStartTime:uint = bytes.readUnsignedInt();
			s_.dwStartTime = dwStartTime;
			var stPlayer:SArenaFighter = SArenaFighter.fromByteArray(bytes);
			s_.stPlayer = stPlayer;
			var vecPlatforms:Vector.<SPlatformParam> = SPlatformParam.vectorFromByteArray(bytes);
			s_.vecPlatforms = vecPlatforms;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPlayerHelpInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPlayerHelpInfo> = new Vector.<SPlayerHelpInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPlayerHelpInfo = SPlayerHelpInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeByte(byPos);
			bytes.writeByte(byLevel);
			bytes.writeUnsignedInt(dwStartTime);
			stPlayer.toByteArray(bytes);
			SPlatformParam.vectorToByteArray(vecPlatforms, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SPlayerHelpInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPlayerHelpInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
