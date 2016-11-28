/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattleBuffInfo.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 战斗外的Buff信息
	 */
	public final class SBattleBuffInfo
	{
		public var wBuffID:uint; //(无符号16位整数)Buff种类
		public var vecBuffData:Vector.<uint>; //(无符号32位整数)Buff数值
		public var dwBuffCount:uint; //(无符号32位整数)Buff叠加层数
		public var dwBuffTime:uint; //(无符号32位整数)Buff失效时间

		/**
		 * 辅助创建函数
		 */
		public static function create(wBuffID:uint, vecBuffData:Vector.<uint>, dwBuffCount:uint, dwBuffTime:uint):SBattleBuffInfo
		{
			var s_:SBattleBuffInfo = new SBattleBuffInfo();
			s_.wBuffID = wBuffID;
			s_.vecBuffData = vecBuffData;
			s_.dwBuffCount = dwBuffCount;
			s_.dwBuffTime = dwBuffTime;
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
				topXml = <SBattleBuffInfo _name_={name_} wBuffID={wBuffID} dwBuffCount={dwBuffCount} dwBuffTime={dwBuffTime}/>;
			else
				topXml = <SBattleBuffInfo wBuffID={wBuffID} dwBuffCount={dwBuffCount} dwBuffTime={dwBuffTime}/>;
			if(vecBuffData != null)
			{
				var vecBuffDataXml:XML = <Vec_UINT32 _name_="vecBuffData"/>;
				var text1:String = "";
				for each(var value1:uint in vecBuffData)
					text1 += "[" + value1 + "]";
				vecBuffDataXml.appendChild(text1);
				topXml.appendChild(vecBuffDataXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wBuffID = wBuffID;
			obj_.vecBuffData = vecBuffData;
			obj_.dwBuffCount = dwBuffCount;
			obj_.dwBuffTime = dwBuffTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattleBuffInfo
		{
			var s_:SBattleBuffInfo = new SBattleBuffInfo();
			var wBuffID:uint = bytes.readUnsignedShort();
			s_.wBuffID = wBuffID;
			var vecBuffData:Vector.<uint> = BytesUtil.readVecUInt(bytes);
			s_.vecBuffData = vecBuffData;
			var dwBuffCount:uint = bytes.readUnsignedInt();
			s_.dwBuffCount = dwBuffCount;
			var dwBuffTime:uint = bytes.readUnsignedInt();
			s_.dwBuffTime = dwBuffTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattleBuffInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleBuffInfo> = new Vector.<SBattleBuffInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleBuffInfo = SBattleBuffInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wBuffID);
			BytesUtil.writeVecUInt(bytes, vecBuffData);
			bytes.writeUnsignedInt(dwBuffCount);
			bytes.writeUnsignedInt(dwBuffTime);
		}

		public static function vectorToByteArray(vec:Vector.<SBattleBuffInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleBuffInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
