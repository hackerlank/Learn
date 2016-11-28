/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGuildTechInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派科技
	 */
	public final class SGuildTechInfo extends SGuildInfoBase
	{
		public var eType:uint; //(枚举类型：ETechType)科技类型
		public var wLevel:uint; //(无符号16位整数)科技等级

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SGuildInfoBase.eType_SGuildTechInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SGuildTechInfo _name_={name_} eType={eType} wLevel={wLevel}/>;
			else
				topXml = <SGuildTechInfo eType={eType} wLevel={wLevel}/>;
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
			obj_.eType = eType;
			obj_.wLevel = wLevel;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGuildTechInfo
		{
			var s_:SGuildTechInfo = new SGuildTechInfo();
			var base_:SGuildInfoBase = SGuildInfoBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var eType:uint = bytes.readUnsignedByte();
			s_.eType = eType;
			var wLevel:uint = bytes.readUnsignedShort();
			s_.wLevel = wLevel;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGuildTechInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildTechInfo> = new Vector.<SGuildTechInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildTechInfo = SGuildTechInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeByte(eType);
			bytes.writeShort(wLevel);
		}

		public static function vectorToByteArray(vec:Vector.<SGuildTechInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildTechInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
