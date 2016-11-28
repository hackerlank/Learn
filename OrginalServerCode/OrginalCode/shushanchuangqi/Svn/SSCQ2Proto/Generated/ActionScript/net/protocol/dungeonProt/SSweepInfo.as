/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SSweepInfo.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 扫荡信息
	 */
	public final class SSweepInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var wCurDgnID:uint; //(无符号16位整数)当前扫荡副本
		public var wCurCount:uint; //(无符号16位整数)当前剩余扫荡次数
		public var dwReserverTime:uint; //(无符号32位整数)下次扫荡剩余时间
		public var dwSaveTime:uint; //(无符号32位整数)保存时间
		public var wOptions:uint; //(无符号16位整数)扫荡类型
		public var wCount:uint; //(无符号16位整数)扫荡需求次数
		public var strVecDgn:String; //未开始扫荡副本

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, wCurDgnID:uint, wCurCount:uint, dwReserverTime:uint, dwSaveTime:uint, 
			wOptions:uint, wCount:uint, strVecDgn:String):SSweepInfo
		{
			var s_:SSweepInfo = new SSweepInfo();
			s_.qwRoleID = qwRoleID;
			s_.wCurDgnID = wCurDgnID;
			s_.wCurCount = wCurCount;
			s_.dwReserverTime = dwReserverTime;
			s_.dwSaveTime = dwSaveTime;
			s_.wOptions = wOptions;
			s_.wCount = wCount;
			s_.strVecDgn = strVecDgn;
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
				topXml = <SSweepInfo _name_={name_} qwRoleID={qwRoleID} wCurDgnID={wCurDgnID} wCurCount={wCurCount} dwReserverTime={dwReserverTime} dwSaveTime={dwSaveTime}
				 wOptions={wOptions} wCount={wCount} strVecDgn={strVecDgn}/>;
			else
				topXml = <SSweepInfo qwRoleID={qwRoleID} wCurDgnID={wCurDgnID} wCurCount={wCurCount} dwReserverTime={dwReserverTime} dwSaveTime={dwSaveTime}
				 wOptions={wOptions} wCount={wCount} strVecDgn={strVecDgn}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.wCurDgnID = wCurDgnID;
			obj_.wCurCount = wCurCount;
			obj_.dwReserverTime = dwReserverTime;
			obj_.dwSaveTime = dwSaveTime;
			obj_.wOptions = wOptions;
			obj_.wCount = wCount;
			obj_.strVecDgn = strVecDgn;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SSweepInfo
		{
			var s_:SSweepInfo = new SSweepInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var wCurDgnID:uint = bytes.readUnsignedShort();
			s_.wCurDgnID = wCurDgnID;
			var wCurCount:uint = bytes.readUnsignedShort();
			s_.wCurCount = wCurCount;
			var dwReserverTime:uint = bytes.readUnsignedInt();
			s_.dwReserverTime = dwReserverTime;
			var dwSaveTime:uint = bytes.readUnsignedInt();
			s_.dwSaveTime = dwSaveTime;
			var wOptions:uint = bytes.readUnsignedShort();
			s_.wOptions = wOptions;
			var wCount:uint = bytes.readUnsignedShort();
			s_.wCount = wCount;
			var strVecDgn:String = BytesUtil.readString(bytes);
			s_.strVecDgn = strVecDgn;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SSweepInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SSweepInfo> = new Vector.<SSweepInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SSweepInfo = SSweepInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeShort(wCurDgnID);
			bytes.writeShort(wCurCount);
			bytes.writeUnsignedInt(dwReserverTime);
			bytes.writeUnsignedInt(dwSaveTime);
			bytes.writeShort(wOptions);
			bytes.writeShort(wCount);
			BytesUtil.writeString(bytes, strVecDgn);
		}

		public static function vectorToByteArray(vec:Vector.<SSweepInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SSweepInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
