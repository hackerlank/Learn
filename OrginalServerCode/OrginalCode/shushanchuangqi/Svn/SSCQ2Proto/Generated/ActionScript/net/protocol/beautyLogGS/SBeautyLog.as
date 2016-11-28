/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBeautyLog.as
//  Purpose:      美女log
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.beautyLogGS
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 美女log信息
	 */
	public final class SBeautyLog
	{
		public var qwUserID:BigInteger; //(无符号64位整数)uid
		public var strRoleName:String; //角色名
		public var byColor:uint; //(无符号8位整数)角色颜色
		public var wItemID:uint; //(无符号16位整数)物品id
		public var dwCount:uint; //(无符号32位整数)物品数量

		/**
		 * 辅助创建函数
		 */
		public static function create(qwUserID:BigInteger, strRoleName:String, byColor:uint, wItemID:uint, dwCount:uint):SBeautyLog
		{
			var s_:SBeautyLog = new SBeautyLog();
			s_.qwUserID = qwUserID;
			s_.strRoleName = strRoleName;
			s_.byColor = byColor;
			s_.wItemID = wItemID;
			s_.dwCount = dwCount;
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
				topXml = <SBeautyLog _name_={name_} qwUserID={qwUserID} strRoleName={strRoleName} byColor={byColor} wItemID={wItemID} dwCount={dwCount}/>;
			else
				topXml = <SBeautyLog qwUserID={qwUserID} strRoleName={strRoleName} byColor={byColor} wItemID={wItemID} dwCount={dwCount}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwUserID = qwUserID;
			obj_.strRoleName = strRoleName;
			obj_.byColor = byColor;
			obj_.wItemID = wItemID;
			obj_.dwCount = dwCount;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBeautyLog
		{
			var s_:SBeautyLog = new SBeautyLog();
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwUserID = qwUserID;
			var strRoleName:String = BytesUtil.readString(bytes);
			s_.strRoleName = strRoleName;
			var byColor:uint = bytes.readUnsignedByte();
			s_.byColor = byColor;
			var wItemID:uint = bytes.readUnsignedShort();
			s_.wItemID = wItemID;
			var dwCount:uint = bytes.readUnsignedInt();
			s_.dwCount = dwCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBeautyLog>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBeautyLog> = new Vector.<SBeautyLog>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBeautyLog = SBeautyLog.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwUserID);
			BytesUtil.writeString(bytes, strRoleName);
			bytes.writeByte(byColor);
			bytes.writeShort(wItemID);
			bytes.writeUnsignedInt(dwCount);
		}

		public static function vectorToByteArray(vec:Vector.<SBeautyLog>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBeautyLog in vec)
				s.toByteArray(bytes);
		}
	}
}
