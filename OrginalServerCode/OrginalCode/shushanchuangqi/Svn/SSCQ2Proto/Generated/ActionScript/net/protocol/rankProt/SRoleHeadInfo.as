/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRoleHeadInfo.as
//  Purpose:      排行榜相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.rankProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 魁首榜
	 */
	public final class SRoleHeadInfo extends SRankInfo
	{
		public var eType:uint; //(枚举类型：ERankType)排行榜类型
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var strName:String; //玩家姓名
		public var wID:uint; //(无符号16位整数)对应ID
		public var wPlayerFighterID:uint; //(无符号16位整数)主将ID
		public var byQuality:uint; //(无符号8位整数)主将品质(颜色)
		public var byInfoQuality:uint; //(无符号8位整数)魁首品质(颜色)
		public var strGuildName:String; //帮派名字

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SRankInfo.eType_SRoleHeadInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRoleHeadInfo _name_={name_} eType={eType} qwRoleID={qwRoleID} strName={strName} wID={wID} wPlayerFighterID={wPlayerFighterID}
				 byQuality={byQuality} byInfoQuality={byInfoQuality} strGuildName={strGuildName}/>;
			else
				topXml = <SRoleHeadInfo eType={eType} qwRoleID={qwRoleID} strName={strName} wID={wID} wPlayerFighterID={wPlayerFighterID}
				 byQuality={byQuality} byInfoQuality={byInfoQuality} strGuildName={strGuildName}/>;
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public override function copyTo(obj_:*):void
		{
			super.copyTo(obj_);
			obj_.eType = eType;
			obj_.qwRoleID = qwRoleID;
			obj_.strName = strName;
			obj_.wID = wID;
			obj_.wPlayerFighterID = wPlayerFighterID;
			obj_.byQuality = byQuality;
			obj_.byInfoQuality = byInfoQuality;
			obj_.strGuildName = strGuildName;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRoleHeadInfo
		{
			var s_:SRoleHeadInfo = new SRoleHeadInfo();
			var base_:SRankInfo = SRankInfo.fromByteArray(bytes);
			base_.copyTo(s_);
			var eType:uint = bytes.readUnsignedByte();
			s_.eType = eType;
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var wID:uint = bytes.readUnsignedShort();
			s_.wID = wID;
			var wPlayerFighterID:uint = bytes.readUnsignedShort();
			s_.wPlayerFighterID = wPlayerFighterID;
			var byQuality:uint = bytes.readUnsignedByte();
			s_.byQuality = byQuality;
			var byInfoQuality:uint = bytes.readUnsignedByte();
			s_.byInfoQuality = byInfoQuality;
			var strGuildName:String = BytesUtil.readString(bytes);
			s_.strGuildName = strGuildName;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRoleHeadInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRoleHeadInfo> = new Vector.<SRoleHeadInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRoleHeadInfo = SRoleHeadInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeByte(eType);
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeShort(wID);
			bytes.writeShort(wPlayerFighterID);
			bytes.writeByte(byQuality);
			bytes.writeByte(byInfoQuality);
			BytesUtil.writeString(bytes, strGuildName);
		}

		public static function vectorToByteArray(vec:Vector.<SRoleHeadInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRoleHeadInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
