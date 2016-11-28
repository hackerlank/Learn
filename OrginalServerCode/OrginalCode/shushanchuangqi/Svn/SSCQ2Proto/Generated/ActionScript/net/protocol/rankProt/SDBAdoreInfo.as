/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SDBAdoreInfo.as
//  Purpose:      排行榜相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.rankProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 崇拜数据库信息
	 */
	public final class SDBAdoreInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var dwCount:uint; //(无符号32位整数)被崇拜数量
		public var dwUpdateTime:uint; //(无符号32位整数)更新时间

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, dwCount:uint, dwUpdateTime:uint):SDBAdoreInfo
		{
			var s_:SDBAdoreInfo = new SDBAdoreInfo();
			s_.qwRoleID = qwRoleID;
			s_.dwCount = dwCount;
			s_.dwUpdateTime = dwUpdateTime;
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
				topXml = <SDBAdoreInfo _name_={name_} qwRoleID={qwRoleID} dwCount={dwCount} dwUpdateTime={dwUpdateTime}/>;
			else
				topXml = <SDBAdoreInfo qwRoleID={qwRoleID} dwCount={dwCount} dwUpdateTime={dwUpdateTime}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.dwCount = dwCount;
			obj_.dwUpdateTime = dwUpdateTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SDBAdoreInfo
		{
			var s_:SDBAdoreInfo = new SDBAdoreInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var dwCount:uint = bytes.readUnsignedInt();
			s_.dwCount = dwCount;
			var dwUpdateTime:uint = bytes.readUnsignedInt();
			s_.dwUpdateTime = dwUpdateTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SDBAdoreInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SDBAdoreInfo> = new Vector.<SDBAdoreInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SDBAdoreInfo = SDBAdoreInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeUnsignedInt(dwCount);
			bytes.writeUnsignedInt(dwUpdateTime);
		}

		public static function vectorToByteArray(vec:Vector.<SDBAdoreInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SDBAdoreInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
