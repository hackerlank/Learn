/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFighterDBInfo.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 数据库同步到游戏服务器的将信息
	 */
	public final class SFighterDBInfo
	{
		public var qwInstID:BigInteger; //(无符号64位整数)将唯一ID
		public var qwRoleID:BigInteger; //(无符号64位整数)所属玩家ID
		public var wFighterID:uint; //(无符号16位整数)将类型ID
		public var byRecruited:uint; //(无符号8位整数)是否已招募
		public var byStar:uint; //(无符号8位整数)当前星级
		public var iSlot:int; //(有符号32位整数)将位置
		public var iPos:int; //(有符号32位整数)阵型中的位置
		public var fPotential:Number; //(Float)潜力
		public var fCapacity:Number; //(Float)资质
		public var byLevel:uint; //(无符号8位整数)等级
		public var qwExp:BigInteger; //(无符号64位整数)经验
		public var byLianPi:uint; //(无符号8位整数)炼皮
		public var byTongJin:uint; //(无符号8位整数)通筋
		public var byQiangJi:uint; //(无符号8位整数)强肌
		public var byDuanGu:uint; //(无符号8位整数)锻骨
		public var byHuoLuo:uint; //(无符号8位整数)活络
		public var byXiSui:uint; //(无符号8位整数)洗髓
		public var dwDujieExp:uint; //(无符号32位整数)散仙渡劫经验
		public var dwSpiritPower:uint; //(无符号32位整数)元神力

		/**
		 * 辅助创建函数
		 */
		public static function create(qwInstID:BigInteger, qwRoleID:BigInteger, wFighterID:uint, byRecruited:uint, byStar:uint, 
			iSlot:int, iPos:int, fPotential:Number, fCapacity:Number, byLevel:uint, 
			qwExp:BigInteger, byLianPi:uint, byTongJin:uint, byQiangJi:uint, byDuanGu:uint, 
			byHuoLuo:uint, byXiSui:uint, dwDujieExp:uint, dwSpiritPower:uint):SFighterDBInfo
		{
			var s_:SFighterDBInfo = new SFighterDBInfo();
			s_.qwInstID = qwInstID;
			s_.qwRoleID = qwRoleID;
			s_.wFighterID = wFighterID;
			s_.byRecruited = byRecruited;
			s_.byStar = byStar;
			s_.iSlot = iSlot;
			s_.iPos = iPos;
			s_.fPotential = fPotential;
			s_.fCapacity = fCapacity;
			s_.byLevel = byLevel;
			s_.qwExp = qwExp;
			s_.byLianPi = byLianPi;
			s_.byTongJin = byTongJin;
			s_.byQiangJi = byQiangJi;
			s_.byDuanGu = byDuanGu;
			s_.byHuoLuo = byHuoLuo;
			s_.byXiSui = byXiSui;
			s_.dwDujieExp = dwDujieExp;
			s_.dwSpiritPower = dwSpiritPower;
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
				topXml = <SFighterDBInfo _name_={name_} qwInstID={qwInstID} qwRoleID={qwRoleID} wFighterID={wFighterID} byRecruited={byRecruited} byStar={byStar}
				 iSlot={iSlot} iPos={iPos} fPotential={fPotential} fCapacity={fCapacity} byLevel={byLevel}
				 qwExp={qwExp} byLianPi={byLianPi} byTongJin={byTongJin} byQiangJi={byQiangJi} byDuanGu={byDuanGu}
				 byHuoLuo={byHuoLuo} byXiSui={byXiSui} dwDujieExp={dwDujieExp} dwSpiritPower={dwSpiritPower}/>;
			else
				topXml = <SFighterDBInfo qwInstID={qwInstID} qwRoleID={qwRoleID} wFighterID={wFighterID} byRecruited={byRecruited} byStar={byStar}
				 iSlot={iSlot} iPos={iPos} fPotential={fPotential} fCapacity={fCapacity} byLevel={byLevel}
				 qwExp={qwExp} byLianPi={byLianPi} byTongJin={byTongJin} byQiangJi={byQiangJi} byDuanGu={byDuanGu}
				 byHuoLuo={byHuoLuo} byXiSui={byXiSui} dwDujieExp={dwDujieExp} dwSpiritPower={dwSpiritPower}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwInstID = qwInstID;
			obj_.qwRoleID = qwRoleID;
			obj_.wFighterID = wFighterID;
			obj_.byRecruited = byRecruited;
			obj_.byStar = byStar;
			obj_.iSlot = iSlot;
			obj_.iPos = iPos;
			obj_.fPotential = fPotential;
			obj_.fCapacity = fCapacity;
			obj_.byLevel = byLevel;
			obj_.qwExp = qwExp;
			obj_.byLianPi = byLianPi;
			obj_.byTongJin = byTongJin;
			obj_.byQiangJi = byQiangJi;
			obj_.byDuanGu = byDuanGu;
			obj_.byHuoLuo = byHuoLuo;
			obj_.byXiSui = byXiSui;
			obj_.dwDujieExp = dwDujieExp;
			obj_.dwSpiritPower = dwSpiritPower;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFighterDBInfo
		{
			var s_:SFighterDBInfo = new SFighterDBInfo();
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInstID = qwInstID;
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var wFighterID:uint = bytes.readUnsignedShort();
			s_.wFighterID = wFighterID;
			var byRecruited:uint = bytes.readUnsignedByte();
			s_.byRecruited = byRecruited;
			var byStar:uint = bytes.readUnsignedByte();
			s_.byStar = byStar;
			var iSlot:int = bytes.readInt();
			s_.iSlot = iSlot;
			var iPos:int = bytes.readInt();
			s_.iPos = iPos;
			var fPotential:Number = bytes.readFloat();
			s_.fPotential = fPotential;
			var fCapacity:Number = bytes.readFloat();
			s_.fCapacity = fCapacity;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var qwExp:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwExp = qwExp;
			var byLianPi:uint = bytes.readUnsignedByte();
			s_.byLianPi = byLianPi;
			var byTongJin:uint = bytes.readUnsignedByte();
			s_.byTongJin = byTongJin;
			var byQiangJi:uint = bytes.readUnsignedByte();
			s_.byQiangJi = byQiangJi;
			var byDuanGu:uint = bytes.readUnsignedByte();
			s_.byDuanGu = byDuanGu;
			var byHuoLuo:uint = bytes.readUnsignedByte();
			s_.byHuoLuo = byHuoLuo;
			var byXiSui:uint = bytes.readUnsignedByte();
			s_.byXiSui = byXiSui;
			var dwDujieExp:uint = bytes.readUnsignedInt();
			s_.dwDujieExp = dwDujieExp;
			var dwSpiritPower:uint = bytes.readUnsignedInt();
			s_.dwSpiritPower = dwSpiritPower;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFighterDBInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFighterDBInfo> = new Vector.<SFighterDBInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFighterDBInfo = SFighterDBInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwInstID);
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeShort(wFighterID);
			bytes.writeByte(byRecruited);
			bytes.writeByte(byStar);
			bytes.writeInt(iSlot);
			bytes.writeInt(iPos);
			bytes.writeFloat(fPotential);
			bytes.writeFloat(fCapacity);
			bytes.writeByte(byLevel);
			BytesUtil.writeUInt64(bytes, qwExp);
			bytes.writeByte(byLianPi);
			bytes.writeByte(byTongJin);
			bytes.writeByte(byQiangJi);
			bytes.writeByte(byDuanGu);
			bytes.writeByte(byHuoLuo);
			bytes.writeByte(byXiSui);
			bytes.writeUnsignedInt(dwDujieExp);
			bytes.writeUnsignedInt(dwSpiritPower);
		}

		public static function vectorToByteArray(vec:Vector.<SFighterDBInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFighterDBInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
