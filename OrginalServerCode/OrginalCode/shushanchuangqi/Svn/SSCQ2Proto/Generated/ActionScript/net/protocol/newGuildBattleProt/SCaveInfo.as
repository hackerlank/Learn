/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SCaveInfo.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 洞府战具体信息
	 */
	public final class SCaveInfo
	{
		public var dwRemainTime:uint; //(无符号32位整数)开始倒计时
		public var eSelfSide:uint; //(枚举类型：ENGBSide)自己所在方向
		public var vecCaveCoreInfo:Vector.<SCaveCoreInfo>; //阵眼信息
		public var vecCaveAttackGuildInfo:Vector.<SCaveAttackGuildInfo>; //洞府攻击帮派信息
		public var sSelfInfo:SPlayerInfo; //自己的信息
		public var vecPlayerInfo:Vector.<SPlayerPanelInfo>; //对面玩家信息

		/**
		 * 辅助创建函数
		 */
		public static function create(dwRemainTime:uint, eSelfSide:uint, vecCaveCoreInfo:Vector.<SCaveCoreInfo>, vecCaveAttackGuildInfo:Vector.<SCaveAttackGuildInfo>, sSelfInfo:SPlayerInfo, 
			vecPlayerInfo:Vector.<SPlayerPanelInfo>):SCaveInfo
		{
			var s_:SCaveInfo = new SCaveInfo();
			s_.dwRemainTime = dwRemainTime;
			s_.eSelfSide = eSelfSide;
			s_.vecCaveCoreInfo = vecCaveCoreInfo;
			s_.vecCaveAttackGuildInfo = vecCaveAttackGuildInfo;
			s_.sSelfInfo = sSelfInfo;
			s_.vecPlayerInfo = vecPlayerInfo;
			return s_;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SCaveInfo _name_={name_} dwRemainTime={dwRemainTime} eSelfSide={eSelfSide}/>;
			else
				topXml = <SCaveInfo dwRemainTime={dwRemainTime} eSelfSide={eSelfSide}/>;
			if(vecCaveCoreInfo != null)
			{
				var vecCaveCoreInfoXml:XML = <Vec_SCaveCoreInfo _name_="vecCaveCoreInfo"/>;
				for each(var s1:SCaveCoreInfo in vecCaveCoreInfo)
					vecCaveCoreInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecCaveCoreInfoXml);
			}
			if(vecCaveAttackGuildInfo != null)
			{
				var vecCaveAttackGuildInfoXml:XML = <Vec_SCaveAttackGuildInfo _name_="vecCaveAttackGuildInfo"/>;
				for each(var s2:SCaveAttackGuildInfo in vecCaveAttackGuildInfo)
					vecCaveAttackGuildInfoXml.appendChild(s2.toXML());
				topXml.appendChild(vecCaveAttackGuildInfoXml);
			}
			if(sSelfInfo != null)
				topXml.appendChild(sSelfInfo.toXML("sSelfInfo"));
			if(vecPlayerInfo != null)
			{
				var vecPlayerInfoXml:XML = <Vec_SPlayerPanelInfo _name_="vecPlayerInfo"/>;
				for each(var s4:SPlayerPanelInfo in vecPlayerInfo)
					vecPlayerInfoXml.appendChild(s4.toXML());
				topXml.appendChild(vecPlayerInfoXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwRemainTime = dwRemainTime;
			obj_.eSelfSide = eSelfSide;
			obj_.vecCaveCoreInfo = vecCaveCoreInfo;
			obj_.vecCaveAttackGuildInfo = vecCaveAttackGuildInfo;
			obj_.sSelfInfo = sSelfInfo;
			obj_.vecPlayerInfo = vecPlayerInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SCaveInfo
		{
			var s_:SCaveInfo = new SCaveInfo();
			var dwRemainTime:uint = bytes.readUnsignedInt();
			s_.dwRemainTime = dwRemainTime;
			var eSelfSide:uint = bytes.readUnsignedByte();
			s_.eSelfSide = eSelfSide;
			var vecCaveCoreInfo:Vector.<SCaveCoreInfo> = SCaveCoreInfo.vectorFromByteArray(bytes);
			s_.vecCaveCoreInfo = vecCaveCoreInfo;
			var vecCaveAttackGuildInfo:Vector.<SCaveAttackGuildInfo> = SCaveAttackGuildInfo.vectorFromByteArray(bytes);
			s_.vecCaveAttackGuildInfo = vecCaveAttackGuildInfo;
			var sSelfInfo:SPlayerInfo = SPlayerInfo.fromByteArray(bytes);
			s_.sSelfInfo = sSelfInfo;
			var vecPlayerInfo:Vector.<SPlayerPanelInfo> = SPlayerPanelInfo.vectorFromByteArray(bytes);
			s_.vecPlayerInfo = vecPlayerInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SCaveInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SCaveInfo> = new Vector.<SCaveInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SCaveInfo = SCaveInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwRemainTime);
			bytes.writeByte(eSelfSide);
			SCaveCoreInfo.vectorToByteArray(vecCaveCoreInfo, bytes);
			SCaveAttackGuildInfo.vectorToByteArray(vecCaveAttackGuildInfo, bytes);
			sSelfInfo.toByteArray(bytes);
			SPlayerPanelInfo.vectorToByteArray(vecPlayerInfo, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SCaveInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SCaveInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
