/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBeauty.as
//  Purpose:      美女系统
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.beauty
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 美女信息
	 */
	public final class SBeauty
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家id
		public var wBeautyID:uint; //(无符号16位整数)美女id
		public var wBeautyLevel:uint; //(无符号16位整数)亲密等级
		public var dwBeautyExp:uint; //(无符号32位整数)亲密度
		public var wDayLoveType:uint; //(无符号16位整数)当天喜欢物品类型
		public var dwChatTime:uint; //(无符号32位整数)美女聊天cd(目前是共用cd次字段不用)
		public var dwPrizeExp:uint; //(无符号32位整数)已获得爱心的亲密度
		public var bFight:Boolean; //是否出战

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, wBeautyID:uint, wBeautyLevel:uint, dwBeautyExp:uint, wDayLoveType:uint, 
			dwChatTime:uint, dwPrizeExp:uint, bFight:Boolean):SBeauty
		{
			var s_:SBeauty = new SBeauty();
			s_.qwRoleID = qwRoleID;
			s_.wBeautyID = wBeautyID;
			s_.wBeautyLevel = wBeautyLevel;
			s_.dwBeautyExp = dwBeautyExp;
			s_.wDayLoveType = wDayLoveType;
			s_.dwChatTime = dwChatTime;
			s_.dwPrizeExp = dwPrizeExp;
			s_.bFight = bFight;
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
				topXml = <SBeauty _name_={name_} qwRoleID={qwRoleID} wBeautyID={wBeautyID} wBeautyLevel={wBeautyLevel} dwBeautyExp={dwBeautyExp} wDayLoveType={wDayLoveType}
				 dwChatTime={dwChatTime} dwPrizeExp={dwPrizeExp} bFight={bFight}/>;
			else
				topXml = <SBeauty qwRoleID={qwRoleID} wBeautyID={wBeautyID} wBeautyLevel={wBeautyLevel} dwBeautyExp={dwBeautyExp} wDayLoveType={wDayLoveType}
				 dwChatTime={dwChatTime} dwPrizeExp={dwPrizeExp} bFight={bFight}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.wBeautyID = wBeautyID;
			obj_.wBeautyLevel = wBeautyLevel;
			obj_.dwBeautyExp = dwBeautyExp;
			obj_.wDayLoveType = wDayLoveType;
			obj_.dwChatTime = dwChatTime;
			obj_.dwPrizeExp = dwPrizeExp;
			obj_.bFight = bFight;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBeauty
		{
			var s_:SBeauty = new SBeauty();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var wBeautyID:uint = bytes.readUnsignedShort();
			s_.wBeautyID = wBeautyID;
			var wBeautyLevel:uint = bytes.readUnsignedShort();
			s_.wBeautyLevel = wBeautyLevel;
			var dwBeautyExp:uint = bytes.readUnsignedInt();
			s_.dwBeautyExp = dwBeautyExp;
			var wDayLoveType:uint = bytes.readUnsignedShort();
			s_.wDayLoveType = wDayLoveType;
			var dwChatTime:uint = bytes.readUnsignedInt();
			s_.dwChatTime = dwChatTime;
			var dwPrizeExp:uint = bytes.readUnsignedInt();
			s_.dwPrizeExp = dwPrizeExp;
			var bFight:Boolean = bytes.readBoolean();
			s_.bFight = bFight;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBeauty>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBeauty> = new Vector.<SBeauty>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBeauty = SBeauty.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeShort(wBeautyID);
			bytes.writeShort(wBeautyLevel);
			bytes.writeUnsignedInt(dwBeautyExp);
			bytes.writeShort(wDayLoveType);
			bytes.writeUnsignedInt(dwChatTime);
			bytes.writeUnsignedInt(dwPrizeExp);
			bytes.writeBoolean(bFight);
		}

		public static function vectorToByteArray(vec:Vector.<SBeauty>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBeauty in vec)
				s.toByteArray(bytes);
		}
	}
}
