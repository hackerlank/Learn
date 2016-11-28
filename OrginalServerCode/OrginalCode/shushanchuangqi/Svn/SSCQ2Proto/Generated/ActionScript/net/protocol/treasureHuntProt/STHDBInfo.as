/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STHDBInfo.as
//  Purpose:      寻宝协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.treasureHuntProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 寻宝DB信息
	 */
	public final class STHDBInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)RoleID
		public var byCopyID:uint; //(无符号8位整数)副本ID
		public var byStatus:uint; //(无符号8位整数)寻宝状态（1：正在进行；2：结束，等待领取奖品）
		public var dwBossCurHP:uint; //(无符号32位整数)Boss当前血量
		public var dwLastTime:uint; //(无符号32位整数)攻打上一波怪时间
		public var dwTime:uint; //(无符号32位整数)寻宝累计时间
		public var dwNum:uint; //(无符号32位整数)寻宝累计波数
		public var strAward:String; //寻宝奖励

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, byCopyID:uint, byStatus:uint, dwBossCurHP:uint, dwLastTime:uint, 
			dwTime:uint, dwNum:uint, strAward:String):STHDBInfo
		{
			var s_:STHDBInfo = new STHDBInfo();
			s_.qwRoleID = qwRoleID;
			s_.byCopyID = byCopyID;
			s_.byStatus = byStatus;
			s_.dwBossCurHP = dwBossCurHP;
			s_.dwLastTime = dwLastTime;
			s_.dwTime = dwTime;
			s_.dwNum = dwNum;
			s_.strAward = strAward;
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
				topXml = <STHDBInfo _name_={name_} qwRoleID={qwRoleID} byCopyID={byCopyID} byStatus={byStatus} dwBossCurHP={dwBossCurHP} dwLastTime={dwLastTime}
				 dwTime={dwTime} dwNum={dwNum} strAward={strAward}/>;
			else
				topXml = <STHDBInfo qwRoleID={qwRoleID} byCopyID={byCopyID} byStatus={byStatus} dwBossCurHP={dwBossCurHP} dwLastTime={dwLastTime}
				 dwTime={dwTime} dwNum={dwNum} strAward={strAward}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.byCopyID = byCopyID;
			obj_.byStatus = byStatus;
			obj_.dwBossCurHP = dwBossCurHP;
			obj_.dwLastTime = dwLastTime;
			obj_.dwTime = dwTime;
			obj_.dwNum = dwNum;
			obj_.strAward = strAward;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STHDBInfo
		{
			var s_:STHDBInfo = new STHDBInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var byCopyID:uint = bytes.readUnsignedByte();
			s_.byCopyID = byCopyID;
			var byStatus:uint = bytes.readUnsignedByte();
			s_.byStatus = byStatus;
			var dwBossCurHP:uint = bytes.readUnsignedInt();
			s_.dwBossCurHP = dwBossCurHP;
			var dwLastTime:uint = bytes.readUnsignedInt();
			s_.dwLastTime = dwLastTime;
			var dwTime:uint = bytes.readUnsignedInt();
			s_.dwTime = dwTime;
			var dwNum:uint = bytes.readUnsignedInt();
			s_.dwNum = dwNum;
			var strAward:String = BytesUtil.readString(bytes);
			s_.strAward = strAward;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STHDBInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STHDBInfo> = new Vector.<STHDBInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STHDBInfo = STHDBInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeByte(byCopyID);
			bytes.writeByte(byStatus);
			bytes.writeUnsignedInt(dwBossCurHP);
			bytes.writeUnsignedInt(dwLastTime);
			bytes.writeUnsignedInt(dwTime);
			bytes.writeUnsignedInt(dwNum);
			BytesUtil.writeString(bytes, strAward);
		}

		public static function vectorToByteArray(vec:Vector.<STHDBInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STHDBInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
