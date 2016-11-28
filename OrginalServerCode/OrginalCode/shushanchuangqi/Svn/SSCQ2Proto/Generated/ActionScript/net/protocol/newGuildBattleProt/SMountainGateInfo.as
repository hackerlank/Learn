/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SMountainGateInfo.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 灵山城门信息
	 */
	public final class SMountainGateInfo
	{
		public var dwRemainTime:uint; //(无符号32位整数)开始倒计时
		public var dwGateMaxHP:uint; //(无符号32位整数)城门总血量
		public var dwGateHP:uint; //(无符号32位整数)城门剩余血量
		public var vecPuppetInfo:Vector.<SPuppetInfo>; //傀儡信息
		public var eSelfSide:uint; //(枚举类型：ENGBSide)自己所在方向
		public var sSelfInfo:SPlayerInfo; //自己的信息
		public var vecPlayerInfo:Vector.<SPlayerPanelInfo>; //对面玩家信息

		/**
		 * 辅助创建函数
		 */
		public static function create(dwRemainTime:uint, dwGateMaxHP:uint, dwGateHP:uint, vecPuppetInfo:Vector.<SPuppetInfo>, eSelfSide:uint, 
			sSelfInfo:SPlayerInfo, vecPlayerInfo:Vector.<SPlayerPanelInfo>):SMountainGateInfo
		{
			var s_:SMountainGateInfo = new SMountainGateInfo();
			s_.dwRemainTime = dwRemainTime;
			s_.dwGateMaxHP = dwGateMaxHP;
			s_.dwGateHP = dwGateHP;
			s_.vecPuppetInfo = vecPuppetInfo;
			s_.eSelfSide = eSelfSide;
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
				topXml = <SMountainGateInfo _name_={name_} dwRemainTime={dwRemainTime} dwGateMaxHP={dwGateMaxHP} dwGateHP={dwGateHP} eSelfSide={eSelfSide}/>;
			else
				topXml = <SMountainGateInfo dwRemainTime={dwRemainTime} dwGateMaxHP={dwGateMaxHP} dwGateHP={dwGateHP} eSelfSide={eSelfSide}/>;
			if(vecPuppetInfo != null)
			{
				var vecPuppetInfoXml:XML = <Vec_SPuppetInfo _name_="vecPuppetInfo"/>;
				for each(var s1:SPuppetInfo in vecPuppetInfo)
					vecPuppetInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecPuppetInfoXml);
			}
			if(sSelfInfo != null)
				topXml.appendChild(sSelfInfo.toXML("sSelfInfo"));
			if(vecPlayerInfo != null)
			{
				var vecPlayerInfoXml:XML = <Vec_SPlayerPanelInfo _name_="vecPlayerInfo"/>;
				for each(var s3:SPlayerPanelInfo in vecPlayerInfo)
					vecPlayerInfoXml.appendChild(s3.toXML());
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
			obj_.dwGateMaxHP = dwGateMaxHP;
			obj_.dwGateHP = dwGateHP;
			obj_.vecPuppetInfo = vecPuppetInfo;
			obj_.eSelfSide = eSelfSide;
			obj_.sSelfInfo = sSelfInfo;
			obj_.vecPlayerInfo = vecPlayerInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SMountainGateInfo
		{
			var s_:SMountainGateInfo = new SMountainGateInfo();
			var dwRemainTime:uint = bytes.readUnsignedInt();
			s_.dwRemainTime = dwRemainTime;
			var dwGateMaxHP:uint = bytes.readUnsignedInt();
			s_.dwGateMaxHP = dwGateMaxHP;
			var dwGateHP:uint = bytes.readUnsignedInt();
			s_.dwGateHP = dwGateHP;
			var vecPuppetInfo:Vector.<SPuppetInfo> = SPuppetInfo.vectorFromByteArray(bytes);
			s_.vecPuppetInfo = vecPuppetInfo;
			var eSelfSide:uint = bytes.readUnsignedByte();
			s_.eSelfSide = eSelfSide;
			var sSelfInfo:SPlayerInfo = SPlayerInfo.fromByteArray(bytes);
			s_.sSelfInfo = sSelfInfo;
			var vecPlayerInfo:Vector.<SPlayerPanelInfo> = SPlayerPanelInfo.vectorFromByteArray(bytes);
			s_.vecPlayerInfo = vecPlayerInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SMountainGateInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SMountainGateInfo> = new Vector.<SMountainGateInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SMountainGateInfo = SMountainGateInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwRemainTime);
			bytes.writeUnsignedInt(dwGateMaxHP);
			bytes.writeUnsignedInt(dwGateHP);
			SPuppetInfo.vectorToByteArray(vecPuppetInfo, bytes);
			bytes.writeByte(eSelfSide);
			sSelfInfo.toByteArray(bytes);
			SPlayerPanelInfo.vectorToByteArray(vecPlayerInfo, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SMountainGateInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SMountainGateInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
