/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SSpotReadyInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 报名阶段据点信息
	 */
	public final class SSpotReadyInfo extends SSpotInfo
	{
		public var byCount:uint; //(无符号8位整数)该据点人数

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SSpotInfo.eType_SSpotReadyInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SSpotReadyInfo _name_={name_} byCount={byCount}/>;
			else
				topXml = <SSpotReadyInfo byCount={byCount}/>;
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
			obj_.byCount = byCount;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SSpotReadyInfo
		{
			var s_:SSpotReadyInfo = new SSpotReadyInfo();
			var base_:SSpotInfo = SSpotInfo.fromByteArray(bytes);
			base_.copyTo(s_);
			var byCount:uint = bytes.readUnsignedByte();
			s_.byCount = byCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SSpotReadyInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SSpotReadyInfo> = new Vector.<SSpotReadyInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SSpotReadyInfo = SSpotReadyInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeByte(byCount);
		}

		public static function vectorToByteArray(vec:Vector.<SSpotReadyInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SSpotReadyInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
