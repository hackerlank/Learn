/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGEMBuffInfo.as
//  Purpose:      守卫峨眉协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guardEMeiProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 守卫峨眉Buff信息
	 */
	public final class SGEMBuffInfo
	{
		public var dwBuffID:uint; //(无符号32位整数)BuffID
		public var dwBuffNum:uint; //(无符号32位整数)Buff数量

		/**
		 * 辅助创建函数
		 */
		public static function create(dwBuffID:uint, dwBuffNum:uint):SGEMBuffInfo
		{
			var s_:SGEMBuffInfo = new SGEMBuffInfo();
			s_.dwBuffID = dwBuffID;
			s_.dwBuffNum = dwBuffNum;
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
				topXml = <SGEMBuffInfo _name_={name_} dwBuffID={dwBuffID} dwBuffNum={dwBuffNum}/>;
			else
				topXml = <SGEMBuffInfo dwBuffID={dwBuffID} dwBuffNum={dwBuffNum}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwBuffID = dwBuffID;
			obj_.dwBuffNum = dwBuffNum;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGEMBuffInfo
		{
			var s_:SGEMBuffInfo = new SGEMBuffInfo();
			var dwBuffID:uint = bytes.readUnsignedInt();
			s_.dwBuffID = dwBuffID;
			var dwBuffNum:uint = bytes.readUnsignedInt();
			s_.dwBuffNum = dwBuffNum;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGEMBuffInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGEMBuffInfo> = new Vector.<SGEMBuffInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGEMBuffInfo = SGEMBuffInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwBuffID);
			bytes.writeUnsignedInt(dwBuffNum);
		}

		public static function vectorToByteArray(vec:Vector.<SGEMBuffInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGEMBuffInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
