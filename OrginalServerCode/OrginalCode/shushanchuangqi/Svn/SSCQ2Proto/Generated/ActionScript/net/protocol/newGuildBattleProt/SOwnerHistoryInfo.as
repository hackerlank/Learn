/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SOwnerHistoryInfo.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 占领历史信息
	 */
	public final class SOwnerHistoryInfo
	{
		public var eMountainType:uint; //(枚举类型：ENGBMountain)灵山类型
		public var qwGuildID:BigInteger; //(无符号64位整数)当前占领帮派ID
		public var strGuildName:String; //当前占领帮派名称
		public var strGuildOwnerName:String; //当前占领帮派帮主名称
		public var dwTime:uint; //(无符号32位整数)占领时间

		/**
		 * 辅助创建函数
		 */
		public static function create(eMountainType:uint, qwGuildID:BigInteger, strGuildName:String, strGuildOwnerName:String, dwTime:uint):SOwnerHistoryInfo
		{
			var s_:SOwnerHistoryInfo = new SOwnerHistoryInfo();
			s_.eMountainType = eMountainType;
			s_.qwGuildID = qwGuildID;
			s_.strGuildName = strGuildName;
			s_.strGuildOwnerName = strGuildOwnerName;
			s_.dwTime = dwTime;
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
				topXml = <SOwnerHistoryInfo _name_={name_} eMountainType={eMountainType} qwGuildID={qwGuildID} strGuildName={strGuildName} strGuildOwnerName={strGuildOwnerName} dwTime={dwTime}/>;
			else
				topXml = <SOwnerHistoryInfo eMountainType={eMountainType} qwGuildID={qwGuildID} strGuildName={strGuildName} strGuildOwnerName={strGuildOwnerName} dwTime={dwTime}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.eMountainType = eMountainType;
			obj_.qwGuildID = qwGuildID;
			obj_.strGuildName = strGuildName;
			obj_.strGuildOwnerName = strGuildOwnerName;
			obj_.dwTime = dwTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SOwnerHistoryInfo
		{
			var s_:SOwnerHistoryInfo = new SOwnerHistoryInfo();
			var eMountainType:uint = bytes.readUnsignedByte();
			s_.eMountainType = eMountainType;
			var qwGuildID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwGuildID = qwGuildID;
			var strGuildName:String = BytesUtil.readString(bytes);
			s_.strGuildName = strGuildName;
			var strGuildOwnerName:String = BytesUtil.readString(bytes);
			s_.strGuildOwnerName = strGuildOwnerName;
			var dwTime:uint = bytes.readUnsignedInt();
			s_.dwTime = dwTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SOwnerHistoryInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SOwnerHistoryInfo> = new Vector.<SOwnerHistoryInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SOwnerHistoryInfo = SOwnerHistoryInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eMountainType);
			BytesUtil.writeUInt64(bytes, qwGuildID);
			BytesUtil.writeString(bytes, strGuildName);
			BytesUtil.writeString(bytes, strGuildOwnerName);
			bytes.writeUnsignedInt(dwTime);
		}

		public static function vectorToByteArray(vec:Vector.<SOwnerHistoryInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SOwnerHistoryInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
