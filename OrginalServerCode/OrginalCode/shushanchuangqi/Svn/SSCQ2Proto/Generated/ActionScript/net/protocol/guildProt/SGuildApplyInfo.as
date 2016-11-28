/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGuildApplyInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派申请列表信息
	 */
	public final class SGuildApplyInfo extends SGuildInfoBase
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var strName:String; //玩家姓名
		public var wLevel:uint; //(无符号16位整数)玩家等级
		public var dwBattlePoint:uint; //(无符号32位整数)玩家战斗力

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SGuildInfoBase.eType_SGuildApplyInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SGuildApplyInfo _name_={name_} qwRoleID={qwRoleID} strName={strName} wLevel={wLevel} dwBattlePoint={dwBattlePoint}/>;
			else
				topXml = <SGuildApplyInfo qwRoleID={qwRoleID} strName={strName} wLevel={wLevel} dwBattlePoint={dwBattlePoint}/>;
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
			obj_.qwRoleID = qwRoleID;
			obj_.strName = strName;
			obj_.wLevel = wLevel;
			obj_.dwBattlePoint = dwBattlePoint;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGuildApplyInfo
		{
			var s_:SGuildApplyInfo = new SGuildApplyInfo();
			var base_:SGuildInfoBase = SGuildInfoBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var wLevel:uint = bytes.readUnsignedShort();
			s_.wLevel = wLevel;
			var dwBattlePoint:uint = bytes.readUnsignedInt();
			s_.dwBattlePoint = dwBattlePoint;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGuildApplyInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildApplyInfo> = new Vector.<SGuildApplyInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildApplyInfo = SGuildApplyInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeShort(wLevel);
			bytes.writeUnsignedInt(dwBattlePoint);
		}

		public static function vectorToByteArray(vec:Vector.<SGuildApplyInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildApplyInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
