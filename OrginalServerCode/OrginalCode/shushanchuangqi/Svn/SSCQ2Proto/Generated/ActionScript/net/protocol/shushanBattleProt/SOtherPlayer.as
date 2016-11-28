/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SOtherPlayer.as
//  Purpose:      蜀山论剑相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanBattleProt
{
	import com.hurlant.math.BigInteger;
	import net.protocol.mapProt.SPlayerAppear;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 对方玩家数据结构
	 */
	public final class SOtherPlayer
	{
		public var qwRoleIDOther:BigInteger; //(无符号64位整数)对方玩家ID
		public var byCurrKillOther:uint; //(无符号8位整数)对方当前连杀数
		public var wHonorOther:uint; //(无符号16位整数)对方总荣誉值
		public var wSkillFlagsOther:uint; //(无符号16位整数)对方技能使用位域,对应位表示技能是否已使用(低8位)
		public var dwMaxHpOther:uint; //(无符号32位整数)对方总血量
		public var dwCurHpOther:uint; //(无符号32位整数)对方当前血量
		public var dwBattlePowerOther:uint; //(无符号32位整数)对方总战斗力
		public var rPlayerAppear:SPlayerAppear; //对方玩家的外观

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleIDOther:BigInteger, byCurrKillOther:uint, wHonorOther:uint, wSkillFlagsOther:uint, dwMaxHpOther:uint, 
			dwCurHpOther:uint, dwBattlePowerOther:uint, rPlayerAppear:SPlayerAppear):SOtherPlayer
		{
			var s_:SOtherPlayer = new SOtherPlayer();
			s_.qwRoleIDOther = qwRoleIDOther;
			s_.byCurrKillOther = byCurrKillOther;
			s_.wHonorOther = wHonorOther;
			s_.wSkillFlagsOther = wSkillFlagsOther;
			s_.dwMaxHpOther = dwMaxHpOther;
			s_.dwCurHpOther = dwCurHpOther;
			s_.dwBattlePowerOther = dwBattlePowerOther;
			s_.rPlayerAppear = rPlayerAppear;
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
				topXml = <SOtherPlayer _name_={name_} qwRoleIDOther={qwRoleIDOther} byCurrKillOther={byCurrKillOther} wHonorOther={wHonorOther} wSkillFlagsOther={wSkillFlagsOther} dwMaxHpOther={dwMaxHpOther}
				 dwCurHpOther={dwCurHpOther} dwBattlePowerOther={dwBattlePowerOther}/>;
			else
				topXml = <SOtherPlayer qwRoleIDOther={qwRoleIDOther} byCurrKillOther={byCurrKillOther} wHonorOther={wHonorOther} wSkillFlagsOther={wSkillFlagsOther} dwMaxHpOther={dwMaxHpOther}
				 dwCurHpOther={dwCurHpOther} dwBattlePowerOther={dwBattlePowerOther}/>;
			if(rPlayerAppear != null)
				topXml.appendChild(rPlayerAppear.toXML("rPlayerAppear"));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleIDOther = qwRoleIDOther;
			obj_.byCurrKillOther = byCurrKillOther;
			obj_.wHonorOther = wHonorOther;
			obj_.wSkillFlagsOther = wSkillFlagsOther;
			obj_.dwMaxHpOther = dwMaxHpOther;
			obj_.dwCurHpOther = dwCurHpOther;
			obj_.dwBattlePowerOther = dwBattlePowerOther;
			obj_.rPlayerAppear = rPlayerAppear;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SOtherPlayer
		{
			var s_:SOtherPlayer = new SOtherPlayer();
			var qwRoleIDOther:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleIDOther = qwRoleIDOther;
			var byCurrKillOther:uint = bytes.readUnsignedByte();
			s_.byCurrKillOther = byCurrKillOther;
			var wHonorOther:uint = bytes.readUnsignedShort();
			s_.wHonorOther = wHonorOther;
			var wSkillFlagsOther:uint = bytes.readUnsignedShort();
			s_.wSkillFlagsOther = wSkillFlagsOther;
			var dwMaxHpOther:uint = bytes.readUnsignedInt();
			s_.dwMaxHpOther = dwMaxHpOther;
			var dwCurHpOther:uint = bytes.readUnsignedInt();
			s_.dwCurHpOther = dwCurHpOther;
			var dwBattlePowerOther:uint = bytes.readUnsignedInt();
			s_.dwBattlePowerOther = dwBattlePowerOther;
			var rPlayerAppear:SPlayerAppear = SPlayerAppear.fromByteArray(bytes);
			s_.rPlayerAppear = rPlayerAppear;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SOtherPlayer>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SOtherPlayer> = new Vector.<SOtherPlayer>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SOtherPlayer = SOtherPlayer.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleIDOther);
			bytes.writeByte(byCurrKillOther);
			bytes.writeShort(wHonorOther);
			bytes.writeShort(wSkillFlagsOther);
			bytes.writeUnsignedInt(dwMaxHpOther);
			bytes.writeUnsignedInt(dwCurHpOther);
			bytes.writeUnsignedInt(dwBattlePowerOther);
			rPlayerAppear.toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SOtherPlayer>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SOtherPlayer in vec)
				s.toByteArray(bytes);
		}
	}
}
