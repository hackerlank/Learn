/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGRLevelInfo.as
//  Purpose:      排行榜相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.rankProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派等级排名
	 */
	public final class SGRLevelInfo extends SGuildRankInfo
	{
		public var wLevel2:uint; //(无符号16位整数)帮派等级

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SRankInfo.eType_SGRLevelInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SGRLevelInfo _name_={name_} wLevel2={wLevel2}/>;
			else
				topXml = <SGRLevelInfo wLevel2={wLevel2}/>;
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
			obj_.wLevel2 = wLevel2;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGRLevelInfo
		{
			var s_:SGRLevelInfo = new SGRLevelInfo();
			var base_:SGuildRankInfo = SGuildRankInfo.fromByteArray(bytes);
			base_.copyTo(s_);
			var wLevel2:uint = bytes.readUnsignedShort();
			s_.wLevel2 = wLevel2;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGRLevelInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGRLevelInfo> = new Vector.<SGRLevelInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGRLevelInfo = SGRLevelInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wLevel2);
		}

		public static function vectorToByteArray(vec:Vector.<SGRLevelInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGRLevelInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
