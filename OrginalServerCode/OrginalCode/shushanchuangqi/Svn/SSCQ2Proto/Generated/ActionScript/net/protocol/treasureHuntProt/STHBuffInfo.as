/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STHBuffInfo.as
//  Purpose:      寻宝协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.treasureHuntProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 寻宝buff信息
	 */
	public final class STHBuffInfo
	{
		public var byBuffID:uint; //(无符号8位整数)BuffID
		public var byBuffNum:uint; //(无符号8位整数)今日已使用Buff次数
		public var dwBuffCDTime:uint; //(无符号32位整数)Buff CD 时间

		/**
		 * 辅助创建函数
		 */
		public static function create(byBuffID:uint, byBuffNum:uint, dwBuffCDTime:uint):STHBuffInfo
		{
			var s_:STHBuffInfo = new STHBuffInfo();
			s_.byBuffID = byBuffID;
			s_.byBuffNum = byBuffNum;
			s_.dwBuffCDTime = dwBuffCDTime;
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
				topXml = <STHBuffInfo _name_={name_} byBuffID={byBuffID} byBuffNum={byBuffNum} dwBuffCDTime={dwBuffCDTime}/>;
			else
				topXml = <STHBuffInfo byBuffID={byBuffID} byBuffNum={byBuffNum} dwBuffCDTime={dwBuffCDTime}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byBuffID = byBuffID;
			obj_.byBuffNum = byBuffNum;
			obj_.dwBuffCDTime = dwBuffCDTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STHBuffInfo
		{
			var s_:STHBuffInfo = new STHBuffInfo();
			var byBuffID:uint = bytes.readUnsignedByte();
			s_.byBuffID = byBuffID;
			var byBuffNum:uint = bytes.readUnsignedByte();
			s_.byBuffNum = byBuffNum;
			var dwBuffCDTime:uint = bytes.readUnsignedInt();
			s_.dwBuffCDTime = dwBuffCDTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STHBuffInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STHBuffInfo> = new Vector.<STHBuffInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STHBuffInfo = STHBuffInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byBuffID);
			bytes.writeByte(byBuffNum);
			bytes.writeUnsignedInt(dwBuffCDTime);
		}

		public static function vectorToByteArray(vec:Vector.<STHBuffInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STHBuffInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
