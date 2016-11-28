/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SSelfGuildInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 存在帮派的本帮信息
	 */
	public final class SSelfGuildInfo extends SGetGuildInfoBase
	{
		public var sAllInfo:SGuildAllInfo; //帮派完整信息

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SGetGuildInfoBase.eType_SSelfGuildInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SSelfGuildInfo _name_={name_}/>;
			else
				topXml = <SSelfGuildInfo/>;
			if(sAllInfo != null)
				topXml.appendChild(sAllInfo.toXML("sAllInfo"));
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.sAllInfo = sAllInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SSelfGuildInfo
		{
			var s_:SSelfGuildInfo = new SSelfGuildInfo();
			var base_:SGetGuildInfoBase = SGetGuildInfoBase.fromByteArray(bytes);
			var sAllInfo:SGuildAllInfo = SGuildAllInfo.fromByteArray(bytes);
			s_.sAllInfo = sAllInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SSelfGuildInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SSelfGuildInfo> = new Vector.<SSelfGuildInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SSelfGuildInfo = SSelfGuildInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			sAllInfo.toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SSelfGuildInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SSelfGuildInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
