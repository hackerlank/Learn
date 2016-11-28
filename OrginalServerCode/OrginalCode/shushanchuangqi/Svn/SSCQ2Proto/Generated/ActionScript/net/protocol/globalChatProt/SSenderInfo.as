/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SSenderInfo.as
//  Purpose:      全局聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.globalChatProt
{
	import com.hurlant.math.BigInteger;
	import net.protocol.protoCommon.SPlatformParam;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 发送者信息
	 */
	public final class SSenderInfo
	{
		public var byVIPType:uint; //(无符号8位整数)VIP特权类型
		public var qwUsrID:BigInteger; //(无符号64位整数)帐号ID
		public var strName:String; //发送者名
		public var strGuildName:String; //帮派名称
		public var byQuality:uint; //(无符号8位整数)玩家品质（颜色）
		public var byNation:uint; //(无符号8位整数)发送者国家
		public var vecPlatforms:Vector.<SPlatformParam>; //平台相关参数

		/**
		 * 辅助创建函数
		 */
		public static function create(byVIPType:uint, qwUsrID:BigInteger, strName:String, strGuildName:String, byQuality:uint, 
			byNation:uint, vecPlatforms:Vector.<SPlatformParam>):SSenderInfo
		{
			var s_:SSenderInfo = new SSenderInfo();
			s_.byVIPType = byVIPType;
			s_.qwUsrID = qwUsrID;
			s_.strName = strName;
			s_.strGuildName = strGuildName;
			s_.byQuality = byQuality;
			s_.byNation = byNation;
			s_.vecPlatforms = vecPlatforms;
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
				topXml = <SSenderInfo _name_={name_} byVIPType={byVIPType} qwUsrID={qwUsrID} strName={strName} strGuildName={strGuildName} byQuality={byQuality}
				 byNation={byNation}/>;
			else
				topXml = <SSenderInfo byVIPType={byVIPType} qwUsrID={qwUsrID} strName={strName} strGuildName={strGuildName} byQuality={byQuality}
				 byNation={byNation}/>;
			if(vecPlatforms != null)
			{
				var vecPlatformsXml:XML = <Vec_SPlatformParam _name_="vecPlatforms"/>;
				for each(var s1:SPlatformParam in vecPlatforms)
					vecPlatformsXml.appendChild(s1.toXML());
				topXml.appendChild(vecPlatformsXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byVIPType = byVIPType;
			obj_.qwUsrID = qwUsrID;
			obj_.strName = strName;
			obj_.strGuildName = strGuildName;
			obj_.byQuality = byQuality;
			obj_.byNation = byNation;
			obj_.vecPlatforms = vecPlatforms;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SSenderInfo
		{
			var s_:SSenderInfo = new SSenderInfo();
			var byVIPType:uint = bytes.readUnsignedByte();
			s_.byVIPType = byVIPType;
			var qwUsrID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwUsrID = qwUsrID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var strGuildName:String = BytesUtil.readString(bytes);
			s_.strGuildName = strGuildName;
			var byQuality:uint = bytes.readUnsignedByte();
			s_.byQuality = byQuality;
			var byNation:uint = bytes.readUnsignedByte();
			s_.byNation = byNation;
			var vecPlatforms:Vector.<SPlatformParam> = SPlatformParam.vectorFromByteArray(bytes);
			s_.vecPlatforms = vecPlatforms;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SSenderInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SSenderInfo> = new Vector.<SSenderInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SSenderInfo = SSenderInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byVIPType);
			BytesUtil.writeUInt64(bytes, qwUsrID);
			BytesUtil.writeString(bytes, strName);
			BytesUtil.writeString(bytes, strGuildName);
			bytes.writeByte(byQuality);
			bytes.writeByte(byNation);
			SPlatformParam.vectorToByteArray(vecPlatforms, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SSenderInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SSenderInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
