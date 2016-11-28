/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGuildBaseInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派基本信息
	 */
	public final class SGuildBaseInfo extends SGuildInfoBase
	{
		public var strName:String; //帮派名称
		public var qwOwnerID:BigInteger; //(无符号64位整数)帮主角色ID
		public var strOwnerName:String; //帮主名称
		public var strInfo:String; //帮派公告
		public var qwQQGroupID:BigInteger; //(无符号64位整数)帮派Q群群号
		public var wUserCount:uint; //(无符号16位整数)成员数量
		public var wMaxUserCount:uint; //(无符号16位整数)最大成员数量
		public var dwMoney:uint; //(无符号32位整数)帮派资金
		public var eSelfRank:uint; //(枚举类型：EMemberRank)本人职位
		public var dwContribution:uint; //(无符号32位整数)本人贡献值
		public var dwRemainDonate:uint; //(无符号32位整数)剩余捐献额
		public var wPlayerFighterID:uint; //(无符号16位整数)帮主ID
		public var byQuality:uint; //(无符号8位整数)帮主品质
		public var dwScore:uint; //(无符号32位整数)天元神兽积分
		public var dwCount:uint; //(无符号32位整数)帮派所有成员兑换物品数量
		public var strLingShan:String; //占领灵山

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SGuildInfoBase.eType_SGuildBaseInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SGuildBaseInfo _name_={name_} strName={strName} qwOwnerID={qwOwnerID} strOwnerName={strOwnerName} strInfo={strInfo} qwQQGroupID={qwQQGroupID}
				 wUserCount={wUserCount} wMaxUserCount={wMaxUserCount} dwMoney={dwMoney} eSelfRank={eSelfRank} dwContribution={dwContribution}
				 dwRemainDonate={dwRemainDonate} wPlayerFighterID={wPlayerFighterID} byQuality={byQuality} dwScore={dwScore} dwCount={dwCount}
				 strLingShan={strLingShan}/>;
			else
				topXml = <SGuildBaseInfo strName={strName} qwOwnerID={qwOwnerID} strOwnerName={strOwnerName} strInfo={strInfo} qwQQGroupID={qwQQGroupID}
				 wUserCount={wUserCount} wMaxUserCount={wMaxUserCount} dwMoney={dwMoney} eSelfRank={eSelfRank} dwContribution={dwContribution}
				 dwRemainDonate={dwRemainDonate} wPlayerFighterID={wPlayerFighterID} byQuality={byQuality} dwScore={dwScore} dwCount={dwCount}
				 strLingShan={strLingShan}/>;
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
			obj_.strName = strName;
			obj_.qwOwnerID = qwOwnerID;
			obj_.strOwnerName = strOwnerName;
			obj_.strInfo = strInfo;
			obj_.qwQQGroupID = qwQQGroupID;
			obj_.wUserCount = wUserCount;
			obj_.wMaxUserCount = wMaxUserCount;
			obj_.dwMoney = dwMoney;
			obj_.eSelfRank = eSelfRank;
			obj_.dwContribution = dwContribution;
			obj_.dwRemainDonate = dwRemainDonate;
			obj_.wPlayerFighterID = wPlayerFighterID;
			obj_.byQuality = byQuality;
			obj_.dwScore = dwScore;
			obj_.dwCount = dwCount;
			obj_.strLingShan = strLingShan;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGuildBaseInfo
		{
			var s_:SGuildBaseInfo = new SGuildBaseInfo();
			var base_:SGuildInfoBase = SGuildInfoBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var qwOwnerID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwOwnerID = qwOwnerID;
			var strOwnerName:String = BytesUtil.readString(bytes);
			s_.strOwnerName = strOwnerName;
			var strInfo:String = BytesUtil.readString(bytes);
			s_.strInfo = strInfo;
			var qwQQGroupID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwQQGroupID = qwQQGroupID;
			var wUserCount:uint = bytes.readUnsignedShort();
			s_.wUserCount = wUserCount;
			var wMaxUserCount:uint = bytes.readUnsignedShort();
			s_.wMaxUserCount = wMaxUserCount;
			var dwMoney:uint = bytes.readUnsignedInt();
			s_.dwMoney = dwMoney;
			var eSelfRank:uint = bytes.readUnsignedByte();
			s_.eSelfRank = eSelfRank;
			var dwContribution:uint = bytes.readUnsignedInt();
			s_.dwContribution = dwContribution;
			var dwRemainDonate:uint = bytes.readUnsignedInt();
			s_.dwRemainDonate = dwRemainDonate;
			var wPlayerFighterID:uint = bytes.readUnsignedShort();
			s_.wPlayerFighterID = wPlayerFighterID;
			var byQuality:uint = bytes.readUnsignedByte();
			s_.byQuality = byQuality;
			var dwScore:uint = bytes.readUnsignedInt();
			s_.dwScore = dwScore;
			var dwCount:uint = bytes.readUnsignedInt();
			s_.dwCount = dwCount;
			var strLingShan:String = BytesUtil.readString(bytes);
			s_.strLingShan = strLingShan;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGuildBaseInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildBaseInfo> = new Vector.<SGuildBaseInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildBaseInfo = SGuildBaseInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			BytesUtil.writeString(bytes, strName);
			BytesUtil.writeUInt64(bytes, qwOwnerID);
			BytesUtil.writeString(bytes, strOwnerName);
			BytesUtil.writeString(bytes, strInfo);
			BytesUtil.writeUInt64(bytes, qwQQGroupID);
			bytes.writeShort(wUserCount);
			bytes.writeShort(wMaxUserCount);
			bytes.writeUnsignedInt(dwMoney);
			bytes.writeByte(eSelfRank);
			bytes.writeUnsignedInt(dwContribution);
			bytes.writeUnsignedInt(dwRemainDonate);
			bytes.writeShort(wPlayerFighterID);
			bytes.writeByte(byQuality);
			bytes.writeUnsignedInt(dwScore);
			bytes.writeUnsignedInt(dwCount);
			BytesUtil.writeString(bytes, strLingShan);
		}

		public static function vectorToByteArray(vec:Vector.<SGuildBaseInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildBaseInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
