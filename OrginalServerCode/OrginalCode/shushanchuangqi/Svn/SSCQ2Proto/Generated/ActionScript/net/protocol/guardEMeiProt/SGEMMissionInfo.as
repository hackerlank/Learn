/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGEMMissionInfo.as
//  Purpose:      守卫峨眉协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guardEMeiProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 守卫峨眉关卡信息
	 */
	public final class SGEMMissionInfo
	{
		public var wFreeEntryNumDay:uint; //(无符号16位整数)当日免费进入次数
		public var wBuyEntryNumDay:uint; //(无符号16位整数)当日购买进入次数
		public var wBuyEntryTotalNum:uint; //(无符号16位整数)购买进入总次数
		public var qwIsGuardSucc:BigInteger; //(无符号64位整数)每一位表示守卫是否成功（注：0未成功；1成功）
		public var wCurMissionID:uint; //(无符号16位整数)正在进行的关卡ID（注：0表示没有）
		public var byGEMType:uint; //(无符号8位整数)正在进行的类型（注：0表示没有；1：守卫；2：扫荡）
		public var wCurProgress:uint; //(无符号16位整数)正在进行的关卡进度（注：0表示没有）

		/**
		 * 辅助创建函数
		 */
		public static function create(wFreeEntryNumDay:uint, wBuyEntryNumDay:uint, wBuyEntryTotalNum:uint, qwIsGuardSucc:BigInteger, wCurMissionID:uint, 
			byGEMType:uint, wCurProgress:uint):SGEMMissionInfo
		{
			var s_:SGEMMissionInfo = new SGEMMissionInfo();
			s_.wFreeEntryNumDay = wFreeEntryNumDay;
			s_.wBuyEntryNumDay = wBuyEntryNumDay;
			s_.wBuyEntryTotalNum = wBuyEntryTotalNum;
			s_.qwIsGuardSucc = qwIsGuardSucc;
			s_.wCurMissionID = wCurMissionID;
			s_.byGEMType = byGEMType;
			s_.wCurProgress = wCurProgress;
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
				topXml = <SGEMMissionInfo _name_={name_} wFreeEntryNumDay={wFreeEntryNumDay} wBuyEntryNumDay={wBuyEntryNumDay} wBuyEntryTotalNum={wBuyEntryTotalNum} qwIsGuardSucc={qwIsGuardSucc} wCurMissionID={wCurMissionID}
				 byGEMType={byGEMType} wCurProgress={wCurProgress}/>;
			else
				topXml = <SGEMMissionInfo wFreeEntryNumDay={wFreeEntryNumDay} wBuyEntryNumDay={wBuyEntryNumDay} wBuyEntryTotalNum={wBuyEntryTotalNum} qwIsGuardSucc={qwIsGuardSucc} wCurMissionID={wCurMissionID}
				 byGEMType={byGEMType} wCurProgress={wCurProgress}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wFreeEntryNumDay = wFreeEntryNumDay;
			obj_.wBuyEntryNumDay = wBuyEntryNumDay;
			obj_.wBuyEntryTotalNum = wBuyEntryTotalNum;
			obj_.qwIsGuardSucc = qwIsGuardSucc;
			obj_.wCurMissionID = wCurMissionID;
			obj_.byGEMType = byGEMType;
			obj_.wCurProgress = wCurProgress;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGEMMissionInfo
		{
			var s_:SGEMMissionInfo = new SGEMMissionInfo();
			var wFreeEntryNumDay:uint = bytes.readUnsignedShort();
			s_.wFreeEntryNumDay = wFreeEntryNumDay;
			var wBuyEntryNumDay:uint = bytes.readUnsignedShort();
			s_.wBuyEntryNumDay = wBuyEntryNumDay;
			var wBuyEntryTotalNum:uint = bytes.readUnsignedShort();
			s_.wBuyEntryTotalNum = wBuyEntryTotalNum;
			var qwIsGuardSucc:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwIsGuardSucc = qwIsGuardSucc;
			var wCurMissionID:uint = bytes.readUnsignedShort();
			s_.wCurMissionID = wCurMissionID;
			var byGEMType:uint = bytes.readUnsignedByte();
			s_.byGEMType = byGEMType;
			var wCurProgress:uint = bytes.readUnsignedShort();
			s_.wCurProgress = wCurProgress;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGEMMissionInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGEMMissionInfo> = new Vector.<SGEMMissionInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGEMMissionInfo = SGEMMissionInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wFreeEntryNumDay);
			bytes.writeShort(wBuyEntryNumDay);
			bytes.writeShort(wBuyEntryTotalNum);
			BytesUtil.writeUInt64(bytes, qwIsGuardSucc);
			bytes.writeShort(wCurMissionID);
			bytes.writeByte(byGEMType);
			bytes.writeShort(wCurProgress);
		}

		public static function vectorToByteArray(vec:Vector.<SGEMMissionInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGEMMissionInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
