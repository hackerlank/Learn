/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFighterBaseInfo.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 战斗者除了外观之外的杂七杂八的基本信息
	 */
	public final class SFighterBaseInfo
	{
		public var qwInstID:BigInteger; //(无符号64位整数)将唯一ID
		public var wFighterID:uint; //(无符号16位整数)将类型ID
		public var byRecruited:uint; //(无符号8位整数)是否已招募
		public var byStar:uint; //(无符号8位整数)当前星级
		public var iSlot:int; //(有符号32位整数)将位置
		public var iPos:int; //(有符号32位整数)阵型中的位置
		public var byLevel:uint; //(无符号8位整数)等级
		public var qwExp:BigInteger; //(无符号64位整数)总经验
		public var strName:String; //将名字
		public var dwHpMax:uint; //(无符号32位整数)最大血量
		public var dwHp:uint; //(无符号32位整数)当前血量
		public var dwAura:uint; //(无符号32位整数)当前灵气
		public var dwAuraMax:uint; //(无符号32位整数)最大灵气
		public var byLianPi:uint; //(无符号8位整数)炼皮
		public var byTongJin:uint; //(无符号8位整数)通筋
		public var byQiangJi:uint; //(无符号8位整数)强肌
		public var byDuanGu:uint; //(无符号8位整数)锻骨
		public var byHuoLuo:uint; //(无符号8位整数)活络
		public var byXiSui:uint; //(无符号8位整数)洗髓
		public var byDujieLevel:uint; //(无符号8位整数)散仙渡劫等级
		public var dwDujieExp:uint; //(无符号32位整数)散仙渡劫经验
		public var byQuality:uint; //(无符号8位整数)散仙品质(颜色)
		public var dwSpiritPower:uint; //(无符号32位整数)元神力

		/**
		 * 辅助创建函数
		 */
		public static function create(qwInstID:BigInteger, wFighterID:uint, byRecruited:uint, byStar:uint, iSlot:int, 
			iPos:int, byLevel:uint, qwExp:BigInteger, strName:String, dwHpMax:uint, 
			dwHp:uint, dwAura:uint, dwAuraMax:uint, byLianPi:uint, byTongJin:uint, 
			byQiangJi:uint, byDuanGu:uint, byHuoLuo:uint, byXiSui:uint, byDujieLevel:uint, 
			dwDujieExp:uint, byQuality:uint, dwSpiritPower:uint):SFighterBaseInfo
		{
			var s_:SFighterBaseInfo = new SFighterBaseInfo();
			s_.qwInstID = qwInstID;
			s_.wFighterID = wFighterID;
			s_.byRecruited = byRecruited;
			s_.byStar = byStar;
			s_.iSlot = iSlot;
			s_.iPos = iPos;
			s_.byLevel = byLevel;
			s_.qwExp = qwExp;
			s_.strName = strName;
			s_.dwHpMax = dwHpMax;
			s_.dwHp = dwHp;
			s_.dwAura = dwAura;
			s_.dwAuraMax = dwAuraMax;
			s_.byLianPi = byLianPi;
			s_.byTongJin = byTongJin;
			s_.byQiangJi = byQiangJi;
			s_.byDuanGu = byDuanGu;
			s_.byHuoLuo = byHuoLuo;
			s_.byXiSui = byXiSui;
			s_.byDujieLevel = byDujieLevel;
			s_.dwDujieExp = dwDujieExp;
			s_.byQuality = byQuality;
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
				topXml = <SFighterBaseInfo _name_={name_} qwInstID={qwInstID} wFighterID={wFighterID} byRecruited={byRecruited} byStar={byStar} iSlot={iSlot}
				 iPos={iPos} byLevel={byLevel} qwExp={qwExp} strName={strName} dwHpMax={dwHpMax}
				 dwHp={dwHp} dwAura={dwAura} dwAuraMax={dwAuraMax} byLianPi={byLianPi} byTongJin={byTongJin}
				 byQiangJi={byQiangJi} byDuanGu={byDuanGu} byHuoLuo={byHuoLuo} byXiSui={byXiSui} byDujieLevel={byDujieLevel}
				 dwDujieExp={dwDujieExp} byQuality={byQuality} dwSpiritPower={dwSpiritPower}/>;
			else
				topXml = <SFighterBaseInfo qwInstID={qwInstID} wFighterID={wFighterID} byRecruited={byRecruited} byStar={byStar} iSlot={iSlot}
				 iPos={iPos} byLevel={byLevel} qwExp={qwExp} strName={strName} dwHpMax={dwHpMax}
				 dwHp={dwHp} dwAura={dwAura} dwAuraMax={dwAuraMax} byLianPi={byLianPi} byTongJin={byTongJin}
				 byQiangJi={byQiangJi} byDuanGu={byDuanGu} byHuoLuo={byHuoLuo} byXiSui={byXiSui} byDujieLevel={byDujieLevel}
				 dwDujieExp={dwDujieExp} byQuality={byQuality} dwSpiritPower={dwSpiritPower}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwInstID = qwInstID;
			obj_.wFighterID = wFighterID;
			obj_.byRecruited = byRecruited;
			obj_.byStar = byStar;
			obj_.iSlot = iSlot;
			obj_.iPos = iPos;
			obj_.byLevel = byLevel;
			obj_.qwExp = qwExp;
			obj_.strName = strName;
			obj_.dwHpMax = dwHpMax;
			obj_.dwHp = dwHp;
			obj_.dwAura = dwAura;
			obj_.dwAuraMax = dwAuraMax;
			obj_.byLianPi = byLianPi;
			obj_.byTongJin = byTongJin;
			obj_.byQiangJi = byQiangJi;
			obj_.byDuanGu = byDuanGu;
			obj_.byHuoLuo = byHuoLuo;
			obj_.byXiSui = byXiSui;
			obj_.byDujieLevel = byDujieLevel;
			obj_.dwDujieExp = dwDujieExp;
			obj_.byQuality = byQuality;
			obj_.dwSpiritPower = dwSpiritPower;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFighterBaseInfo
		{
			var s_:SFighterBaseInfo = new SFighterBaseInfo();
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInstID = qwInstID;
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
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var qwExp:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwExp = qwExp;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var dwHpMax:uint = bytes.readUnsignedInt();
			s_.dwHpMax = dwHpMax;
			var dwHp:uint = bytes.readUnsignedInt();
			s_.dwHp = dwHp;
			var dwAura:uint = bytes.readUnsignedInt();
			s_.dwAura = dwAura;
			var dwAuraMax:uint = bytes.readUnsignedInt();
			s_.dwAuraMax = dwAuraMax;
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
			var byDujieLevel:uint = bytes.readUnsignedByte();
			s_.byDujieLevel = byDujieLevel;
			var dwDujieExp:uint = bytes.readUnsignedInt();
			s_.dwDujieExp = dwDujieExp;
			var byQuality:uint = bytes.readUnsignedByte();
			s_.byQuality = byQuality;
			var dwSpiritPower:uint = bytes.readUnsignedInt();
			s_.dwSpiritPower = dwSpiritPower;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFighterBaseInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFighterBaseInfo> = new Vector.<SFighterBaseInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFighterBaseInfo = SFighterBaseInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwInstID);
			bytes.writeShort(wFighterID);
			bytes.writeByte(byRecruited);
			bytes.writeByte(byStar);
			bytes.writeInt(iSlot);
			bytes.writeInt(iPos);
			bytes.writeByte(byLevel);
			BytesUtil.writeUInt64(bytes, qwExp);
			BytesUtil.writeString(bytes, strName);
			bytes.writeUnsignedInt(dwHpMax);
			bytes.writeUnsignedInt(dwHp);
			bytes.writeUnsignedInt(dwAura);
			bytes.writeUnsignedInt(dwAuraMax);
			bytes.writeByte(byLianPi);
			bytes.writeByte(byTongJin);
			bytes.writeByte(byQiangJi);
			bytes.writeByte(byDuanGu);
			bytes.writeByte(byHuoLuo);
			bytes.writeByte(byXiSui);
			bytes.writeByte(byDujieLevel);
			bytes.writeUnsignedInt(dwDujieExp);
			bytes.writeByte(byQuality);
			bytes.writeUnsignedInt(dwSpiritPower);
		}

		public static function vectorToByteArray(vec:Vector.<SFighterBaseInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFighterBaseInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
