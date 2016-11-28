/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SMountainPanelInfo.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 灵山面板信息
	 */
	public final class SMountainPanelInfo
	{
		public var eMountainType:uint; //(枚举类型：ENGBMountain)灵山类型
		public var eState:uint; //(枚举类型：ENGBMountainState)灵山状态
		public var qwGuildID:BigInteger; //(无符号64位整数)当前占领帮派ID
		public var strGuildName:String; //当前占领帮派名称
		public var wGuildLevel:uint; //(无符号16位整数)当前占领帮派等级
		public var strGuildOwnerName:String; //当前占领帮派帮主名称
		public var dwGuildOwnCount:uint; //(无符号32位整数)当前占领帮派占领次数
		public var vecAttackGuildID:Vector.<BigInteger>; //(无符号64位整数)（洞府战）攻击帮派ID

		/**
		 * 辅助创建函数
		 */
		public static function create(eMountainType:uint, eState:uint, qwGuildID:BigInteger, strGuildName:String, wGuildLevel:uint, 
			strGuildOwnerName:String, dwGuildOwnCount:uint, vecAttackGuildID:Vector.<BigInteger>):SMountainPanelInfo
		{
			var s_:SMountainPanelInfo = new SMountainPanelInfo();
			s_.eMountainType = eMountainType;
			s_.eState = eState;
			s_.qwGuildID = qwGuildID;
			s_.strGuildName = strGuildName;
			s_.wGuildLevel = wGuildLevel;
			s_.strGuildOwnerName = strGuildOwnerName;
			s_.dwGuildOwnCount = dwGuildOwnCount;
			s_.vecAttackGuildID = vecAttackGuildID;
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
				topXml = <SMountainPanelInfo _name_={name_} eMountainType={eMountainType} eState={eState} qwGuildID={qwGuildID} strGuildName={strGuildName} wGuildLevel={wGuildLevel}
				 strGuildOwnerName={strGuildOwnerName} dwGuildOwnCount={dwGuildOwnCount}/>;
			else
				topXml = <SMountainPanelInfo eMountainType={eMountainType} eState={eState} qwGuildID={qwGuildID} strGuildName={strGuildName} wGuildLevel={wGuildLevel}
				 strGuildOwnerName={strGuildOwnerName} dwGuildOwnCount={dwGuildOwnCount}/>;
			if(vecAttackGuildID != null)
			{
				var vecAttackGuildIDXml:XML = <Vec_UINT64 _name_="vecAttackGuildID"/>;
				var text1:String = "";
				for each(var value1:BigInteger in vecAttackGuildID)
					text1 += "[" + value1 + "]";
				vecAttackGuildIDXml.appendChild(text1);
				topXml.appendChild(vecAttackGuildIDXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.eMountainType = eMountainType;
			obj_.eState = eState;
			obj_.qwGuildID = qwGuildID;
			obj_.strGuildName = strGuildName;
			obj_.wGuildLevel = wGuildLevel;
			obj_.strGuildOwnerName = strGuildOwnerName;
			obj_.dwGuildOwnCount = dwGuildOwnCount;
			obj_.vecAttackGuildID = vecAttackGuildID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SMountainPanelInfo
		{
			var s_:SMountainPanelInfo = new SMountainPanelInfo();
			var eMountainType:uint = bytes.readUnsignedByte();
			s_.eMountainType = eMountainType;
			var eState:uint = bytes.readUnsignedByte();
			s_.eState = eState;
			var qwGuildID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwGuildID = qwGuildID;
			var strGuildName:String = BytesUtil.readString(bytes);
			s_.strGuildName = strGuildName;
			var wGuildLevel:uint = bytes.readUnsignedShort();
			s_.wGuildLevel = wGuildLevel;
			var strGuildOwnerName:String = BytesUtil.readString(bytes);
			s_.strGuildOwnerName = strGuildOwnerName;
			var dwGuildOwnCount:uint = bytes.readUnsignedInt();
			s_.dwGuildOwnCount = dwGuildOwnCount;
			var vecAttackGuildID:Vector.<BigInteger> = BytesUtil.readVecUInt64(bytes);
			s_.vecAttackGuildID = vecAttackGuildID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SMountainPanelInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SMountainPanelInfo> = new Vector.<SMountainPanelInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SMountainPanelInfo = SMountainPanelInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eMountainType);
			bytes.writeByte(eState);
			BytesUtil.writeUInt64(bytes, qwGuildID);
			BytesUtil.writeString(bytes, strGuildName);
			bytes.writeShort(wGuildLevel);
			BytesUtil.writeString(bytes, strGuildOwnerName);
			bytes.writeUnsignedInt(dwGuildOwnCount);
			BytesUtil.writeVecUInt64(bytes, vecAttackGuildID);
		}

		public static function vectorToByteArray(vec:Vector.<SMountainPanelInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SMountainPanelInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
