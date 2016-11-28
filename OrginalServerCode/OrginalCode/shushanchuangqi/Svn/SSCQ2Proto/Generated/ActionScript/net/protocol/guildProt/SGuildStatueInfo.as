/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGuildStatueInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派神像
	 */
	public final class SGuildStatueInfo extends SGuildInfoBase
	{
		public var wLevel:uint; //(无符号16位整数)神像等级
		public var dwExp:uint; //(无符号32位整数)神像经验值
		public var vecLogInfo:Vector.<SGuildLogInfo>; //神像日志
		public var byWorshipCount:uint; //(无符号8位整数)供奉人数
		public var byWorshipBit:uint; //(无符号8位整数)当前供奉（第N位表示第N种供奉类型）
		public var dwTime:uint; //(无符号32位整数)操作时间

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SGuildInfoBase.eType_SGuildStatueInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SGuildStatueInfo _name_={name_} wLevel={wLevel} dwExp={dwExp} byWorshipCount={byWorshipCount} byWorshipBit={byWorshipBit}
				 dwTime={dwTime}/>;
			else
				topXml = <SGuildStatueInfo wLevel={wLevel} dwExp={dwExp} byWorshipCount={byWorshipCount} byWorshipBit={byWorshipBit}
				 dwTime={dwTime}/>;
			if(vecLogInfo != null)
			{
				var vecLogInfoXml:XML = <Vec_SGuildLogInfo _name_="vecLogInfo"/>;
				for each(var s1:SGuildLogInfo in vecLogInfo)
					vecLogInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecLogInfoXml);
			}
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public override function copyTo(obj_:*):void
		{
			super.copyTo(obj_);
			obj_.wLevel = wLevel;
			obj_.dwExp = dwExp;
			obj_.vecLogInfo = vecLogInfo;
			obj_.byWorshipCount = byWorshipCount;
			obj_.byWorshipBit = byWorshipBit;
			obj_.dwTime = dwTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGuildStatueInfo
		{
			var s_:SGuildStatueInfo = new SGuildStatueInfo();
			var base_:SGuildInfoBase = SGuildInfoBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var wLevel:uint = bytes.readUnsignedShort();
			s_.wLevel = wLevel;
			var dwExp:uint = bytes.readUnsignedInt();
			s_.dwExp = dwExp;
			var vecLogInfo:Vector.<SGuildLogInfo> = SGuildLogInfo.vectorFromByteArray(bytes);
			s_.vecLogInfo = vecLogInfo;
			var byWorshipCount:uint = bytes.readUnsignedByte();
			s_.byWorshipCount = byWorshipCount;
			var byWorshipBit:uint = bytes.readUnsignedByte();
			s_.byWorshipBit = byWorshipBit;
			var dwTime:uint = bytes.readUnsignedInt();
			s_.dwTime = dwTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGuildStatueInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildStatueInfo> = new Vector.<SGuildStatueInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildStatueInfo = SGuildStatueInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wLevel);
			bytes.writeUnsignedInt(dwExp);
			SGuildLogInfo.vectorToByteArray(vecLogInfo, bytes);
			bytes.writeByte(byWorshipCount);
			bytes.writeByte(byWorshipBit);
			bytes.writeUnsignedInt(dwTime);
		}

		public static function vectorToByteArray(vec:Vector.<SGuildStatueInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildStatueInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
