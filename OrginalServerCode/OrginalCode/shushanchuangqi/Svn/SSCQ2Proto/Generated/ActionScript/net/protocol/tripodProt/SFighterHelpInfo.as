/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFighterHelpInfo.as
//  Purpose:      九疑鼎相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.tripodProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 九疑鼎散仙协助
	 */
	public final class SFighterHelpInfo
	{
		public var wFighterID:uint; //(无符号16位整数)散仙ID
		public var byPos:uint; //(无符号8位整数)协助位置(0,1)
		public var byColor:uint; //(无符号8位整数)散仙协助时的品质
		public var dwStartTime:uint; //(无符号32位整数)开始协助的时间

		/**
		 * 辅助创建函数
		 */
		public static function create(wFighterID:uint, byPos:uint, byColor:uint, dwStartTime:uint):SFighterHelpInfo
		{
			var s_:SFighterHelpInfo = new SFighterHelpInfo();
			s_.wFighterID = wFighterID;
			s_.byPos = byPos;
			s_.byColor = byColor;
			s_.dwStartTime = dwStartTime;
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
				topXml = <SFighterHelpInfo _name_={name_} wFighterID={wFighterID} byPos={byPos} byColor={byColor} dwStartTime={dwStartTime}/>;
			else
				topXml = <SFighterHelpInfo wFighterID={wFighterID} byPos={byPos} byColor={byColor} dwStartTime={dwStartTime}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wFighterID = wFighterID;
			obj_.byPos = byPos;
			obj_.byColor = byColor;
			obj_.dwStartTime = dwStartTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFighterHelpInfo
		{
			var s_:SFighterHelpInfo = new SFighterHelpInfo();
			var wFighterID:uint = bytes.readUnsignedShort();
			s_.wFighterID = wFighterID;
			var byPos:uint = bytes.readUnsignedByte();
			s_.byPos = byPos;
			var byColor:uint = bytes.readUnsignedByte();
			s_.byColor = byColor;
			var dwStartTime:uint = bytes.readUnsignedInt();
			s_.dwStartTime = dwStartTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFighterHelpInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFighterHelpInfo> = new Vector.<SFighterHelpInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFighterHelpInfo = SFighterHelpInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wFighterID);
			bytes.writeByte(byPos);
			bytes.writeByte(byColor);
			bytes.writeUnsignedInt(dwStartTime);
		}

		public static function vectorToByteArray(vec:Vector.<SFighterHelpInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFighterHelpInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
