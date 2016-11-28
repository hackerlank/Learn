/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SMonsterAppear.as
//  Purpose:      地图相关功能的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import net.protocol.battleGS.SFeatureBase;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 怪物的外观
	 */
	public final class SMonsterAppear
	{
		public var wMonsterID:uint; //(无符号16位整数)怪物ID
		public var strName:String; //怪物名称
		public var byLevel:uint; //(无符号8位整数)等级
		public var dwSpeed:uint; //(无符号32位整数)移动速度/200
		public var dwCurHP:uint; //(无符号32位整数)当前HP
		public var dwMaxHP:uint; //(无符号32位整数)最大HP
		public var byCamp:uint; //(无符号8位整数)阵营
		public var wGroup:uint; //(无符号16位整数)所属的组
		public var bySight:uint; //(无符号8位整数)视野
		public var bySightAngle:uint; //(无符号8位整数)视野角度
		public var byFindEnemy:uint; //(无符号8位整数)0,无目标：1有目标
		public var pFeature:SFeatureBase; //外观信息

		/**
		 * 辅助创建函数
		 */
		public static function create(wMonsterID:uint, strName:String, byLevel:uint, dwSpeed:uint, dwCurHP:uint, 
			dwMaxHP:uint, byCamp:uint, wGroup:uint, bySight:uint, bySightAngle:uint, 
			byFindEnemy:uint, pFeature:SFeatureBase):SMonsterAppear
		{
			var s_:SMonsterAppear = new SMonsterAppear();
			s_.wMonsterID = wMonsterID;
			s_.strName = strName;
			s_.byLevel = byLevel;
			s_.dwSpeed = dwSpeed;
			s_.dwCurHP = dwCurHP;
			s_.dwMaxHP = dwMaxHP;
			s_.byCamp = byCamp;
			s_.wGroup = wGroup;
			s_.bySight = bySight;
			s_.bySightAngle = bySightAngle;
			s_.byFindEnemy = byFindEnemy;
			s_.pFeature = pFeature;
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
				topXml = <SMonsterAppear _name_={name_} wMonsterID={wMonsterID} strName={strName} byLevel={byLevel} dwSpeed={dwSpeed} dwCurHP={dwCurHP}
				 dwMaxHP={dwMaxHP} byCamp={byCamp} wGroup={wGroup} bySight={bySight} bySightAngle={bySightAngle}
				 byFindEnemy={byFindEnemy}/>;
			else
				topXml = <SMonsterAppear wMonsterID={wMonsterID} strName={strName} byLevel={byLevel} dwSpeed={dwSpeed} dwCurHP={dwCurHP}
				 dwMaxHP={dwMaxHP} byCamp={byCamp} wGroup={wGroup} bySight={bySight} bySightAngle={bySightAngle}
				 byFindEnemy={byFindEnemy}/>;
			if(pFeature != null)
				topXml.appendChild(pFeature.toXML("pFeature"));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wMonsterID = wMonsterID;
			obj_.strName = strName;
			obj_.byLevel = byLevel;
			obj_.dwSpeed = dwSpeed;
			obj_.dwCurHP = dwCurHP;
			obj_.dwMaxHP = dwMaxHP;
			obj_.byCamp = byCamp;
			obj_.wGroup = wGroup;
			obj_.bySight = bySight;
			obj_.bySightAngle = bySightAngle;
			obj_.byFindEnemy = byFindEnemy;
			obj_.pFeature = pFeature;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SMonsterAppear
		{
			var s_:SMonsterAppear = new SMonsterAppear();
			var wMonsterID:uint = bytes.readUnsignedShort();
			s_.wMonsterID = wMonsterID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var dwSpeed:uint = bytes.readUnsignedInt();
			s_.dwSpeed = dwSpeed;
			var dwCurHP:uint = bytes.readUnsignedInt();
			s_.dwCurHP = dwCurHP;
			var dwMaxHP:uint = bytes.readUnsignedInt();
			s_.dwMaxHP = dwMaxHP;
			var byCamp:uint = bytes.readUnsignedByte();
			s_.byCamp = byCamp;
			var wGroup:uint = bytes.readUnsignedShort();
			s_.wGroup = wGroup;
			var bySight:uint = bytes.readUnsignedByte();
			s_.bySight = bySight;
			var bySightAngle:uint = bytes.readUnsignedByte();
			s_.bySightAngle = bySightAngle;
			var byFindEnemy:uint = bytes.readUnsignedByte();
			s_.byFindEnemy = byFindEnemy;
			var pFeature:SFeatureBase = SFeatureBase.superFromByteArray(bytes);
			s_.pFeature = pFeature;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SMonsterAppear>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SMonsterAppear> = new Vector.<SMonsterAppear>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SMonsterAppear = SMonsterAppear.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wMonsterID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeByte(byLevel);
			bytes.writeUnsignedInt(dwSpeed);
			bytes.writeUnsignedInt(dwCurHP);
			bytes.writeUnsignedInt(dwMaxHP);
			bytes.writeByte(byCamp);
			bytes.writeShort(wGroup);
			bytes.writeByte(bySight);
			bytes.writeByte(bySightAngle);
			bytes.writeByte(byFindEnemy);
			pFeature.superToByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SMonsterAppear>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SMonsterAppear in vec)
				s.toByteArray(bytes);
		}
	}
}
