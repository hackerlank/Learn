/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGuildAuthorityInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派可选权限信息
	 */
	public final class SGuildAuthorityInfo extends SGuildInfoBase
	{
		public var eMemberRank:uint; //(枚举类型：EMemberRank)帮派职位
		public var dwAuthority:uint; //(无符号32位整数)可选权限 0x01:指挥帮战 0x02:升级建筑 0x04:开启血池 0x08:指挥末日之战 0x10:创建遗迹攻击小队

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SGuildInfoBase.eType_SGuildAuthorityInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SGuildAuthorityInfo _name_={name_} eMemberRank={eMemberRank} dwAuthority={dwAuthority}/>;
			else
				topXml = <SGuildAuthorityInfo eMemberRank={eMemberRank} dwAuthority={dwAuthority}/>;
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
			obj_.eMemberRank = eMemberRank;
			obj_.dwAuthority = dwAuthority;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGuildAuthorityInfo
		{
			var s_:SGuildAuthorityInfo = new SGuildAuthorityInfo();
			var base_:SGuildInfoBase = SGuildInfoBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var eMemberRank:uint = bytes.readUnsignedByte();
			s_.eMemberRank = eMemberRank;
			var dwAuthority:uint = bytes.readUnsignedInt();
			s_.dwAuthority = dwAuthority;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGuildAuthorityInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildAuthorityInfo> = new Vector.<SGuildAuthorityInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildAuthorityInfo = SGuildAuthorityInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeByte(eMemberRank);
			bytes.writeUnsignedInt(dwAuthority);
		}

		public static function vectorToByteArray(vec:Vector.<SGuildAuthorityInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildAuthorityInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
