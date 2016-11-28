/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFlauntAchievement.as
//  Purpose:      全局聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.globalChatProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 成就炫耀信息
	 */
	public final class SFlauntAchievement
	{
		public var qwInstID:BigInteger; //(无符号64位整数)成就唯一ID
		public var wAchievementID:uint; //(无符号16位整数)成就ID

		/**
		 * 辅助创建函数
		 */
		public static function create(qwInstID:BigInteger, wAchievementID:uint):SFlauntAchievement
		{
			var s_:SFlauntAchievement = new SFlauntAchievement();
			s_.qwInstID = qwInstID;
			s_.wAchievementID = wAchievementID;
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
				topXml = <SFlauntAchievement _name_={name_} qwInstID={qwInstID} wAchievementID={wAchievementID}/>;
			else
				topXml = <SFlauntAchievement qwInstID={qwInstID} wAchievementID={wAchievementID}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwInstID = qwInstID;
			obj_.wAchievementID = wAchievementID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFlauntAchievement
		{
			var s_:SFlauntAchievement = new SFlauntAchievement();
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInstID = qwInstID;
			var wAchievementID:uint = bytes.readUnsignedShort();
			s_.wAchievementID = wAchievementID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFlauntAchievement>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFlauntAchievement> = new Vector.<SFlauntAchievement>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFlauntAchievement = SFlauntAchievement.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwInstID);
			bytes.writeShort(wAchievementID);
		}

		public static function vectorToByteArray(vec:Vector.<SFlauntAchievement>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFlauntAchievement in vec)
				s.toByteArray(bytes);
		}
	}
}
