/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBeastSoulInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 兽魂信息
	 */
	public final class SBeastSoulInfo
	{
		public var eType:uint; //(枚举类型：EBeastSoulType)兽魂类型
		public var byRank:uint; //(无符号8位整数)兽魂星图等级
		public var byLevel:uint; //(无符号8位整数)兽魂星魂等级

		/**
		 * 辅助创建函数
		 */
		public static function create(eType:uint, byRank:uint, byLevel:uint):SBeastSoulInfo
		{
			var s_:SBeastSoulInfo = new SBeastSoulInfo();
			s_.eType = eType;
			s_.byRank = byRank;
			s_.byLevel = byLevel;
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
				topXml = <SBeastSoulInfo _name_={name_} eType={eType} byRank={byRank} byLevel={byLevel}/>;
			else
				topXml = <SBeastSoulInfo eType={eType} byRank={byRank} byLevel={byLevel}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.eType = eType;
			obj_.byRank = byRank;
			obj_.byLevel = byLevel;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBeastSoulInfo
		{
			var s_:SBeastSoulInfo = new SBeastSoulInfo();
			var eType:uint = bytes.readUnsignedByte();
			s_.eType = eType;
			var byRank:uint = bytes.readUnsignedByte();
			s_.byRank = byRank;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBeastSoulInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBeastSoulInfo> = new Vector.<SBeastSoulInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBeastSoulInfo = SBeastSoulInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eType);
			bytes.writeByte(byRank);
			bytes.writeByte(byLevel);
		}

		public static function vectorToByteArray(vec:Vector.<SBeastSoulInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBeastSoulInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
