/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPlayerAppear.as
//  Purpose:      地图相关功能的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import com.hurlant.math.BigInteger;
	import net.protocol.battleGS.SFeatureBase;
	import net.protocol.protoCommon.SPlatformParam;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 角色的外观
	 */
	public final class SPlayerAppear
	{
		public var strName:String; //角色名
		public var eCareer:uint; //(枚举类型：protoCommon.ECareerType)职业
		public var eSex:uint; //(枚举类型：protoCommon.ESexType)性别
		public var byLevel:uint; //(无符号8位整数)等级
		public var dwSpeed:uint; //(无符号32位整数)速度
		public var pFeature:SFeatureBase; //外观信息
		public var dwHorseID:uint; //(无符号32位整数)坐骑
		public var dwHorseLevel:uint; //(无符号32位整数)坐骑等级
		public var wPetID:uint; //(无符号16位整数)阵灵ID
		public var byPetLevel:uint; //(无符号8位整数)阵灵等级
		public var wBeautyID:uint; //(无符号16位整数)美女ID
		public var byBeautyLevel:uint; //(无符号8位整数)美女等级
		public var bIsSitting:uint; //(无符号8位整数)是否打坐0,没有打坐，1单修，2双修
		public var qwOtherSitID:BigInteger; //(无符号64位整数)双修玩家
		public var vecPlatforms:Vector.<SPlatformParam>; //平台信息

		/**
		 * 辅助创建函数
		 */
		public static function create(strName:String, eCareer:uint, eSex:uint, byLevel:uint, dwSpeed:uint, 
			pFeature:SFeatureBase, dwHorseID:uint, dwHorseLevel:uint, wPetID:uint, byPetLevel:uint, 
			wBeautyID:uint, byBeautyLevel:uint, bIsSitting:uint, qwOtherSitID:BigInteger, vecPlatforms:Vector.<SPlatformParam>):SPlayerAppear
		{
			var s_:SPlayerAppear = new SPlayerAppear();
			s_.strName = strName;
			s_.eCareer = eCareer;
			s_.eSex = eSex;
			s_.byLevel = byLevel;
			s_.dwSpeed = dwSpeed;
			s_.pFeature = pFeature;
			s_.dwHorseID = dwHorseID;
			s_.dwHorseLevel = dwHorseLevel;
			s_.wPetID = wPetID;
			s_.byPetLevel = byPetLevel;
			s_.wBeautyID = wBeautyID;
			s_.byBeautyLevel = byBeautyLevel;
			s_.bIsSitting = bIsSitting;
			s_.qwOtherSitID = qwOtherSitID;
			s_.vecPlatforms = vecPlatforms;
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
				topXml = <SPlayerAppear _name_={name_} strName={strName} eCareer={eCareer} eSex={eSex} byLevel={byLevel} dwSpeed={dwSpeed} dwHorseID={dwHorseID} dwHorseLevel={dwHorseLevel} wPetID={wPetID} byPetLevel={byPetLevel}
				 wBeautyID={wBeautyID} byBeautyLevel={byBeautyLevel} bIsSitting={bIsSitting} qwOtherSitID={qwOtherSitID}/>;
			else
				topXml = <SPlayerAppear strName={strName} eCareer={eCareer} eSex={eSex} byLevel={byLevel} dwSpeed={dwSpeed} dwHorseID={dwHorseID} dwHorseLevel={dwHorseLevel} wPetID={wPetID} byPetLevel={byPetLevel}
				 wBeautyID={wBeautyID} byBeautyLevel={byBeautyLevel} bIsSitting={bIsSitting} qwOtherSitID={qwOtherSitID}/>;
			if(pFeature != null)
				topXml.appendChild(pFeature.toXML("pFeature"));
			if(vecPlatforms != null)
			{
				var vecPlatformsXml:XML = <Vec_SPlatformParam _name_="vecPlatforms"/>;
				for each(var s2:SPlatformParam in vecPlatforms)
					vecPlatformsXml.appendChild(s2.toXML());
				topXml.appendChild(vecPlatformsXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.strName = strName;
			obj_.eCareer = eCareer;
			obj_.eSex = eSex;
			obj_.byLevel = byLevel;
			obj_.dwSpeed = dwSpeed;
			obj_.pFeature = pFeature;
			obj_.dwHorseID = dwHorseID;
			obj_.dwHorseLevel = dwHorseLevel;
			obj_.wPetID = wPetID;
			obj_.byPetLevel = byPetLevel;
			obj_.wBeautyID = wBeautyID;
			obj_.byBeautyLevel = byBeautyLevel;
			obj_.bIsSitting = bIsSitting;
			obj_.qwOtherSitID = qwOtherSitID;
			obj_.vecPlatforms = vecPlatforms;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPlayerAppear
		{
			var s_:SPlayerAppear = new SPlayerAppear();
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var eCareer:uint = bytes.readUnsignedByte();
			s_.eCareer = eCareer;
			var eSex:uint = bytes.readUnsignedByte();
			s_.eSex = eSex;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var dwSpeed:uint = bytes.readUnsignedInt();
			s_.dwSpeed = dwSpeed;
			var pFeature:SFeatureBase = SFeatureBase.superFromByteArray(bytes);
			s_.pFeature = pFeature;
			var dwHorseID:uint = bytes.readUnsignedInt();
			s_.dwHorseID = dwHorseID;
			var dwHorseLevel:uint = bytes.readUnsignedInt();
			s_.dwHorseLevel = dwHorseLevel;
			var wPetID:uint = bytes.readUnsignedShort();
			s_.wPetID = wPetID;
			var byPetLevel:uint = bytes.readUnsignedByte();
			s_.byPetLevel = byPetLevel;
			var wBeautyID:uint = bytes.readUnsignedShort();
			s_.wBeautyID = wBeautyID;
			var byBeautyLevel:uint = bytes.readUnsignedByte();
			s_.byBeautyLevel = byBeautyLevel;
			var bIsSitting:uint = bytes.readUnsignedByte();
			s_.bIsSitting = bIsSitting;
			var qwOtherSitID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwOtherSitID = qwOtherSitID;
			var vecPlatforms:Vector.<SPlatformParam> = SPlatformParam.vectorFromByteArray(bytes);
			s_.vecPlatforms = vecPlatforms;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPlayerAppear>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPlayerAppear> = new Vector.<SPlayerAppear>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPlayerAppear = SPlayerAppear.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeString(bytes, strName);
			bytes.writeByte(eCareer);
			bytes.writeByte(eSex);
			bytes.writeByte(byLevel);
			bytes.writeUnsignedInt(dwSpeed);
			pFeature.superToByteArray(bytes);
			bytes.writeUnsignedInt(dwHorseID);
			bytes.writeUnsignedInt(dwHorseLevel);
			bytes.writeShort(wPetID);
			bytes.writeByte(byPetLevel);
			bytes.writeShort(wBeautyID);
			bytes.writeByte(byBeautyLevel);
			bytes.writeByte(bIsSitting);
			BytesUtil.writeUInt64(bytes, qwOtherSitID);
			SPlatformParam.vectorToByteArray(vecPlatforms, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SPlayerAppear>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPlayerAppear in vec)
				s.toByteArray(bytes);
		}
	}
}
