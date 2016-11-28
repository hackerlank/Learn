/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGuildBuildingInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派建筑信息
	 */
	public final class SGuildBuildingInfo extends SGuildInfoBase
	{
		public var eBuildingType:uint; //(枚举类型：EBuildingType)帮派建筑类型
		public var wLevel:uint; //(无符号16位整数)帮派建筑等级

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SGuildInfoBase.eType_SGuildBuildingInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SGuildBuildingInfo _name_={name_} eBuildingType={eBuildingType} wLevel={wLevel}/>;
			else
				topXml = <SGuildBuildingInfo eBuildingType={eBuildingType} wLevel={wLevel}/>;
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
			obj_.eBuildingType = eBuildingType;
			obj_.wLevel = wLevel;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGuildBuildingInfo
		{
			var s_:SGuildBuildingInfo = new SGuildBuildingInfo();
			var base_:SGuildInfoBase = SGuildInfoBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var eBuildingType:uint = bytes.readUnsignedByte();
			s_.eBuildingType = eBuildingType;
			var wLevel:uint = bytes.readUnsignedShort();
			s_.wLevel = wLevel;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGuildBuildingInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildBuildingInfo> = new Vector.<SGuildBuildingInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildBuildingInfo = SGuildBuildingInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeByte(eBuildingType);
			bytes.writeShort(wLevel);
		}

		public static function vectorToByteArray(vec:Vector.<SGuildBuildingInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildBuildingInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
