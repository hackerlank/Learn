/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SAchievementShare.as
//  Purpose:      成就相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.achievementProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 成就分享列表
	 */
	public final class SAchievementShare
	{
		public var wAchievementID:uint; //(无符号16位整数)成就ID
		public var eProcess:uint; //(枚举类型：EAchievementProcess)分享状态

		/**
		 * 辅助创建函数
		 */
		public static function create(wAchievementID:uint, eProcess:uint):SAchievementShare
		{
			var s_:SAchievementShare = new SAchievementShare();
			s_.wAchievementID = wAchievementID;
			s_.eProcess = eProcess;
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
				topXml = <SAchievementShare _name_={name_} wAchievementID={wAchievementID} eProcess={eProcess}/>;
			else
				topXml = <SAchievementShare wAchievementID={wAchievementID} eProcess={eProcess}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wAchievementID = wAchievementID;
			obj_.eProcess = eProcess;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SAchievementShare
		{
			var s_:SAchievementShare = new SAchievementShare();
			var wAchievementID:uint = bytes.readUnsignedShort();
			s_.wAchievementID = wAchievementID;
			var eProcess:uint = bytes.readUnsignedByte();
			s_.eProcess = eProcess;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SAchievementShare>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SAchievementShare> = new Vector.<SAchievementShare>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SAchievementShare = SAchievementShare.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wAchievementID);
			bytes.writeByte(eProcess);
		}

		public static function vectorToByteArray(vec:Vector.<SAchievementShare>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SAchievementShare in vec)
				s.toByteArray(bytes);
		}
	}
}
