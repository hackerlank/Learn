/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRankInfo.as
//  Purpose:      排行榜相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.rankProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 排名信息
	 */
	public class SRankInfo
	{
		public var dwValue:uint; //(无符号32位整数)排名依据的信息(战斗力/等级……)
		public var dwUpdateTime:uint; //(无符号32位整数)更新时间

		/**
		 * 获取继承类的类型
		 */
		public function getClassType():uint
		{
			return EType_SRankInfo.eType_SRankInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRankInfo _name_={name_} dwValue={dwValue} dwUpdateTime={dwUpdateTime}/>;
			else
				topXml = <SRankInfo dwValue={dwValue} dwUpdateTime={dwUpdateTime}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwValue = dwValue;
			obj_.dwUpdateTime = dwUpdateTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRankInfo
		{
			var s_:SRankInfo = new SRankInfo();
			var dwValue:uint = bytes.readUnsignedInt();
			s_.dwValue = dwValue;
			var dwUpdateTime:uint = bytes.readUnsignedInt();
			s_.dwUpdateTime = dwUpdateTime;
			return s_;
		}

		public static function superFromByteArray(bytes:ByteArray):SRankInfo
		{
			var eType:uint = bytes.readUnsignedByte();
			var s:SRankInfo;
			switch(eType)
			{
				case EType_SRankInfo.eType_SRankInfo:
					s = SRankInfo.fromByteArray(bytes);
					break;
				case EType_SRankInfo.eType_SRoleHeadInfo:
					s = SRoleHeadInfo.fromByteArray(bytes);
					break;
				case EType_SRankInfo.eType_SRoleRankInfo:
					s = SRoleRankInfo.fromByteArray(bytes);
					break;
				case EType_SRankInfo.eType_SGuildRankInfo:
					s = SGuildRankInfo.fromByteArray(bytes);
					break;
				case EType_SRankInfo.eType_SRRBattlePointInfo:
					s = SRRBattlePointInfo.fromByteArray(bytes);
					break;
				case EType_SRankInfo.eType_SRRLevelInfo:
					s = SRRLevelInfo.fromByteArray(bytes);
					break;
				case EType_SRankInfo.eType_SRRFormationInfo:
					s = SRRFormationInfo.fromByteArray(bytes);
					break;
				case EType_SRankInfo.eType_SRRHeroFighterInfo:
					s = SRRHeroFighterInfo.fromByteArray(bytes);
					break;
				case EType_SRankInfo.eType_SRRTrumpInfo:
					s = SRRTrumpInfo.fromByteArray(bytes);
					break;
				case EType_SRankInfo.eType_SRRArenaInfo:
					s = SRRArenaInfo.fromByteArray(bytes);
					break;
				case EType_SRankInfo.eType_SGRBattleInfo:
					s = SGRBattleInfo.fromByteArray(bytes);
					break;
				case EType_SRankInfo.eType_SGRLevelInfo:
					s = SGRLevelInfo.fromByteArray(bytes);
					break;
				default:
					throw new Error("Unknown value for EType_SRankInfo:" + eType);
			}
			return s;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRankInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRankInfo> = new Vector.<SRankInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRankInfo = SRankInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public static function superVectorFromByteArray(bytes:ByteArray):Vector.<SRankInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRankInfo> = new Vector.<SRankInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRankInfo = SRankInfo.superFromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwValue);
			bytes.writeUnsignedInt(dwUpdateTime);
		}

		public function superToByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(getClassType());
			toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SRankInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRankInfo in vec)
				s.toByteArray(bytes);
		}

		public static function superVectorToByteArray(vec:Vector.<SRankInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRankInfo in vec)
				s.superToByteArray(bytes);
		}
	}
}
