/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRRLevelInfo.as
//  Purpose:      排行榜相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.rankProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 等级信息
	 */
	public final class SRRLevelInfo extends SRoleRankInfo
	{
		public var wLevel:uint; //(无符号16位整数)等级
		public var qwExp:BigInteger; //(无符号64位整数)经验值

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SRankInfo.eType_SRRLevelInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRRLevelInfo _name_={name_} wLevel={wLevel} qwExp={qwExp}/>;
			else
				topXml = <SRRLevelInfo wLevel={wLevel} qwExp={qwExp}/>;
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
			obj_.qwExp = qwExp;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRRLevelInfo
		{
			var s_:SRRLevelInfo = new SRRLevelInfo();
			var base_:SRoleRankInfo = SRoleRankInfo.fromByteArray(bytes);
			base_.copyTo(s_);
			var wLevel:uint = bytes.readUnsignedShort();
			s_.wLevel = wLevel;
			var qwExp:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwExp = qwExp;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRRLevelInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRRLevelInfo> = new Vector.<SRRLevelInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRRLevelInfo = SRRLevelInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wLevel);
			BytesUtil.writeUInt64(bytes, qwExp);
		}

		public static function vectorToByteArray(vec:Vector.<SRRLevelInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRRLevelInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
