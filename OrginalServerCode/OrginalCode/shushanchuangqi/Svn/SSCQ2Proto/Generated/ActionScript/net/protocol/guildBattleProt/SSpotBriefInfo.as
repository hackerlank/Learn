/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SSpotBriefInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 据点简略信息
	 */
	public final class SSpotBriefInfo extends SSpotInfo
	{
		public var eState:uint; //(枚举类型：EGBSpotState)据点状态

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SSpotInfo.eType_SSpotBriefInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SSpotBriefInfo _name_={name_} eState={eState}/>;
			else
				topXml = <SSpotBriefInfo eState={eState}/>;
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
			obj_.eState = eState;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SSpotBriefInfo
		{
			var s_:SSpotBriefInfo = new SSpotBriefInfo();
			var base_:SSpotInfo = SSpotInfo.fromByteArray(bytes);
			base_.copyTo(s_);
			var eState:uint = bytes.readUnsignedByte();
			s_.eState = eState;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SSpotBriefInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SSpotBriefInfo> = new Vector.<SSpotBriefInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SSpotBriefInfo = SSpotBriefInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeByte(eState);
		}

		public static function vectorToByteArray(vec:Vector.<SSpotBriefInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SSpotBriefInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
