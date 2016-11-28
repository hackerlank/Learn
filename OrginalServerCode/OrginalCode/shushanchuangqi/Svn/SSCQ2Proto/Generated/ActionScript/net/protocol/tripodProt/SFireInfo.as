/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFireInfo.as
//  Purpose:      九疑鼎相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.tripodProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家的九疑鼎火种数据
	 */
	public final class SFireInfo
	{
		public var wFireID:uint; //(无符号16位整数)九疑鼎火种ID
		public var dwSucceed:uint; //(无符号32位整数)火种祈火成功次数
		public var dwRemain:uint; //(无符号32位整数)火种剩余祈火次数

		/**
		 * 辅助创建函数
		 */
		public static function create(wFireID:uint, dwSucceed:uint, dwRemain:uint):SFireInfo
		{
			var s_:SFireInfo = new SFireInfo();
			s_.wFireID = wFireID;
			s_.dwSucceed = dwSucceed;
			s_.dwRemain = dwRemain;
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
				topXml = <SFireInfo _name_={name_} wFireID={wFireID} dwSucceed={dwSucceed} dwRemain={dwRemain}/>;
			else
				topXml = <SFireInfo wFireID={wFireID} dwSucceed={dwSucceed} dwRemain={dwRemain}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wFireID = wFireID;
			obj_.dwSucceed = dwSucceed;
			obj_.dwRemain = dwRemain;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFireInfo
		{
			var s_:SFireInfo = new SFireInfo();
			var wFireID:uint = bytes.readUnsignedShort();
			s_.wFireID = wFireID;
			var dwSucceed:uint = bytes.readUnsignedInt();
			s_.dwSucceed = dwSucceed;
			var dwRemain:uint = bytes.readUnsignedInt();
			s_.dwRemain = dwRemain;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFireInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFireInfo> = new Vector.<SFireInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFireInfo = SFireInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wFireID);
			bytes.writeUnsignedInt(dwSucceed);
			bytes.writeUnsignedInt(dwRemain);
		}

		public static function vectorToByteArray(vec:Vector.<SFireInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFireInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
