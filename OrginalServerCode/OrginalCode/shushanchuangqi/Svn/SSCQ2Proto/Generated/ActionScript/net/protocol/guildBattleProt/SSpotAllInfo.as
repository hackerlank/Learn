/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SSpotAllInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 据点详细信息
	 */
	public final class SSpotAllInfo extends SSpotInfo
	{
		public var eState:uint; //(枚举类型：EGBSpotState)据点状态
		public var vecMemberInfoA:Vector.<SBattleUserInfo>; //A方成员信息
		public var vecMemberInfoB:Vector.<SBattleUserInfo>; //B方成员信息
		public var vecBattleSlotInfo:Vector.<SBattleSlotInfo>; //战斗场信息
		public var vecBattleInfo:Vector.<SBattleInfo>; //战报信息

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SSpotInfo.eType_SSpotAllInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SSpotAllInfo _name_={name_} eState={eState}/>;
			else
				topXml = <SSpotAllInfo eState={eState}/>;
			if(vecMemberInfoA != null)
			{
				var vecMemberInfoAXml:XML = <Vec_SBattleUserInfo _name_="vecMemberInfoA"/>;
				for each(var s1:SBattleUserInfo in vecMemberInfoA)
					vecMemberInfoAXml.appendChild(s1.toXML());
				topXml.appendChild(vecMemberInfoAXml);
			}
			if(vecMemberInfoB != null)
			{
				var vecMemberInfoBXml:XML = <Vec_SBattleUserInfo _name_="vecMemberInfoB"/>;
				for each(var s2:SBattleUserInfo in vecMemberInfoB)
					vecMemberInfoBXml.appendChild(s2.toXML());
				topXml.appendChild(vecMemberInfoBXml);
			}
			if(vecBattleSlotInfo != null)
			{
				var vecBattleSlotInfoXml:XML = <Vec_SBattleSlotInfo _name_="vecBattleSlotInfo"/>;
				for each(var s3:SBattleSlotInfo in vecBattleSlotInfo)
					vecBattleSlotInfoXml.appendChild(s3.toXML());
				topXml.appendChild(vecBattleSlotInfoXml);
			}
			if(vecBattleInfo != null)
			{
				var vecBattleInfoXml:XML = <Vec_SBattleInfo _name_="vecBattleInfo"/>;
				for each(var s4:SBattleInfo in vecBattleInfo)
					vecBattleInfoXml.appendChild(s4.toXML());
				topXml.appendChild(vecBattleInfoXml);
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
			obj_.eState = eState;
			obj_.vecMemberInfoA = vecMemberInfoA;
			obj_.vecMemberInfoB = vecMemberInfoB;
			obj_.vecBattleSlotInfo = vecBattleSlotInfo;
			obj_.vecBattleInfo = vecBattleInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SSpotAllInfo
		{
			var s_:SSpotAllInfo = new SSpotAllInfo();
			var base_:SSpotInfo = SSpotInfo.fromByteArray(bytes);
			base_.copyTo(s_);
			var eState:uint = bytes.readUnsignedByte();
			s_.eState = eState;
			var vecMemberInfoA:Vector.<SBattleUserInfo> = SBattleUserInfo.superVectorFromByteArray(bytes);
			s_.vecMemberInfoA = vecMemberInfoA;
			var vecMemberInfoB:Vector.<SBattleUserInfo> = SBattleUserInfo.superVectorFromByteArray(bytes);
			s_.vecMemberInfoB = vecMemberInfoB;
			var vecBattleSlotInfo:Vector.<SBattleSlotInfo> = SBattleSlotInfo.vectorFromByteArray(bytes);
			s_.vecBattleSlotInfo = vecBattleSlotInfo;
			var vecBattleInfo:Vector.<SBattleInfo> = SBattleInfo.vectorFromByteArray(bytes);
			s_.vecBattleInfo = vecBattleInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SSpotAllInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SSpotAllInfo> = new Vector.<SSpotAllInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SSpotAllInfo = SSpotAllInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeByte(eState);
			SBattleUserInfo.superVectorToByteArray(vecMemberInfoA, bytes);
			SBattleUserInfo.superVectorToByteArray(vecMemberInfoB, bytes);
			SBattleSlotInfo.vectorToByteArray(vecBattleSlotInfo, bytes);
			SBattleInfo.vectorToByteArray(vecBattleInfo, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SSpotAllInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SSpotAllInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
