/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEnterParam.as
//  Purpose:      角色信息相关操作协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEnterGameProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 角色信息
	 */
	public final class SEnterParam
	{
		public var byPtType:uint; //(枚举类型：protoCommon.EPtType)平台类型
		public var byQQPtType:uint; //(枚举类型：protoCommon.EQQPtType)QQ平台类型
		public var byQQPtLv:uint; //(无符号8位整数)QQ平台类型等级
		public var byQQPtYearType:uint; //(无符号8位整数)是否年费
		public var byQQPtLuxuryType:uint; //(无符号8位整数)是否豪华
		public var customPar1:String; //广告主来源
		public var customPar2:String; //广告次来源
		public var strOpenId:String; //openID
		public var strOpenKey:String; //openKey

		/**
		 * 辅助创建函数
		 */
		public static function create(byPtType:uint, byQQPtType:uint, byQQPtLv:uint, byQQPtYearType:uint, byQQPtLuxuryType:uint, 
			customPar1:String, customPar2:String, strOpenId:String, strOpenKey:String):SEnterParam
		{
			var s_:SEnterParam = new SEnterParam();
			s_.byPtType = byPtType;
			s_.byQQPtType = byQQPtType;
			s_.byQQPtLv = byQQPtLv;
			s_.byQQPtYearType = byQQPtYearType;
			s_.byQQPtLuxuryType = byQQPtLuxuryType;
			s_.customPar1 = customPar1;
			s_.customPar2 = customPar2;
			s_.strOpenId = strOpenId;
			s_.strOpenKey = strOpenKey;
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
				topXml = <SEnterParam _name_={name_} byPtType={byPtType} byQQPtType={byQQPtType} byQQPtLv={byQQPtLv} byQQPtYearType={byQQPtYearType} byQQPtLuxuryType={byQQPtLuxuryType}
				 customPar1={customPar1} customPar2={customPar2} strOpenId={strOpenId} strOpenKey={strOpenKey}/>;
			else
				topXml = <SEnterParam byPtType={byPtType} byQQPtType={byQQPtType} byQQPtLv={byQQPtLv} byQQPtYearType={byQQPtYearType} byQQPtLuxuryType={byQQPtLuxuryType}
				 customPar1={customPar1} customPar2={customPar2} strOpenId={strOpenId} strOpenKey={strOpenKey}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byPtType = byPtType;
			obj_.byQQPtType = byQQPtType;
			obj_.byQQPtLv = byQQPtLv;
			obj_.byQQPtYearType = byQQPtYearType;
			obj_.byQQPtLuxuryType = byQQPtLuxuryType;
			obj_.customPar1 = customPar1;
			obj_.customPar2 = customPar2;
			obj_.strOpenId = strOpenId;
			obj_.strOpenKey = strOpenKey;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEnterParam
		{
			var s_:SEnterParam = new SEnterParam();
			var byPtType:uint = bytes.readUnsignedByte();
			s_.byPtType = byPtType;
			var byQQPtType:uint = bytes.readUnsignedByte();
			s_.byQQPtType = byQQPtType;
			var byQQPtLv:uint = bytes.readUnsignedByte();
			s_.byQQPtLv = byQQPtLv;
			var byQQPtYearType:uint = bytes.readUnsignedByte();
			s_.byQQPtYearType = byQQPtYearType;
			var byQQPtLuxuryType:uint = bytes.readUnsignedByte();
			s_.byQQPtLuxuryType = byQQPtLuxuryType;
			var customPar1:String = BytesUtil.readString(bytes);
			s_.customPar1 = customPar1;
			var customPar2:String = BytesUtil.readString(bytes);
			s_.customPar2 = customPar2;
			var strOpenId:String = BytesUtil.readString(bytes);
			s_.strOpenId = strOpenId;
			var strOpenKey:String = BytesUtil.readString(bytes);
			s_.strOpenKey = strOpenKey;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEnterParam>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEnterParam> = new Vector.<SEnterParam>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEnterParam = SEnterParam.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byPtType);
			bytes.writeByte(byQQPtType);
			bytes.writeByte(byQQPtLv);
			bytes.writeByte(byQQPtYearType);
			bytes.writeByte(byQQPtLuxuryType);
			BytesUtil.writeString(bytes, customPar1);
			BytesUtil.writeString(bytes, customPar2);
			BytesUtil.writeString(bytes, strOpenId);
			BytesUtil.writeString(bytes, strOpenKey);
		}

		public static function vectorToByteArray(vec:Vector.<SEnterParam>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEnterParam in vec)
				s.toByteArray(bytes);
		}
	}
}
