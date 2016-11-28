/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SDBBuffInfo.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * Buff数据信息
	 */
	public final class SDBBuffInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)对应玩家ID
		public var qwOwnerID:BigInteger; //(无符号64位整数)所属实例ID(Role/Fighter/...
		public var eBuffType:uint; //(枚举类型：EBuffType)Buff大类
		public var wBuffID:uint; //(无符号16位整数)Buff种类
		public var eBuffEffectType:uint; //(枚举类型：EBuffEffectType)Buff效果类型
		public var eBuffState:uint; //(枚举类型：EBuffState)Buff当前状态
		public var vecBuffParam:Vector.<uint>; //(无符号32位整数)Buff效果参数
		public var dwBuffCount:uint; //(无符号32位整数)Buff失效次数
		public var dwBuffTime:uint; //(无符号32位整数)Buff失效时间
		public var vecEffectMapID:Vector.<uint>; //(无符号32位整数)地图ID限制，空表示任意地图
		public var byBattleType:uint; //(无符号8位整数)有效的战斗类型(不存数据库)

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, qwOwnerID:BigInteger, eBuffType:uint, wBuffID:uint, eBuffEffectType:uint, 
			eBuffState:uint, vecBuffParam:Vector.<uint>, dwBuffCount:uint, dwBuffTime:uint, vecEffectMapID:Vector.<uint>, 
			byBattleType:uint):SDBBuffInfo
		{
			var s_:SDBBuffInfo = new SDBBuffInfo();
			s_.qwRoleID = qwRoleID;
			s_.qwOwnerID = qwOwnerID;
			s_.eBuffType = eBuffType;
			s_.wBuffID = wBuffID;
			s_.eBuffEffectType = eBuffEffectType;
			s_.eBuffState = eBuffState;
			s_.vecBuffParam = vecBuffParam;
			s_.dwBuffCount = dwBuffCount;
			s_.dwBuffTime = dwBuffTime;
			s_.vecEffectMapID = vecEffectMapID;
			s_.byBattleType = byBattleType;
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
				topXml = <SDBBuffInfo _name_={name_} qwRoleID={qwRoleID} qwOwnerID={qwOwnerID} eBuffType={eBuffType} wBuffID={wBuffID} eBuffEffectType={eBuffEffectType}
				 eBuffState={eBuffState} dwBuffCount={dwBuffCount} dwBuffTime={dwBuffTime}
				 byBattleType={byBattleType}/>;
			else
				topXml = <SDBBuffInfo qwRoleID={qwRoleID} qwOwnerID={qwOwnerID} eBuffType={eBuffType} wBuffID={wBuffID} eBuffEffectType={eBuffEffectType}
				 eBuffState={eBuffState} dwBuffCount={dwBuffCount} dwBuffTime={dwBuffTime}
				 byBattleType={byBattleType}/>;
			if(vecBuffParam != null)
			{
				var vecBuffParamXml:XML = <Vec_UINT32 _name_="vecBuffParam"/>;
				var text1:String = "";
				for each(var value1:uint in vecBuffParam)
					text1 += "[" + value1 + "]";
				vecBuffParamXml.appendChild(text1);
				topXml.appendChild(vecBuffParamXml);
			}
			if(vecEffectMapID != null)
			{
				var vecEffectMapIDXml:XML = <Vec_UINT32 _name_="vecEffectMapID"/>;
				var text2:String = "";
				for each(var value2:uint in vecEffectMapID)
					text2 += "[" + value2 + "]";
				vecEffectMapIDXml.appendChild(text2);
				topXml.appendChild(vecEffectMapIDXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.qwOwnerID = qwOwnerID;
			obj_.eBuffType = eBuffType;
			obj_.wBuffID = wBuffID;
			obj_.eBuffEffectType = eBuffEffectType;
			obj_.eBuffState = eBuffState;
			obj_.vecBuffParam = vecBuffParam;
			obj_.dwBuffCount = dwBuffCount;
			obj_.dwBuffTime = dwBuffTime;
			obj_.vecEffectMapID = vecEffectMapID;
			obj_.byBattleType = byBattleType;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SDBBuffInfo
		{
			var s_:SDBBuffInfo = new SDBBuffInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var qwOwnerID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwOwnerID = qwOwnerID;
			var eBuffType:uint = bytes.readUnsignedByte();
			s_.eBuffType = eBuffType;
			var wBuffID:uint = bytes.readUnsignedShort();
			s_.wBuffID = wBuffID;
			var eBuffEffectType:uint = bytes.readUnsignedByte();
			s_.eBuffEffectType = eBuffEffectType;
			var eBuffState:uint = bytes.readUnsignedByte();
			s_.eBuffState = eBuffState;
			var vecBuffParam:Vector.<uint> = BytesUtil.readVecUInt(bytes);
			s_.vecBuffParam = vecBuffParam;
			var dwBuffCount:uint = bytes.readUnsignedInt();
			s_.dwBuffCount = dwBuffCount;
			var dwBuffTime:uint = bytes.readUnsignedInt();
			s_.dwBuffTime = dwBuffTime;
			var vecEffectMapID:Vector.<uint> = BytesUtil.readVecUInt(bytes);
			s_.vecEffectMapID = vecEffectMapID;
			var byBattleType:uint = bytes.readUnsignedByte();
			s_.byBattleType = byBattleType;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SDBBuffInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SDBBuffInfo> = new Vector.<SDBBuffInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SDBBuffInfo = SDBBuffInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeUInt64(bytes, qwOwnerID);
			bytes.writeByte(eBuffType);
			bytes.writeShort(wBuffID);
			bytes.writeByte(eBuffEffectType);
			bytes.writeByte(eBuffState);
			BytesUtil.writeVecUInt(bytes, vecBuffParam);
			bytes.writeUnsignedInt(dwBuffCount);
			bytes.writeUnsignedInt(dwBuffTime);
			BytesUtil.writeVecUInt(bytes, vecEffectMapID);
			bytes.writeByte(byBattleType);
		}

		public static function vectorToByteArray(vec:Vector.<SDBBuffInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SDBBuffInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
