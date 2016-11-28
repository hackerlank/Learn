/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SOtherGuildListInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 没有帮派返回的其他帮派列表信息
	 */
	public final class SOtherGuildListInfo extends SGetGuildInfoBase
	{
		public var dwMaxGuildCount:uint; //(无符号32位整数)最大帮派
		public var dwCurGuildCount:uint; //(无符号32位整数)当前帮派索引
		public var vecGuildListInfo:Vector.<SGuildListInfo>; //帮派列表信息
		public var vecApplyGuildID:Vector.<BigInteger>; //(无符号64位整数)已申请列表帮派ID

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SGetGuildInfoBase.eType_SOtherGuildListInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SOtherGuildListInfo _name_={name_} dwMaxGuildCount={dwMaxGuildCount} dwCurGuildCount={dwCurGuildCount}/>;
			else
				topXml = <SOtherGuildListInfo dwMaxGuildCount={dwMaxGuildCount} dwCurGuildCount={dwCurGuildCount}/>;
			if(vecGuildListInfo != null)
			{
				var vecGuildListInfoXml:XML = <Vec_SGuildListInfo _name_="vecGuildListInfo"/>;
				for each(var s1:SGuildListInfo in vecGuildListInfo)
					vecGuildListInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecGuildListInfoXml);
			}
			if(vecApplyGuildID != null)
			{
				var vecApplyGuildIDXml:XML = <Vec_UINT64 _name_="vecApplyGuildID"/>;
				var text2:String = "";
				for each(var value2:BigInteger in vecApplyGuildID)
					text2 += "[" + value2 + "]";
				vecApplyGuildIDXml.appendChild(text2);
				topXml.appendChild(vecApplyGuildIDXml);
			}
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwMaxGuildCount = dwMaxGuildCount;
			obj_.dwCurGuildCount = dwCurGuildCount;
			obj_.vecGuildListInfo = vecGuildListInfo;
			obj_.vecApplyGuildID = vecApplyGuildID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SOtherGuildListInfo
		{
			var s_:SOtherGuildListInfo = new SOtherGuildListInfo();
			var base_:SGetGuildInfoBase = SGetGuildInfoBase.fromByteArray(bytes);
			var dwMaxGuildCount:uint = bytes.readUnsignedInt();
			s_.dwMaxGuildCount = dwMaxGuildCount;
			var dwCurGuildCount:uint = bytes.readUnsignedInt();
			s_.dwCurGuildCount = dwCurGuildCount;
			var vecGuildListInfo:Vector.<SGuildListInfo> = SGuildListInfo.vectorFromByteArray(bytes);
			s_.vecGuildListInfo = vecGuildListInfo;
			var vecApplyGuildID:Vector.<BigInteger> = BytesUtil.readVecUInt64(bytes);
			s_.vecApplyGuildID = vecApplyGuildID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SOtherGuildListInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SOtherGuildListInfo> = new Vector.<SOtherGuildListInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SOtherGuildListInfo = SOtherGuildListInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeUnsignedInt(dwMaxGuildCount);
			bytes.writeUnsignedInt(dwCurGuildCount);
			SGuildListInfo.vectorToByteArray(vecGuildListInfo, bytes);
			BytesUtil.writeVecUInt64(bytes, vecApplyGuildID);
		}

		public static function vectorToByteArray(vec:Vector.<SOtherGuildListInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SOtherGuildListInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
