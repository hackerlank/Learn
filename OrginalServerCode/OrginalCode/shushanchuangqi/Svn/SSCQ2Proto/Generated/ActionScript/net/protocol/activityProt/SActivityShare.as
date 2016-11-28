/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SActivityShare.as
//  Purpose:      活力任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.activityProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 活力分享列表
	 */
	public final class SActivityShare
	{
		public var dwActivityID:uint; //(无符号32位整数)活跃度ID
		public var eStatus:uint; //(枚举类型：EShareStatus)分享状态

		/**
		 * 辅助创建函数
		 */
		public static function create(dwActivityID:uint, eStatus:uint):SActivityShare
		{
			var s_:SActivityShare = new SActivityShare();
			s_.dwActivityID = dwActivityID;
			s_.eStatus = eStatus;
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
				topXml = <SActivityShare _name_={name_} dwActivityID={dwActivityID} eStatus={eStatus}/>;
			else
				topXml = <SActivityShare dwActivityID={dwActivityID} eStatus={eStatus}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwActivityID = dwActivityID;
			obj_.eStatus = eStatus;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SActivityShare
		{
			var s_:SActivityShare = new SActivityShare();
			var dwActivityID:uint = bytes.readUnsignedInt();
			s_.dwActivityID = dwActivityID;
			var eStatus:uint = bytes.readUnsignedByte();
			s_.eStatus = eStatus;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SActivityShare>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SActivityShare> = new Vector.<SActivityShare>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SActivityShare = SActivityShare.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwActivityID);
			bytes.writeByte(eStatus);
		}

		public static function vectorToByteArray(vec:Vector.<SActivityShare>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SActivityShare in vec)
				s.toByteArray(bytes);
		}
	}
}
