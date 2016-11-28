/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SWActPlayerInfo.as
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 人物信息
	 */
	public final class SWActPlayerInfo
	{
		public var wWActID:uint; //(无符号16位整数)活动ID
		public var wID:uint; //(无符号16位整数)散仙|阵灵ID
		public var qwPlayerID:BigInteger; //(无符号64位整数)玩家ID
		public var strName:String; //玩家名字|帮主名
		public var eCareer:uint; //(枚举类型：protoCommon.ECareerType)玩家职业
		public var eSex:uint; //(枚举类型：protoCommon.ESexType)玩家性别
		public var strName1:String; //帮派名
		public var dwValue1:uint; //(无符号32位整数)参数1(战力，等级，散仙，阵灵，帮派）排名
		public var dwValue2:uint; //(无符号32位整数)参数2(战力，等级，散仙战力，阵灵战力，帮派等级)

		/**
		 * 辅助创建函数
		 */
		public static function create(wWActID:uint, wID:uint, qwPlayerID:BigInteger, strName:String, eCareer:uint, 
			eSex:uint, strName1:String, dwValue1:uint, dwValue2:uint):SWActPlayerInfo
		{
			var s_:SWActPlayerInfo = new SWActPlayerInfo();
			s_.wWActID = wWActID;
			s_.wID = wID;
			s_.qwPlayerID = qwPlayerID;
			s_.strName = strName;
			s_.eCareer = eCareer;
			s_.eSex = eSex;
			s_.strName1 = strName1;
			s_.dwValue1 = dwValue1;
			s_.dwValue2 = dwValue2;
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
				topXml = <SWActPlayerInfo _name_={name_} wWActID={wWActID} wID={wID} qwPlayerID={qwPlayerID} strName={strName} eCareer={eCareer}
				 eSex={eSex} strName1={strName1} dwValue1={dwValue1} dwValue2={dwValue2}/>;
			else
				topXml = <SWActPlayerInfo wWActID={wWActID} wID={wID} qwPlayerID={qwPlayerID} strName={strName} eCareer={eCareer}
				 eSex={eSex} strName1={strName1} dwValue1={dwValue1} dwValue2={dwValue2}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wWActID = wWActID;
			obj_.wID = wID;
			obj_.qwPlayerID = qwPlayerID;
			obj_.strName = strName;
			obj_.eCareer = eCareer;
			obj_.eSex = eSex;
			obj_.strName1 = strName1;
			obj_.dwValue1 = dwValue1;
			obj_.dwValue2 = dwValue2;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SWActPlayerInfo
		{
			var s_:SWActPlayerInfo = new SWActPlayerInfo();
			var wWActID:uint = bytes.readUnsignedShort();
			s_.wWActID = wWActID;
			var wID:uint = bytes.readUnsignedShort();
			s_.wID = wID;
			var qwPlayerID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwPlayerID = qwPlayerID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var eCareer:uint = bytes.readUnsignedByte();
			s_.eCareer = eCareer;
			var eSex:uint = bytes.readUnsignedByte();
			s_.eSex = eSex;
			var strName1:String = BytesUtil.readString(bytes);
			s_.strName1 = strName1;
			var dwValue1:uint = bytes.readUnsignedInt();
			s_.dwValue1 = dwValue1;
			var dwValue2:uint = bytes.readUnsignedInt();
			s_.dwValue2 = dwValue2;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SWActPlayerInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SWActPlayerInfo> = new Vector.<SWActPlayerInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SWActPlayerInfo = SWActPlayerInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wWActID);
			bytes.writeShort(wID);
			BytesUtil.writeUInt64(bytes, qwPlayerID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeByte(eCareer);
			bytes.writeByte(eSex);
			BytesUtil.writeString(bytes, strName1);
			bytes.writeUnsignedInt(dwValue1);
			bytes.writeUnsignedInt(dwValue2);
		}

		public static function vectorToByteArray(vec:Vector.<SWActPlayerInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SWActPlayerInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
